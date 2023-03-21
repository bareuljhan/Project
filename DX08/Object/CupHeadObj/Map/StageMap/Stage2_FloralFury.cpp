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
	_sprite->GetTransform()->SetPosition(Vector2(CENTER_X, CENTER_Y - 30));
	_sprite->GetTransform()->SetScale(Vector2(1.5f, 1.5f));
	_action->Play();

	_floorCol = make_shared<RectCollider>(Vector2(1400, 100));
	_floorCol->GetTransform()->SetParent(_transform);
	_floorCol->GetTransform()->SetPosition(Vector2(CENTER_X,30));

	_sideCol = make_shared<RectCollider>(Vector2(100, 1280));
	_sideCol->GetTransform()->SetParent(_transform);
	_sideCol->GetTransform()->SetPosition(Vector2(-45, 0));

	_sideCol2 = make_shared<RectCollider>(Vector2(100, 1280));
	_sideCol2->GetTransform()->SetParent(_transform);
	_sideCol2->GetTransform()->SetPosition(Vector2(1325, 100));

	_colliders.push_back(_floorCol);
	_colliders.push_back(_sideCol);
	_colliders.push_back(_sideCol2);

}

Stage2_FloralFury::~Stage2_FloralFury()
{
	_transform = nullptr;
}

void Stage2_FloralFury::Update()
{
	_floorCol->Update();
	_sideCol->Update();
	_sideCol2->Update();

	_sky->Update();
	_mainBG->Update();
	_hill->Update();
	_cloud->Update();
	_flower->Update();
	_sea->Update();
	_sun->Update();

	_sprite->Update();
	_action->Update();

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
	_sprite->Render();
	_sprite->SetActionClip(_action->GetCurClip());
	_hill->Render();
	_mainBG->Render();
}

void Stage2_FloralFury::PostRender()
{
	_flower->Render();	
	_floorCol->Render();
	_sideCol->Render();
	_sideCol2->Render();
}

void Stage2_FloralFury::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Stage2/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/StageMap/Stage2/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_action = make_shared<Action>(xml.GetClips(), actionName, type);
	_sprite = make_shared<Sprite>(srvPath, xml.AverageSize());
}
