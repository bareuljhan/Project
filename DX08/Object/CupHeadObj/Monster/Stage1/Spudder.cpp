#include "framework.h"
#include "Spudder.h"

Spudder::Spudder()
{
	_transform = make_shared<Transform>();


	_support = make_shared<Quad>(L"Resource/Texture/CupHead/Monster/support.png");
	_support->GetTransform()->GetScale() *= 1.1f;
	_support->GetTransform()->GetPos() = CENTER;
	_support->GetTransform()->GetPos().x += 400;
	_support->GetTransform()->GetPos().y -= 100;

	CreateAction("Spawn", Action::Type::END);
	CreateAction("Spudder", Action::Type::LOOP);

	_actions[1]->SetCallBack_Target(std::bind(&Spudder::AttackToPlayer, this));

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

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
	_muzzle->GetPos().x -= 250;
	_muzzle->GetPos().y -= 120;

	_collider = make_shared<RectCollider>(Vector2(285, 400));
	_collider->GetTransform()->SetParent(_transform);
}

Spudder::~Spudder()
{
}

void Spudder::Update()
{
	if (_hp == 0.0f) return;
	_collider->Update();

	for (auto bullet : _bullets)
		bullet->Update();

	a += DELTA_TIME;

	if (a > 2.0)
	{
		Init();
	}

	_transform->Update();

	
	for (auto sprite : _sprites)
		sprite->Update();

	for (auto action : _actions)
		action->Update();
	

}

void Spudder::Render()
{
	if (_hp == 0.0f) return;

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

void Spudder::AttackToPlayer()
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
			bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
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
		/*SetAction(DIE);*/
	}
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
