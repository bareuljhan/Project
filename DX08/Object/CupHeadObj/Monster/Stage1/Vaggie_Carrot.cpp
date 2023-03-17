#include "framework.h"
#include "Vaggie_Carrot.h"

Vaggie_Carrot::Vaggie_Carrot()
{
	_transform = make_shared<Transform>();

	CreateAction("CarrotSpawn", Action::Type::END);
	CreateAction("carrotIntro", Action::Type::END);
	CreateAction("carrotIDLE", Action::Type::END);
	CreateAction("carrotBeam", Action::Type::PINGPONG);
	CreateAction("carrotDeath", Action::Type::PINGPONG);

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
	_mosaicBuffer->_data.value1 = 1000;

	for (int i = 0; i < 2; i++)
	{
		shared_ptr<Vaggie_Bullet> bullet = make_shared<Vaggie_Bullet>();
		bullet->isActive = false;
		bullet->GetTransform()->GetScale() *= 0.8f;
		_bullets.push_back(bullet);
	}
	
	for (int i = 0; i < 5; i++)
	{
		shared_ptr<Vaggie_Beam> beam = make_shared<Vaggie_Beam>();
		beam->isActive = false;
		beam->GetTransform()->GetScale() *= 0.9f;
		_beams.push_back(beam);
	}

	_muzzle = make_shared<Transform>();

	wstring file = L"Resource/Texture/CupHead/Effect/BossExpension.png";
	_effect = make_shared<Effect>(file, Vector2(2, 2), Vector2(200, 200), 0.05f);
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(500, 500), 0.06f);
}

Vaggie_Carrot::~Vaggie_Carrot()
{
	_transform = nullptr;
}

void Vaggie_Carrot::Update()
{
	if (_mosaicBuffer->_data.value1 == 0) return;

	_collider->Update();

	_efCheck += DELTA_TIME;

	if (isDead == true)
		Dead();

	for (auto bullet : _bullets)
		bullet->Update();
	for (auto beam : _beams)
		beam->Update();
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

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_collider->Render();
}

void Vaggie_Carrot::BulletRender()
{
	for (auto bullet : _bullets)
		bullet->Render();

	for (auto beam : _beams)
		beam->Render();
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
	if (player->isDead == true) return;

	_shot += DELTA_TIME;
	_muzzle->SetPosition(Vector2(CENTER_X, 550));
	Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();

	if (_beams[0]->isActive == false && _shot >= _shotDelay)
	{
		_beams[0]->Enable();
		_beams[0]->SetFireDir(dir);
		_beams[0]->GetTransform()->SetPosition(_muzzle->GetWorldPos());

		_shot = 0.0f;
	}
	if (_beams[1]->isActive == false && _shot >= _shotDelay)
	{
		_beams[1]->Enable();
		_beams[1]->SetFireDir(dir);
		_beams[1]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
		_shot = 0.0f;
	}
	if (_beams[2]->isActive == false && _shot >= _shotDelay)
	{
		_beams[2]->Enable();
		_beams[2]->SetFireDir(dir);
		_beams[2]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
		_shot = 0.0f;
	}
	if (_beams[3]->isActive == false && _shot >= _shotDelay)
	{
		_beams[3]->Enable();
		_beams[3]->SetFireDir(dir);
		_beams[3]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
		_shot = 0.0f;
	}
	if (_beams[4]->isActive == false && _shot>= _shotDelay)
	{
		_beams[4]->Enable();
		_beams[4]->SetFireDir(dir);
		_beams[4]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
		_shot = 0.0f;
	}
}
void Vaggie_Carrot::BulletAttack(shared_ptr<Player> player)
{
	if (_curState != IDLE) return;
	if (isDead == true) return;
	if (player->isDead == true) return;

	if (_bullets[0]->isActive == false)
	{
		_muzzle->SetPosition(Vector2(CENTER_X - 200, 500));
		Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
		_bullets[0]->Enable();
		_bullets[0]->SetFireDir(dir);
		_bullets[0]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
	}
	if (_bullets[1]->isActive == false)
	{
		_muzzle->SetPosition(Vector2(CENTER_X + 200, 500));
		Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
		_bullets[1]->Enable();
		_bullets[1]->SetFireDir(dir);
		_bullets[1]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
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

	if (_efCheck >= 0.8f)
	{
		EFFECT->Play("BossExpension", Vector2(_transform->GetPos().x, _transform->GetPos().y), true);
		_efCheck = 0.0f;
	}
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
