#include "framework.h"
#include "Chomper.h"

Chomper::Chomper()
{
	_transform = make_shared<Transform>();

	CreateAction("FlowerChomper", Action::Type::LOOP);

	_collider = make_shared<CircleCollider>(40);
	_collider->GetTransform()->SetParent(_transform);
	
	_sprite->GetTransform()->SetParent(_transform);

	_transform->SetPosition(Vector2(750, 150));
	_action->Play();
}

Chomper::~Chomper()
{
	_transform = nullptr;
}

void Chomper::Update()
{
	if (isActive == false) return;
	
	_collider->Update();
	_action->Update();
	_sprite->Update();
}

void Chomper::Render()
{
	if (isActive == false) return;

	_sprite->Render();
	_sprite->SetActionClip(_action->GetCurClip());
	_collider->Render();
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

bool Chomper::Collision(shared_ptr<Collider> col)
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
