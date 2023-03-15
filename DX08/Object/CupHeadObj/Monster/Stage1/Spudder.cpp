#include "framework.h"
#include "Spudder.h"

Spudder::Spudder()
{
	_transform = make_shared<Transform>();


	_support = make_shared<Quad>(L"Resource/Texture/CupHead/Monster/support.png");
	_support->GetTransform()->GetScale() *= 1.1f;
	_support->GetTransform()->SetPosition(Vector2(CENTER_X+400, CENTER_Y-100));


	CreateAction("Spawn", Action::Type::END);
	CreateAction("Spudder", Action::Type::LOOP);
	CreateAction("death", Action::Type::PINGPONG);

	_actions[1]->SetCallBack_Target(std::bind(&Spudder::BeamAttack, this));

	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_transform);
	}

	_oldState = State::SPAWN;
	_actions[State::SPAWN]->Play();

	for (int i = 0; i < 4; i++)
	{
		shared_ptr<Monster_Bullet> bullet = make_shared<Monster_Bullet>();
		bullet->isActive = false;
		bullet->GetTransform()->GetScale() *= 0.8f;
		_bullets.push_back(bullet);
	}

	_muzzle = make_shared<Transform>();
	_muzzle->SetParent(_transform);
	_muzzle->SetPosition(Vector2(-250, -120));

	_collider = make_shared<RectCollider>(Vector2(285, 400));
	_collider->GetTransform()->SetParent(_transform);

	_mosaicBuffer = make_shared<CupMosaicBuffer>();
	_mosaicBuffer->_data.value1 = 3500;
}

Spudder::~Spudder()
{
}

void Spudder::Update()
{
	if (_mosaicBuffer->_data.value1 == 0)
	{
		isNextMonster = true;
		return;
	}
	if (isDead == true)
		Dead();

	_collider->Update();


	for (auto bullet : _bullets)
		bullet->Update();

	a += DELTA_TIME;

	if (a > 2.0 && isDead == false)
	{
		Init();
	}

	_transform->UpdateSRT();


	for (auto sprite : _sprites)
		sprite->Update();

	for (auto action : _actions)
		action->Update();

	_mosaicBuffer->Update();
}

void Spudder::Render()
{
	if (_mosaicBuffer->_data.value1 == 0) return;

	_mosaicBuffer->SetPSBuffer(2);

	for (auto bullet : _bullets)
		bullet->Render();

	_support->Render();

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_collider->Render();
}

void Spudder::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Spudder::SetIDLE()
{
	SetAction(State::IDLE);
}

void Spudder::Init()
{
	SetIDLE();
	_support->Update();
}

void Spudder::BeamAttack()
{
	if (isDead == true) return;
	if (_curState != IDLE) return;

	for (auto bullet : _bullets)
	{
		Vector2 dir = Vector2(-1, 0);
		dir.Normalize();
		if (bullet->isActive == false)
		{
			bullet->Enable();
			bullet->SetFireDir(dir);
			bullet->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			bullet->GetTransform()->Update();
			break; 
		}
	}
}

void Spudder::GetDamaged(float amount)
{
	if (amount <= 0) return;

	_hp -= amount;

	if (_hp <= 0)
	{
		_hp = 0.0f;
		isDead = true;
	}
}

void Spudder::Dead()
{
	for (auto sprite : _sprites)
	{
		sprite->SetPS(ADD_PS(L"Shader/MosaicPixelShader.hlsl"));
	}
	SetAction(State::DEAD);
	_mosaicBuffer->_data.value1 -= DELTA_TIME;
	_collider->isActive = false;
}

void Spudder::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "Monster_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
