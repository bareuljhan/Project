#include "framework.h"
#include "PuffBall.h"

PuffBall::PuffBall()
{
	_transform = make_shared<Transform>();
	_muzzle = make_shared<Transform>();

	CreateAction("PuffBall", Action::Type::LOOP);

}

PuffBall::~PuffBall()
{
	_transform = nullptr;
}

void PuffBall::Update()
{
	_sprite->Update();
	_action->Update();

	_transform->UpdateSRT();
}

void PuffBall::Render()
{
	_sprite->Render();
	_sprite->SetActionClip(_action->GetCurClip());
}

void PuffBall::Enalbe()
{
	isActive = true;
	_collider->isActive = true;
}

void PuffBall::Disable()
{
	isActive = false;
	_collider->isActive = false;
}

bool PuffBall::Collision(shared_ptr<Collider> col)
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

void PuffBall::SetFireDir(Vector2 pos)
{
}

void PuffBall::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Stage2/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/FlowerWeapons/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_action = make_shared<Action>(xml.GetClips(), actionName, type);
	_sprite = make_shared<Sprite>(srvPath, xml.AverageSize());
}
