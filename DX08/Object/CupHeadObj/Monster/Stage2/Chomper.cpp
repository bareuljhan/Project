#include "framework.h"
#include "Chomper.h"

Chomper::Chomper()
{
	_transform = make_shared<Transform>();

	CreateAction("FlowerChomper", Action::Type::LOOP);
}

Chomper::~Chomper()
{
	_transform = nullptr;
}

void Chomper::Update()
{
	_action->Update();
	_sprite->Update();
}

void Chomper::Render()
{
	_sprite->Render();
	_sprite->SetActionClip(_action->GetCurClip());
}

void Chomper::Enable()
{
	isActive = true;
	_collider->isActive = true;
}

void Chomper::Disable()
{
	isActive = false;
	_collider->isActive = false;
}

void Chomper::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_action = make_shared<Action>(xml.GetClips(), actionName, type);
	_sprite = make_shared<Sprite>(srvPath, xml.AverageSize());
}
