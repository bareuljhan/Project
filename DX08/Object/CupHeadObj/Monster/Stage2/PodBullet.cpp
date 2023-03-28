#include "framework.h"
#include "PodBullet.h"

PodBullet::PodBullet()
{
	_transform = make_shared<Transform>();

	CreateAction("pod_one", Action::Type::PINGPONG);

	_sprite->GetTransform()->SetParent(_transform);

	_collider = make_shared<CircleCollider>(30);
	_collider->GetTransform()->SetParent(_transform);

	_action->Play();
}

PodBullet::~PodBullet()
{
	_transform = nullptr;
}

void PodBullet::Update()
{
	if (isActive == false) return;

	_sprite->Update();
	_action->Update();
	
	Vector2 temp = _transform->GetPos();
	temp.y -= _direction.y * _speed * DELTA_TIME;
	_transform->SetPosition(temp);

	_transform->UpdateSRT();
}

void PodBullet::Render()
{
	if (isActive == false) return;

	_sprite->Render();
	_sprite->SetActionClip(_action->GetCurClip());
}

void PodBullet::Enable()
{
	isActive = true;
	_collider->isActive = true;
}

void PodBullet::Disable()
{
	isActive = false;
	_collider->isActive = false;
}

bool PodBullet::Collision(shared_ptr<Collider> col)
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

void PodBullet::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Stage2/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/FlowerWeapons/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_action = make_shared<Action>(xml.GetClips(), actionName, type);
	_sprite = make_shared<Sprite>(srvPath, xml.AverageSize());
}