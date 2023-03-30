#include "framework.h"
#include "ReadyScreen.h"

ReadyScreen::ReadyScreen()
{
	CreateAction("Ready", Action::Type::END);

	_sprite->GetTransform()->SetPosition(CENTER);
	_sprite->GetTransform()->SetScale(Vector2(2.5f, 2.5f));

	_action->Ready(std::bind(&ReadyScreen::SetEnd, this));

	_action->Play();
}

ReadyScreen::~ReadyScreen()
{
}

void ReadyScreen::Update()
{
	_sprite->Update();
	_action->Update();
}

void ReadyScreen::Render()
{
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void ReadyScreen::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Screen/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Screen/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_action = make_shared<Action>(xml.GetClips(), actionName, type);
	_sprite = make_shared<Sprite>(srvPath, xml.AverageSize());
}
