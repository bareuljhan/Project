#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_transform = make_shared<Transform>();

	_collider = make_shared<CircleCollider>(10);
	_collider2 = make_shared<CircleCollider>(60);
	CreateAction("Bullet_Loop", Action::Type::LOOP);
	CreateAction("Special_Bullet_Loop", Action::Type::LOOP);

	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_transform);
		sprite->GetTransform()->GetScale() *= 0.8f;
		_collider->GetTransform()->SetParent(sprite->GetTransform());
		_collider2->GetTransform()->SetParent(sprite->GetTransform());
	}
	_collider->GetTransform()->GetPos().y += 60;
	_collider2->GetTransform()->GetPos().y += 150;

	wstring file = L"Resource/Texture/CupHead/Effect/bulletDeath.png";
	_effect = make_shared<Effect>(file, Vector2(2, 2), Vector2(200, 200), 0.084f);
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(80, 80), 0.1f);

	file = L"Resource/Texture/CupHead/Effect/specialEffect.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(300, 300), 0.1f);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (!isActive) return;

	if(_curState == BASIC)
		_collider->Update();
	else
		_collider2->Update();

	_delay += DELTA_TIME;

	_effect->Update();

	if (_delay >= _lifeTime)
	{
		for(auto action : _actions)
			action->Reset();
		isActive = false;
		_delay = 0.0f;
	}

	_transform->GetPos() += _direction * _speed * DELTA_TIME;
	for (auto sprite : _sprites)
	{
		sprite->Update();
	}

	for (auto action : _actions)
		action->Update();
	_transform->Update();
}

void Bullet::Render()
{
	if (!isActive) return;

	_effect->Render();

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	if (_curState == BASIC)
		_collider->Render();
	else
		_collider2->Render();
}

void Bullet::SetPostion(Vector2 pos)
{
	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->GetPos() = pos;
	}
}

void Bullet::SetFireDir(Vector2 dir)
{
	for(auto action : _actions)
		action->Play();
	
	_direction = dir.NormalVector2();

	for(auto sprite : _sprites)
		sprite->GetTransform()->GetAngle() = dir.Angle() - PI * 0.5f;
}

void Bullet::Enable()
{
	_collider->isActive = true;
	_collider2->isActive = true;
	isActive = true;
	_delay = 0.0f;
}

void Bullet::Disable()
{
	_collider->isActive = false;
	_collider2->isActive = false;
	isActive = false;
	_delay = 0.0f;
}

bool Bullet::Collision(shared_ptr<Collider> col)
{
	if (isActive == false) return false;
	bool result = false;

	if (_curState == BASIC)
		result = _collider->IsCollision(col);
	else if (_curState == SPECIAL)
		result = _collider2->IsCollision(col);

	if (result == true)
	{
		Disable();
		if (_curState == BASIC)
		{
			EFFECT->Play("bulletDeath", _collider->GetTransform()->GetWorldPos(), false);
		}
		else if (_curState == SPECIAL)
		{
			EFFECT->Play("specialEffect", _collider2->GetTransform()->GetWorldPos(), false);

		}
	}

	return result;
}

void Bullet::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Bullet::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Bullet/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "BULLET_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
