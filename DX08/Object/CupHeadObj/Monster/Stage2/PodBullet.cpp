#include "framework.h"
#include "PodBullet.h"

PodBullet::PodBullet()
{
	_transform = make_shared<Transform>();

	CreateAction("pod_one", Action::Type::PINGPONG);
	CreateAction("pod_two", Action::Type::PINGPONG);
	CreateAction("pod_three", Action::Type::PINGPONG);
	
	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_transform);
	}

	for (int i = 0; i < 2; i++)
	{
		shared_ptr<Chomper> chomper = make_shared<Chomper>();
		_chompers.push_back(chomper);
	}

	_vine = make_shared<Vine>();

	_collider = make_shared<CircleCollider>(30);
	_collider->GetTransform()->SetParent(_transform);

	_oldState = BLUE;
	_actions[_curState]->Play();

	wstring file = L"Resource/Texture/CupHead/Effect/Vine.png";
	_effect = make_shared<Effect>(file, Vector2(2, 2), Vector2(200, 200), 0.05f);
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(50, 200), 0.05f);

	file = L"Resource/Texture/CupHead/Effect/ChomperDeath.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(80, 80), 0.05f);

	file = L"Resource/Texture/CupHead/Effect/venusDeath.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(80, 80), 0.05f);
}

PodBullet::~PodBullet()
{
	_transform = nullptr;
}

void PodBullet::Update()
{
	if (isActive == false) return;

	for(auto sprite : _sprites)
		sprite->Update();
	for(auto action : _actions)
		action->Update();

	_chompers[0]->Update();
	_chompers[1]->Update();
	_vine->Update();

	ChomperSpawn();
	
	Vector2 temp = _transform->GetPos();
	temp.y -= _direction.y * _speed * DELTA_TIME;
	_transform->SetPosition(temp);

	_transform->UpdateSRT();
}

void PodBullet::Render()
{
	if (isActive == false) return;

	_sprites[_curState]->Render();
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());

	_chompers[0]->Render();
	_chompers[1]->Render();
	_vine->Render();

}

void PodBullet::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void PodBullet::ChomperSpawn()
{
	if (isFloorOne == false)
		_chompers[0]->Disable();
	if (isFloorThr == false)
		_chompers[1]->Disable();
	if (isFloorTwo == false)
		_vine->Disable();


	if (isFloorOne == true && _curState == BLUE)
	{
		_chomperDelay += DELTA_TIME;
		_chompers[0]->Enable();
	}
	if (isFloorThr == true && _curState == PURPLE)
	{
		_chomperDelayTwo += DELTA_TIME;
		_chompers[1]->GetTransform()->SetPosition(Vector2(300, 150));
		_chompers[1]->Enable();
	}
	if (isFloorTwo == true && _curState == RED)
	{
		if(_vineDelay == 0)
			EFFECT->Play("Vine", Vector2(_vine->GetTransform()->GetPos().x, _vine->GetTransform()->GetPos().y - 120), false);
		_vineDelay += DELTA_TIME;
		if(_vineDelay >= 0.6)
			_vine->Enable();
	}

	if (_chomperDelay >= 3.5f)
	{
		EFFECT->Play("ChomperDeath", _chompers[0]->GetTransform()->GetPos(), false);
		_chompers[0]->Disable();
		isFloorOne = false;
		_chomperDelay = 0.0f;
	}
	if (_chomperDelayTwo >= 3.5f)
	{
		EFFECT->Play("ChomperDeath", _chompers[1]->GetTransform()->GetPos(), false);
		_chompers[1]->Disable();
		isFloorThr = false;
		_chomperDelayTwo = 0.0f;
	}	
	if (_vineDelay >= 4.5f)
	{
		_vine->Disable();
		EFFECT->Play("venusDeath", _vine->GetTransform()->GetPos(), false);
		isFloorTwo = false;
		_vineDelay = 0.0f;
		_vine->GetTransform()->SetPosition(Vector2(500, 220));
	}
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
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}