#include "framework.h"
#include "Spudder_Bullet.h"

Spudder_Bullet::Spudder_Bullet()
{
	_transform = make_shared<Transform>();

	CreateAction("Spudder_Bullet", Action::Type::LOOP);

	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_transform);
	}

	_collider = make_shared<CircleCollider>(50);
	_collider->GetTransform()->SetParent(_transform);
}

Spudder_Bullet::~Spudder_Bullet()
{
}

void Spudder_Bullet::Update()
{
	if (!isActive) return;

	_collider->Update();

	_delay += DELTA_TIME;

	if (_delay >= _lifeTime)
	{
		for (auto action : _actions)
			action->Reset();
		isActive = false;
		_delay = 0.0f;
	}

	Vector2 temp = _transform->GetPos();
	temp += _direction * _speed * DELTA_TIME;
	_transform->SetPosition(temp);

	for (auto sprite : _sprites)
	{
		sprite->Update();
	}

	for (auto action : _actions)
		action->Update();
	_transform->Update();
}

void Spudder_Bullet::Render()
{
	if (!isActive) return;

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
	_collider->Render();
}

void Spudder_Bullet::SetFireDir(Vector2 dir)
{
	for (auto action : _actions)
		action->Play();

	_direction = dir.NormalVector2();

	for (auto sprite : _sprites)
		sprite->GetTransform()->GetAngle() = dir.Angle() - PI * 0.5f;
}

void Spudder_Bullet::Enable()
{
	_collider->isActive = true;
	isActive = true;
	_delay = 0.0f;
}

void Spudder_Bullet::Disable()
{
	_collider->isActive = false;
	isActive = false;
	_delay = 0.0f;
}

bool Spudder_Bullet::Collision(shared_ptr<Collider> col)
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

void Spudder_Bullet::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Spudder_Bullet::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "BULLET_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
