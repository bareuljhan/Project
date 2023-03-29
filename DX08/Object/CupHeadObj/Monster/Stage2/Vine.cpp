#include "framework.h"
#include "Vine.h"

Vine::Vine()
{
	_transform = make_shared<Transform>();

	CreateAction("venus", Action::Type::END);
	CreateAction("venusATK", Action::Type::LOOP);

	_actions[IDLE]->VineRespawn(std::bind(&Vine::SetAttack, this));

	_transform->SetPosition(Vector2(500, 220));
	
	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);


	_collider = make_shared<CircleCollider>(40);
	_collider->GetTransform()->SetParent(_transform);

	_oldState = IDLE;
	_actions[IDLE]->Play();
}

Vine::~Vine()
{
	_transform = nullptr;
}

void Vine::Update()
{
	if (isActive == false) return;
	
	_collider->Update();

	if (_curState == ATK)
	{
		Vector2 temp = _transform->GetPos();
		temp += _direction * _speed * DELTA_TIME;
		_transform->SetPosition(temp);
	}
	for (auto sprite : _sprites)
		sprite->Update();
	for (auto action : _actions)
		action->Update();
}

void Vine::Render()
{
	if (isActive == false) return;

	_sprites[_curState]->Render();
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());

	_collider->Render();
}

void Vine::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Vine::Enable()
{
	isActive = true;
	_collider->isActive = true;
}

void Vine::Disable()
{
	isActive = false;
	_collider->isActive = false;
}

void Vine::SetAttack()
{
	SetAction(ATK);
}

bool Vine::Collision(shared_ptr<Collider> col)
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

void Vine::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
