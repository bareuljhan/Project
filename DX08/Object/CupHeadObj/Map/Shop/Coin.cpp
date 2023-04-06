#include "framework.h"
#include "Coin.h"

Coin::Coin()
{
	_transform = make_shared<Transform>();

	CreateAction("Coin", Action::Type::LOOP);

	_sprite->GetTransform()->SetParent(_transform);
	_action->Play();
}

Coin::~Coin()
{
	_transform = nullptr;
}

void Coin::Update()
{
	_sprite->Update();
	_action->Update();

	_transform->UpdateSRT();
}

void Coin::Render()
{
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void Coin::PostRender()
{
}

void Coin::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Shop/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Shop/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_action = make_shared<Action>(xml.GetClips(), actionName, type);
	_sprite = make_shared<Sprite>(srvPath, xml.AverageSize());
}