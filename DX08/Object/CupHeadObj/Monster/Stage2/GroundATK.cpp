#include "framework.h"
#include "GroundATK.h"

GroundATK::GroundATK()
{
	_transform = make_shared<Transform>();

	CreateAction("frontVine_intro", Action::Type::END);
	CreateAction("frontVine_Idle", Action::Type::PINGPONG);
	CreateAction("frontVine_ATK", Action::Type::END);

	_actions[INTRO_A]->VineRespawn(std::bind(&GroundATK::SetIDLE, this));
	_collider = make_shared<RectCollider>(Vector2(60, 100));
	_collider->GetTransform()->SetParent(_transform);

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_oldState = INTRO_A;
	_actions[_curState]->Play();
}

GroundATK::~GroundATK()
{
	_transform = nullptr;
}

void GroundATK::Update()
{
	if (isActive == false) return;
	if (_curState == IDLE_A)
		_delay += DELTA_TIME;
	
	_collider->Update();

	ATKPattern();
	for (auto sprite : _sprites)
		sprite->Update();
	for (auto action : _actions)
		action->Update();

	_transform->UpdateSRT();
}

void GroundATK::Render()
{
	if (isActive == false) return;
	_sprites[_curState]->Render();
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());

	_collider->Render();
}

void GroundATK::SetIDLE()
{
	SetAction(IDLE_A);
	_sprites[IDLE_A]->GetTransform()->SetScale(Vector2(0.8f, 0.8f));
}

void GroundATK::ATKPattern()
{
	if (_curState == IDLE_A && _delay >= 1.3f && _actions[_curState]->isEnd == true)
	{
		SetAction(ATK_A);
		_collider->GetTransform()->SetPosition(Vector2(0, 150));
		_actions[_curState]->isEnd = false;
	}
	if (_curState == ATK_A && _actions[_curState]->isEnd == true)
	{
		Disable();
		_collider->GetTransform()->SetPosition(Vector2(0, 0));
		_actions[_curState]->isEnd = false;
		_delay = 0.0f;
	}
}

void GroundATK::Enable()
{
	isActive = true;
	_collider->isActive = true;
}

void GroundATK::Disable()
{
	isActive = false;
	_collider->isActive = false;
}

bool GroundATK::Collision(shared_ptr<Collider> col)
{
	if (isActive == false)
		return false;

	bool result = _collider->IsCollision(col);

	return result;
}

void GroundATK::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void GroundATK::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
