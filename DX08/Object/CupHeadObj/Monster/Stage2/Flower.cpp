#include "framework.h"
#include "Flower.h"

Flower::Flower()
{
	_transform = make_shared<Transform>();

	CreateAction("FlowerIntro", Action::Type::END);
	CreateAction("FlowerIdle", Action::Type::PINGPONG);
	CreateAction("FlowerGatling", Action::Type::END);
	CreateAction("FlowerHand", Action::Type::END);

	_actions[GATLING]->PodEffect(std::bind(&Flower::PlayEffect, this));

	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_transform);
		sprite->GetTransform()->SetPosition(Vector2(0, 50));
		sprite->GetTransform()->SetScale(Vector2(0.9f, 0.9f));
	}

	_hitCollider = make_shared<RectCollider>(Vector2(200, 200));
	_hitCollider->GetTransform()->SetParent(_transform);
	_hitCollider->GetTransform()->SetPosition(Vector2(40, 150));

	_transform->SetPosition(Vector2(1000, 300));

	_podBullet = make_shared<PodBullet>();

	_oldState = INTRO;
	_curState = INTRO;

	_actions[_curState]->Play();

	wstring file = L"Resource/Texture/CupHead/Monster/GatlingFX.png";
	_effect = make_shared<Effect>(file, Vector2(2, 2), Vector2(200, 200), 0.05f);
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(200, 200), 0.1f);
}

Flower::~Flower()
{
}

void Flower::Update()
{
	AttackPattern();

	for (auto action : _actions)
		action->Update();
	for (auto sprite : _sprites)
		sprite->Update();

	_transform->UpdateSRT();
}

void Flower::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	if(_curState != INTRO)
		_hitCollider->Render();
}

void Flower::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Flower::AttackPattern()
{
	if (_curState == INTRO && _actions[_curState]->isEnd == true)
	{
		SetIDLE();
		_hitCollider->Update();
		_actions[_curState]->isEnd = false;
	}
	if (_curState == IDLE && _actions[_curState]->isEnd == true)
	{
		SetGatling();
		_actions[_curState]->isEnd = false;
	}
	if (_curState == GATLING && _actions[_curState]->isEnd == true)
	{
		SetHandATK();
		_actions[_curState]->isEnd = false;
	}
	if (_curState == HANDATK && _actions[_curState]->isEnd == true)
	{
		SetIDLE();
		_actions[_curState]->isEnd = false;
	}
}

void Flower::SetIDLE()
{
	SetAction(State::IDLE);
}

void Flower::SetGatling()
{
	SetAction(State::GATLING);
}

void Flower::SetHandATK()
{
	SetAction(State::HANDATK);
}

void Flower::PlayEffect()
{
	isUpdate = true;
	EFFECT->Play("GatlingFX", Vector2(950, 650), true);
}

void Flower::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
