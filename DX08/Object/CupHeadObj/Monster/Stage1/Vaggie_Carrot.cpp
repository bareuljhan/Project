#include "framework.h"
#include "Vaggie_Carrot.h"

Vaggie_Carrot::Vaggie_Carrot()
{
	_transform = make_shared<Transform>();

	CreateAction("CarrotSpawn", Action::Type::END);
	CreateAction("carrotIntro", Action::Type::END);
	CreateAction("carrotIDLE", Action::Type::END);
	CreateAction("carrotBeam", Action::Type::PINGPONG);

	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_transform);
		sprite->GetTransform()->GetScale() *= 1.2f;
	}

	_transform->SetPosition(Vector2(CENTER_X, CENTER_Y - 100));

	_actions[0]->VaggieSpawn(std::bind(&Vaggie_Carrot::SetIntro, this));
	_actions[1]->VaggieIdle(std::bind(&Vaggie_Carrot::SetIDLE, this));
	_actions[2]->VaggieBeam(std::bind(&Vaggie_Carrot::SetBeam, this));

	_actions[3]->VaggieIdle(std::bind(&Vaggie_Carrot::SetIDLE, this));

	_collider = make_shared<RectCollider>(Vector2(120, 120));
	_collider->GetTransform()->SetParent(_transform);

	_oldState = State::SPAWN;
	_actions[State::SPAWN]->Play();

	_mosaicBuffer = make_shared<CupMosaicBuffer>();
	_mosaicBuffer->_data.value1 = 3500;

	for (int i = 0; i < 4; i++)
	{
		shared_ptr<Vaggie_Bullet> bullet = make_shared<Vaggie_Bullet>();
		bullet->isActive = false;
		bullet->GetTransform()->GetScale() *= 0.8f;
		_bullets.push_back(bullet);
	}

	_muzzle = make_shared<Transform>();
	_muzzle->SetPosition(Vector2(CENTER_X, 500));
}

Vaggie_Carrot::~Vaggie_Carrot()
{
	_transform = nullptr;
}

void Vaggie_Carrot::Update()
{
	if (_mosaicBuffer->_data.value1 == 0) return;

	_collider->Update();

	if (isDead == true)
		Dead();

	for (auto bullet : _bullets)
		bullet->Update();
	for (auto action : _actions)
		action->Update();
	for (auto sprite : _sprites)
		sprite->Update();

	_transform->UpdateSRT();

	_mosaicBuffer->Update();
}

void Vaggie_Carrot::Render()
{
	if (_mosaicBuffer->_data.value1 == 0) return;

	_mosaicBuffer->SetPSBuffer(2);

	for (auto bullet : _bullets)
		bullet->Render();

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_collider->Render();
}

void Vaggie_Carrot::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Vaggie_Carrot::SetIDLE()
{
	SetAction(State::IDLE);
}

void Vaggie_Carrot::SetIntro()
{
	SetAction(State::INTRO);
	_transform->SetPosition(Vector2(CENTER_X, CENTER_Y + 100));
}

void Vaggie_Carrot::SetBeam()
{
	SetAction(State::BEAM);
}

void Vaggie_Carrot::BeamAttack(shared_ptr<Player> player)
{
	if (_curState != BEAM) return;
	if (isDead == true) return;

	Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();

	for (auto bullet : _bullets)
	{
		if (bullet->isActive == false)
		{
			bullet->Enable();
			bullet->SetFireDir(dir);
			bullet->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			break;
		}
	}
}
void Vaggie_Carrot::BulletAttack(shared_ptr<Player> player)
{
	if (_curState != IDLE) return;
	if (isDead == true) return;

	Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();

	for (auto bullet : _bullets)
	{
		if (bullet->isActive == false)
		{
			bullet->Enable();
			bullet->SetFireDir(dir);
			bullet->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			break;
		}
	}
}

void Vaggie_Carrot::GetDamaged(float amount)
{
	if (amount <= 0) return;

	_hp -= amount;

	if (_hp <= 0)
	{
		_hp = 0.0f;
		isDead = true;
		_collider->isActive = false;
	}
}

void Vaggie_Carrot::Dead()
{
	for (auto sprite : _sprites)
	{
		sprite->SetPS(ADD_PS(L"Shader/MosaicPixelShader.hlsl"));
	}
	SetAction(State::DEAD);

	_mosaicBuffer->_data.value1 -= DELTA_TIME;
}

void Vaggie_Carrot::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "Monster_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
