#include "framework.h"
#include "HandATK.h"

HandATK::HandATK()
{
	_transform = make_shared<Transform>();

	CreateAction("AcornSpin", Action::Type::END);
	CreateAction("AcornShoot", Action::Type::LOOP);
	CreateAction("FlowerBoomerang", Action::Type::PINGPONG);

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_collider = make_shared<CircleCollider>(40);
	_collider->GetTransform()->SetParent(_transform);

	_oldState = BALL;
	_actions[_curState]->Play();

	wstring file = L"Resource/Texture/CupHead/Effect/AcornPuff.png";
	_effect = make_shared<Effect>(file, Vector2(2, 2), Vector2(200, 200), 0.05f);
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(50, 40), 0.05f);
}

HandATK::~HandATK()
{	
	_transform = nullptr;
}

void HandATK::Update()
{
	if (isActive == false) return;

	_collider->Update();

	if (_curState == BALL && _actions[_curState]->isEnd == true)
	{
		SetAction(BALLATK);
		EFFECT->Play("AcornPuff", _transform->GetPos(), false);
	}

	if (_curState == BALLATK)
	{
		Vector2 temp = _transform->GetPos();
		temp += _direction * _speed * DELTA_TIME;
		_transform->SetPosition(temp);
	}

	if (_curState == BOOMERANG)
	{
		_delay += DELTA_TIME;
		Vector2 temp = _transform->GetPos();

		if (_delay < 3.0f)
		{
			temp.x += _direction.x * _speed * DELTA_TIME;
			_transform->SetPosition(temp);
		}
		else
		{
			temp.x -= _direction.x * _speed * DELTA_TIME;
			_transform->SetPosition(temp);
		}
	}
	for (auto sprite : _sprites)
		sprite->Update();
	for (auto action : _actions)
		action->Update();
}

void HandATK::Render()
{
	if (isActive == false) return;

	_sprites[_curState]->Render();
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());

	_collider->Render();
}

void HandATK::Enable()
{
	_collider->isActive = true;
	isActive = true;
}

void HandATK::Disable()
{
	_collider->isActive = false;
	isActive = false;
}

void HandATK::SetFireDir(Vector2 dir)
{
	for (auto action : _actions)
		action->Play();

	_direction = dir.NormalVector2();
}

bool HandATK::Collision(shared_ptr<Collider> col)
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

void HandATK::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void HandATK::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "Monster_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}