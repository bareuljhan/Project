#include "framework.h"
#include "OverWorld_Player.h"

OverWorld_Player::OverWorld_Player()
{
	_transform = make_shared<Transform>();

	CreateAction("OverWorld_IDLE", Action::Type::LOOP);
	//CreateAction("OverWorld_RUN", Action::Type::LOOP);
	//CreateAction("OverWorld_UP", Action::Type::LOOP);
	//CreateAction("OverWorld_DOWN", Action::Type::LOOP);
	//CreateAction("OverWorld_WD", Action::Type::LOOP);
	//CreateAction("OverWorld_SD", Action::Type::LOOP);
	//CreateAction("OverWorld_CLEAR", Action::Type::END);

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);
	_oldState = State::IDLE;
	_actions[State::IDLE]->Play();
}

OverWorld_Player::~OverWorld_Player()
{
}

void OverWorld_Player::SetRight()
{
	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 0;
	}
}

void OverWorld_Player::SetLeft()
{
	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 1;
	}
}

void OverWorld_Player::Update()
{

	if (KEY_DOWN(VK_LBUTTON))
	{
		AStar(_transform->GetPos(), MOUSE_POS);
	}

	for (auto sprite : _sprites)
		sprite->Update();

	for (auto action : _actions)
		action->Update();


	if (_transform->GetPos().x - _endPos.x <= 0 || _transform->GetPos().y - _endPos.y <= 0 && isRun == true)
	{
		Vector2 temp = _transform->GetPos();
		temp += _direction.NormalVector2() * _speed * DELTA_TIME;
		_transform->SetPosition(temp);
	}


	_transform->UpdateSRT();
}

void OverWorld_Player::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
}

void OverWorld_Player::Init()
{
}

void OverWorld_Player::AStar(Vector2 start, Vector2 end)
{
}

void OverWorld_Player::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void OverWorld_Player::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/OverWorld/Character/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Character/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
