#include "framework.h"
#include "WinScreen.h"

WinScreen::WinScreen()
{
	CreateAction("KnockOut", Action::Type::END);

	_sprite->GetTransform()->SetPosition(CENTER);
	_sprite->GetTransform()->SetScale(Vector2(2.5f, 2.5f));
	_action->CallBack_TS(std::bind(&WinScreen::SetEnd, this));
	
	_action->Play();
}

WinScreen::~WinScreen()
{
}

void WinScreen::Update()
{
	_sprite->Update();
	_action->Update();
}

void WinScreen::Render()
{
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void WinScreen::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Screen/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Screen/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_action = make_shared<Action>(xml.GetClips(), actionName, type);
	_sprite = make_shared<Sprite>(srvPath, xml.AverageSize());
}
