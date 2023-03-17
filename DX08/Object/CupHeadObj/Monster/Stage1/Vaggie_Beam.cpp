#include "framework.h"
#include "Vaggie_Beam.h"

Vaggie_Beam::Vaggie_Beam()
{
	_transform = make_shared<Transform>();

	CreateAction("CarrotBeam_Bullet", Action::Type::LOOP);
	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_collider = make_shared<CircleCollider>(50);
	_collider->GetTransform()->SetParent(_transform);

	_actions[BEAM]->Play();
}

Vaggie_Beam::~Vaggie_Beam()
{
	_transform = nullptr;
}

void Vaggie_Beam::Update()
{
	if (isActive == false) return;
	
	_lifeTime += DELTA_TIME;

	if (_lifeTime >= _delay)
	{
		for (auto action : _actions)
			action->Reset();
		isActive = false;
		_lifeTime = 0.0f;
	}
	_collider->Update();

	for (auto action : _actions)
		action->Update();
	for (auto sprite : _sprites)
		sprite->Update();

	Vector2 temp = _transform->GetPos();
	temp += _direction * 5;
	_transform->SetPosition(temp);

	_transform->UpdateSRT();
}

void Vaggie_Beam::Render()
{

	if (isActive == false) return;
	
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_collider->Render();
}

void Vaggie_Beam::SetFireDir(Vector2 dir)
{
	for (auto action : _actions)
		action->Play();

	_direction = dir.NormalVector2();

	this->GetTransform()->GetAngle() = dir.Angle() + PI * 0.5f;
}

void Vaggie_Beam::Enable()
{
	_collider->isActive = true;
	isActive = true;
}

void Vaggie_Beam::Disable()
{
	_collider->isActive = false;
	//isActive = false;
}

void Vaggie_Beam::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

bool Vaggie_Beam::Collision(shared_ptr<Collider> col)
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

void Vaggie_Beam::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
