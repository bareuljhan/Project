#include "framework.h"
#include "PuffBall.h"

PuffBall::PuffBall()
{
	_transform = make_shared<Transform>();
	_muzzle = make_shared<Transform>();

	CreateAction("PuffBall", Action::Type::LOOP);

	_transform->SetPosition(Vector2(1000, 400));

	_collider = make_shared<CircleCollider>(40);
	_collider->GetTransform()->SetParent(_transform);

	_sprite->GetTransform()->SetParent(_transform);
	_action->Play();
}

PuffBall::~PuffBall()
{
	_transform = nullptr;
}

void PuffBall::Update()
{
	if (isActive == false) return;

	_delay += DELTA_TIME;

	_collider->Update();

	_sprite->Update();
	_action->Update();
	
	if (_delay <= 0.4f)
	{
		Vector2 temp = _transform->GetPos();
		temp += _direction * _speed * DELTA_TIME;
		_transform->SetPosition(temp);
	}
	else if (_delay > 0.4 && _delay <= 0.8f)
	{
		Vector2 temp = _transform->GetPos();
		temp += _directionDW * _speed * DELTA_TIME;
		_transform->SetPosition(temp);
	}
	else
		_delay = 0.0f;

	_transform->UpdateSRT();
}

void PuffBall::Render()
{
	if (isActive == false) return;
	
	_sprite->Render();
	_sprite->SetActionClip(_action->GetCurClip());

	_collider->Render();
}

void PuffBall::Enable()
{
	isActive = true;
	_collider->isActive = true;
	_delay = 0.0f;
}

void PuffBall::Disable()
{
	isActive = false;
	_collider->isActive = false;
	_delay = 0.0f;
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
