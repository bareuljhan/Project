#include "framework.h"
#include "Vaggie_Bullet.h"

Vaggie_Bullet::Vaggie_Bullet()
{
	_transform = make_shared<Transform>();

	CreateAction("carrotBullet", Action::Type::LOOP);
	CreateAction("bulletDestroy", Action::Type::END);

	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_transform);
	}
	_sprites[1]->GetTransform()->GetScale() *= 0.6f;

	_collider = make_shared<CircleCollider>(40);
	_collider->GetTransform()->SetParent(_transform);

	_oldState = State::BULLET;
	_actions[State::BULLET]->Play();
}

Vaggie_Bullet::~Vaggie_Bullet()
{
}

void Vaggie_Bullet::Update()
{
	if (!isActive) return;
	
	Destroy();

	_lifeTime += DELTA_TIME;

	if ( _lifeTime >= _delay || isDestroy == true)
	{
		for (auto action : _actions)
			action->Reset();
		isActive = false;
		_lifeTime = 0.0f;
		_hp = 30.0f;
	}


	Vector2 temp = _transform->GetPos();
	temp += _direction * _speed * DELTA_TIME;	
	_transform->SetPosition(temp);

	_collider->Update();
	for (auto action : _actions)
		action->Update();
	for (auto sprite : _sprites)
		sprite->Update();
	
	_transform->Update();
	
}

void Vaggie_Bullet::Render()
{
	if (!isActive) return;

	if (_curState != NONE)
	{
		_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
		_sprites[_curState]->Render();
		_collider->Render();
	}
}

void Vaggie_Bullet::SetFireDir(Vector2 dir)
{
	for (auto action : _actions)
		action->Play();

	_direction = dir.NormalVector2();

	this->GetTransform()->GetAngle() = dir.Angle() +  PI * 0.5f;
}

void Vaggie_Bullet::Enable()
{
	SetAction(BULLET);
	_hp = 30.0f;
	_collider->isActive = true;
	isActive = true;
	isDestroy = false;
}

void Vaggie_Bullet::Disable()
{
	_collider->isActive = false;
	isActive = false;
	isDestroy = true;
}

void Vaggie_Bullet::Destroy()
{
	if (_hp != 0.0f) return;
	
	_b += DELTA_TIME;

	SetAction(State::DESTROY);
	
	if (_a <= _b)
	{
		isActive = false;
		isDestroy = true;
		_b = 0.0f;
	}
}

void Vaggie_Bullet::GetDamage(float amount)
{
	if (amount <= 0) return;

	_hp -= amount;

	if (_hp <= 0)
	{
		_hp = 0.0f;
		_collider->isActive = false;
	}
}

bool Vaggie_Bullet::Collision(shared_ptr<Collider> col)
{
	if (isActive == false)
		return false;

	bool result = _collider->IsCollision(col);

	if (result == true)
	{
		Disable();
	}

	return result;
}

void Vaggie_Bullet::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Vaggie_Bullet::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "BULLET_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));

}