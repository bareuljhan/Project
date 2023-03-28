#include "framework.h"
#include "Vine.h"

Vine::Vine()
{
	_transform = make_shared<Transform>();

	CreateAction("Venus", Action::Type::END);
	CreateAction("venusATK", Action::Type::END);

	_actions[IDLE]->VineRespawn(std::bind(&Vine::SetAttack, this));

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_collider = make_shared<CircleCollider>(40);
	_collider->GetTransform()->SetParent(_transform);

	_oldState = IDLE;
	_actions[_curState]->Play();

	wstring file = L"Resource/Texture/CupHead/Effect/Vine.png";
	_effect = make_shared<Effect>(file, Vector2(2, 2), Vector2(200, 200), 0.05f);
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(50, 100), 0.05f);
}

Vine::~Vine()
{
	_transform = nullptr;
}

void Vine::Update()
{
	if (isActive == false) return;
	for (auto sprite : _sprites)
		sprite->Update();
	for (auto action : _actions)
		action->Update();
}

void Vine::Render()
{
	if (isActive == false) return;
	_sprites[_curState]->Update();
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
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

	Vector2 temp = _transform->GetPos();
	temp += _direction * _speed * DELTA_TIME;
	_transform->SetPosition(temp);
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
