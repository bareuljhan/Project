#include "framework.h"
#include "PodBullet.h"

PodBullet::PodBullet()
{
	_transform = make_shared<Transform>();

	CreateAction("pod_one", Action::Type::PINGPONG);
	CreateAction("pod_two", Action::Type::PINGPONG);
	CreateAction("pod_three", Action::Type::PINGPONG);

	_sprites[BLUE]->GetTransform()->SetPosition(Vector2(CENTER_X - 100, 700));
	_sprites[BLUE]->GetTransform()->SetParent(_transform);
	_sprites[RED]->GetTransform()->SetPosition(Vector2(CENTER_X + 400, 900));
	_sprites[RED]->GetTransform()->SetParent(_transform);
	_sprites[PURPLE]->GetTransform()->SetPosition(Vector2(200, 800));
	_sprites[PURPLE]->GetTransform()->SetParent(_transform);

	_collider1 = make_shared<CircleCollider>(30);
	_collider1->GetTransform()->SetParent(_sprites[0]->GetTransform());

	_collider2 = make_shared<CircleCollider>(30);
	_collider2->GetTransform()->SetParent(_sprites[1]->GetTransform());

	_collider3 = make_shared<CircleCollider>(30);
	_collider3->GetTransform()->SetParent(_sprites[2]->GetTransform());

	_colliders.push_back(_collider1);
	_colliders.push_back(_collider2);
	_colliders.push_back(_collider3);

	_actions[BLUE]->Play();
	_actions[RED]->Play();
	_actions[PURPLE]->Play();

	_chomper = make_shared<Chomper>();
	//for (int i = 0; i < 2; i++)
	//{
	//	shared_ptr<Vine> vine = make_shared<Vine>();
	//	_vines.push_back(vine);
	//}
	//_vines[0]->GetTransform()->SetParent(_sprites[RED]->GetTransform());
	//_vines[1]->GetTransform()->SetParent(_sprites[PURPLE]->GetTransform());
}

PodBullet::~PodBullet()
{
}

void PodBullet::Update()
{
	_shotDelay += DELTA_TIME;

	_collider1->Update();
	_collider2->Update();
	_collider3->Update();

	if (isActive[0] != false)
	{
		_sprites[0]->Update();
		_actions[0]->Update();

		Vector2 temp = _transform->GetPos();
		temp.y -= _bulletSpeed * DELTA_TIME;
		_transform->SetPosition(temp);
	}
	if (isActive[1] != false)
	{
		_sprites[1]->Update();
		_actions[1]->Update();

		Vector2 temp = _transform->GetPos();
		temp.y -= _bulletSpeed * DELTA_TIME;
		_transform->SetPosition(temp);
	}
	if (isActive[2] != false)
	{
		_sprites[2]->Update();
		_actions[2]->Update();

		Vector2 temp = _transform->GetPos();
		temp.y -= _bulletSpeed * DELTA_TIME;
		_transform->SetPosition(temp);
	}
	if (isFloorOne == true)
		_chomper->Update();
	//if (isFloorTwo == true)
	//	_vines[0]->Update();
	//if (isFloorThr == true)
	//	_vines[1]->Update();
		
	_transform->UpdateSRT();
}

void PodBullet::Render()
{
	if (isActive[0] != false)
	{
		_sprites[0]->Render();
		_sprites[0]->SetActionClip(_actions[0]->GetCurClip());
	}
	if (isActive[1] != false)
	{
		_sprites[1]->Render();
		_sprites[1]->SetActionClip(_actions[1]->GetCurClip());
	}
	if (isActive[2] != false)
	{
		_sprites[2]->Render();
		_sprites[2]->SetActionClip(_actions[2]->GetCurClip());
	}
	_collider1->Render();
	_collider2->Render();
	_collider3->Render();
}

void PodBullet::Enable(int index)
{
	_colliders[index]->isActive = true;
	isActive[index] = true;
	isFloorOne = true;
	isFloorTwo = true;
	isFloorThr = true;
}

void PodBullet::Disable(int index)
{
	_colliders[index]->isActive = false;
	isActive[index] = false;
}

bool PodBullet::Collision(shared_ptr<Collider> col, int index)
{
	if (isActive[index] == false)
		return false;

	bool result = _colliders[index]->IsCollision(col);

	if (result == true)
	{
		Disable(index);
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