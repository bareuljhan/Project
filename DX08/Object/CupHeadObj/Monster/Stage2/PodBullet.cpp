#include "framework.h"
#include "PodBullet.h"

PodBullet::PodBullet()
{
	_transform = make_shared<Transform>();

	CreateAction("pod_one", Action::Type::PINGPONG);
	CreateAction("pod_two", Action::Type::PINGPONG);
	CreateAction("pod_three", Action::Type::PINGPONG);
	
	_sprites[0]->GetTransform()->SetPosition(Vector2(CENTER_X - 100, 700));
	_sprites[0]->GetTransform()->SetParent(_transform);
	_sprites[1]->GetTransform()->SetPosition(Vector2(CENTER_X + 400, 700));
	_sprites[1]->GetTransform()->SetParent(_transform);
	_sprites[2]->GetTransform()->SetPosition(Vector2( 200, 700));
	_sprites[2]->GetTransform()->SetParent(_transform);
}

PodBullet::~PodBullet()
{
}

void PodBullet::Update()
{
	for (auto sprite : _sprites)
		sprite->Update();
	for (auto action : _actions)
		action->Update();

	_transform->UpdateSRT();

	Vector2 temp = _transform->GetPos();
	temp.y -= _bulletSpeed * DELTA_TIME;

	_transform->SetPosition(temp);
}

void PodBullet::Render()
{
	for (auto sprite : _sprites)
		sprite->Render();
	_sprites[0]->SetActionClip(_actions[0]->GetCurClip());
	_sprites[1]->SetActionClip(_actions[1]->GetCurClip());
	_sprites[2]->SetActionClip(_actions[2]->GetCurClip());
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
