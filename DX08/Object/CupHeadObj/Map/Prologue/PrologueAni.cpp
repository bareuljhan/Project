#include "framework.h"
#include "PrologueAni.h"

PrologueAni::PrologueAni()
{
	CreateAction("Intro1", Action::Type::END);
	CreateAction("Intro2", Action::Type::END);
	
	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetPosition(CENTER);
		sprite->GetTransform()->GetScale() *= 0.9f;
	}

	_oldState == State::ONE;
	_actions[State::ONE]->Play();

	_actions[0]->NextScreen(std::bind(&PrologueAni::SetNext, this));
	_actions[1]->NextScreen(std::bind(&PrologueAni::SetEnd, this));
}

PrologueAni::~PrologueAni()
{
}

void PrologueAni::Update()
{
	for(auto action : _actions)
		action->Update();
	for(auto sprite : _sprites)
		sprite->Update();
}

void PrologueAni::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
}

void PrologueAni::SetNext()
{
	_oldState = ONE;
	_curState = TWO;
	SetAction(State::TWO);
}

void PrologueAni::SetEnd()
{
	isEnd = true;
}

void PrologueAni::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void PrologueAni::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Prologue/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Prologue/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "Prologue" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
