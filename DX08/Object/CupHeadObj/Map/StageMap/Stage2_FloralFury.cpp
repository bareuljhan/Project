#include "framework.h"
#include "Stage2_FloralFury.h"

Stage2_FloralFury::Stage2_FloralFury()
{
	_transform = make_shared<Transform>();

	_sky = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage2/FloralFurySky.png");
	_sky->GetTransform()->SetPosition(Vector2(CENTER_X, CENTER_Y + 150));
	_sky->GetTransform()->SetScale(Vector2(1.3f, 1.3f));
	
	_mainBG = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage2/FloralFuryBG.png");
	_mainBG->GetTransform()->SetPosition(Vector2(CENTER_X + 50, CENTER_Y));
	_mainBG->GetTransform()->SetScale(Vector2(2.1f, 2.1f));
	
	_hill = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage2/FloralFuryHills.png");
	_hill->GetTransform()->SetPosition(CENTER);
	_hill->GetTransform()->SetPosition(Vector2(CENTER_X + 30, CENTER_Y + 130));

	_cloud = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage2/FloralFuryCloud1.png");
	_cloud->GetTransform()->SetPosition(Vector2(CENTER_X - 250, CENTER_Y + 50));
	_cloud->GetTransform()->SetScale(Vector2(0.8f, 0.8f));

	_flower = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage2/FloralFuryPost.png");
	_flower->GetTransform()->SetPosition(Vector2(CENTER_X, CENTER_Y - 280));
	
	_sea = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage2/FloralFurySea.png");
	_sea->GetTransform()->SetPosition(CENTER);
	_sea->GetTransform()->SetPosition(Vector2(CENTER_X, CENTER_Y - 50));
	
	_sun = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage2/FloralFurySun.png");
	_sun->GetTransform()->SetPosition(Vector2(450, 570));

	CreateAction("waterTwinkle", Action::Type::LOOP);
	CreateAction("Platform", Action::Type::LOOP);
	CreateAction("PlatformFx", Action::Type::LOOP);
	CreateAction("Platform", Action::Type::LOOP);
	CreateAction("PlatformFx", Action::Type::LOOP);
	CreateAction("Platform", Action::Type::LOOP);
	CreateAction("PlatformFx", Action::Type::LOOP);

	_sprites[0]->GetTransform()->SetPosition(Vector2(CENTER_X, CENTER_Y - 30));
	_sprites[0]->GetTransform()->SetScale(Vector2(1.5f, 1.5f));
	_actions[0]->Play();

	_sprites[1]->GetTransform()->SetPosition(Vector2(CENTER_X - 460, CENTER_Y - 100));
	_sprites[1]->GetTransform()->SetScale(Vector2(0.8f, 0.8f));
	_actions[1]->Play();

	_sprites[2]->GetTransform()->SetPosition(Vector2(CENTER_X - 460, CENTER_Y - 130));
	_sprites[2]->GetTransform()->SetScale(Vector2(0.8f, 0.8f));
	_actions[2]->Play();

	_sprites[3]->GetTransform()->SetPosition(Vector2(CENTER_X - 210, CENTER_Y - 100));
	_sprites[3]->GetTransform()->SetScale(Vector2(0.8f, 0.8f));
	_actions[3]->Play();

	_sprites[4]->GetTransform()->SetPosition(Vector2(CENTER_X - 210, CENTER_Y - 130));
	_sprites[4]->GetTransform()->SetScale(Vector2(0.8f, 0.8f));
	_actions[4]->Play();

	_sprites[5]->GetTransform()->SetPosition(Vector2(CENTER_X + 30, CENTER_Y - 100));
	_sprites[5]->GetTransform()->SetScale(Vector2(0.8f, 0.8f));
	_actions[5]->Play();

	_sprites[6]->GetTransform()->SetPosition(Vector2(CENTER_X + 30, CENTER_Y - 130));
	_sprites[6]->GetTransform()->SetScale(Vector2(0.8f, 0.8f));
	_actions[6]->Play();

	_floorCol = make_shared<RectCollider>(Vector2(1400, 100));
	_floorCol->GetTransform()->SetParent(_transform);
	_floorCol->GetTransform()->SetPosition(Vector2(CENTER_X,30));

	_sideCol = make_shared<RectCollider>(Vector2(100, 1280));
	_sideCol->GetTransform()->SetParent(_transform);
	_sideCol->GetTransform()->SetPosition(Vector2(-45, 0));

	_sideCol2 = make_shared<RectCollider>(Vector2(100, 1280));
	_sideCol2->GetTransform()->SetParent(_transform);
	_sideCol2->GetTransform()->SetPosition(Vector2(1325, 100));

	_platformCol1 = make_shared<RectCollider>(Vector2(120, 10));
	_platformCol1->GetTransform()->SetParent(_transform);
	_platformCol1->GetTransform()->SetPosition(Vector2(CENTER_X - 460, CENTER_Y - 70));
	_platformCol2 = make_shared<RectCollider>(Vector2(120, 10));
	_platformCol2->GetTransform()->SetParent(_transform);
	_platformCol2->GetTransform()->SetPosition(Vector2(CENTER_X - 210, CENTER_Y - 70));
	_platformCol3 = make_shared<RectCollider>(Vector2(120, 10));
	_platformCol3->GetTransform()->SetParent(_transform);
	_platformCol3->GetTransform()->SetPosition(Vector2(CENTER_X + 30, CENTER_Y - 70));

	_colliders.push_back(_floorCol);
	_colliders.push_back(_sideCol);
	_colliders.push_back(_sideCol2);
	_colliders.push_back(_platformCol1);
	_colliders.push_back(_platformCol2);
	_colliders.push_back(_platformCol3);

}

Stage2_FloralFury::~Stage2_FloralFury()
{
	_transform = nullptr;
}

void Stage2_FloralFury::Update()
{

	for (auto col : _colliders)
		col->Update();

	_sky->Update();
	_mainBG->Update();
	_hill->Update();
	_cloud->Update();
	_flower->Update();
	_sea->Update();
	_sun->Update();

	for(auto sprite : _sprites)
		sprite->Update();
	for(auto action : _actions)
		action->Update();

	_transform->UpdateSRT();

	if (_player.expired() == false)
	{
		shared_ptr<CircleCollider> circle = _player.lock()->GetBlockCollider();
		HIT_RESULT result;

		for (auto collider : _colliders)
		{
			result = collider->Block(circle);
			if (result.isHit == true && result.dir == Dir::UP)
			{
				_player.lock()->Ground();
				break;
			}
			else if (result.isHit && result.dir == Dir::DOWN)
			{
				_player.lock()->NGround();
				break;
			}


			if (result.isHit == false)
			{
				_player.lock()->NGround();
			}
		}
	}
}

void Stage2_FloralFury::Render()
{
	_sun->Render();
}

void Stage2_FloralFury::PreRender()
{
	_sky->Render();
	_cloud->Render();
	_sea->Render();

	_sprites[0]->Render();
	_sprites[0]->SetActionClip(_actions[0]->GetCurClip());

	_hill->Render();
	_mainBG->Render();

	_sprites[2]->Render();
	_sprites[1]->Render();
	_sprites[1]->SetActionClip(_actions[1]->GetCurClip());
	_sprites[2]->SetActionClip(_actions[2]->GetCurClip());
	_sprites[4]->Render();
	_sprites[3]->Render();
	_sprites[3]->SetActionClip(_actions[1]->GetCurClip());
	_sprites[4]->SetActionClip(_actions[2]->GetCurClip());
	_sprites[6]->Render();
	_sprites[5]->Render();
	_sprites[5]->SetActionClip(_actions[1]->GetCurClip());
	_sprites[6]->SetActionClip(_actions[2]->GetCurClip());
}

void Stage2_FloralFury::PostRender()
{
	_flower->Render();	

	for (auto col : _colliders)
		col->Render();
}

void Stage2_FloralFury::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Stage2/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/StageMap/Stage2/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
