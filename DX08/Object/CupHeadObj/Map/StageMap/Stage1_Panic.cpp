#include "framework.h"
#include "Stage1_Panic.h"

Stage1_Panic::Stage1_Panic()
{
	_transform = make_shared<Transform>();

	_sky = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/sky.png");
	_sky->GetTransform()->GetPos() = CENTER;
	_sky->GetTransform()->GetPos().y += 105;
	_sky->GetTransform()->GetScale() *= 1.5;

	_mainBG = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/mainBG1.png");
	_mainBG->GetTransform()->GetPos() = CENTER;
	_mainBG->GetTransform()->GetScale() *= 1.358;
	_mainBG->GetTransform()->GetPos().y -= 210;
	_mainBG->GetTransform()->GetPos().x += 10;

	_mainField1 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/mainfield.png");	
	_mainField1->GetTransform()->GetScale() *= 1.7;
	_mainField1->GetTransform()->GetPos() = CENTER;
	_mainField1->GetTransform()->GetPos().y += 190;

	_field1 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/field1.png");
	_field1->GetTransform()->GetScale() *= 1.6;
	_field1->GetTransform()->GetPos() = CENTER;
	_field1->GetTransform()->GetPos().x += 20;

	_field2 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/field2.png");
	_field2->GetTransform()->GetScale() *= 1.5;
	_field2->GetTransform()->GetPos() = CENTER;
	_field2->GetTransform()->GetPos().x += 50;
	_field2->GetTransform()->GetPos().y -= 10;


	_field3 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/field3.png");
	_field3->GetTransform()->GetScale() *= 1.612;
	_field3->GetTransform()->GetPos() = CENTER;
	_field3->GetTransform()->GetPos().x += 70;
	_field3->GetTransform()->GetPos().y -= 95;

	_field4 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/field4.png");
	_field4->GetTransform()->GetScale() *= 1.612;
	_field4->GetTransform()->GetPos() = CENTER;
	_field4->GetTransform()->GetPos().x += 185;
	_field4->GetTransform()->GetPos().y -= 95;

	_field5 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/field5.png");
	_field5->GetTransform()->GetScale() *= 1.5;
	_field5->GetTransform()->GetPos() = CENTER;
	_field5->GetTransform()->GetPos().x += 20;

	_field6 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/field6.png");
	_field6->GetTransform()->GetScale() *= 1.6;
	_field6->GetTransform()->GetPos() = CENTER;
	_field6->GetTransform()->GetPos().x -= 20;
	_field6->GetTransform()->GetPos().y += 13;

	_cloud1 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/cloud3.png");
	_cloud1->GetTransform()->GetScale() *= 1.7;
	_cloud1->GetTransform()->GetPos() = CENTER;
	_cloud1->GetTransform()->GetPos().y += 350;

	_cloud2 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/cloud2.png");
	_cloud2->GetTransform()->GetScale() *= 1.1;
	_cloud2->GetTransform()->GetPos() = CENTER;
	_cloud2->GetTransform()->GetPos().y += 70;
	_cloud2->GetTransform()->GetPos().x -= 570;

	_cloud3 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/cloud3.png");
	_cloud3->GetTransform()->GetScale() *= 1.5;
	_cloud3->GetTransform()->GetPos() = CENTER;
	_cloud3->GetTransform()->GetPos().y += 350;
	_cloud3->GetTransform()->GetPos().x += 540;

	_cloud4 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/cloud4.png");
	_cloud4->GetTransform()->GetScale() *= 1.1;
	_cloud4->GetTransform()->GetPos() = CENTER;
	_cloud4->GetTransform()->GetPos().y += 350;
	_cloud4->GetTransform()->GetPos().x -= 540;

	_cloud5 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/cloud5.png");
	_cloud5->GetTransform()->GetScale() *= 1.5;
	_cloud5->GetTransform()->GetPos() = CENTER;
	_cloud5->GetTransform()->GetPos().y += 100;
	_cloud5->GetTransform()->GetPos().x += 580;

	_cloud6 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/cloud6.png");
	_cloud6->GetTransform()->GetScale() *= 1.6;
	_cloud6->GetTransform()->GetPos() = CENTER;
	_cloud6->GetTransform()->GetPos().y += 100;
	_cloud6->GetTransform()->GetPos().x -= 30;

	_postField1 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/Post_field1.png");
	_postField1->GetTransform()->GetScale() *= 1.2;
	_postField1->GetTransform()->GetPos() = CENTER;
	_postField1->GetTransform()->GetPos().x += 430;
	_postField1->GetTransform()->GetPos().y -= 290;

	_postField2 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/Post_field2.png");
	_postField2->GetTransform()->GetScale() *= 1.2;
	_postField2->GetTransform()->GetPos() = CENTER;
	_postField2->GetTransform()->GetPos().x -= 470;
	_postField2->GetTransform()->GetPos().y -= 290;

	_sideField1 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/sidefield1.png");
	_sideField1->GetTransform()->GetScale() *= 2.0;
	_sideField1->GetTransform()->GetPos() = CENTER;
	_sideField1->GetTransform()->GetPos().x -= 530;

	_sideField2 = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/sidefield2.png");
	_sideField2->GetTransform()->GetScale() *= 1.5;
	_sideField2->GetTransform()->GetPos() = CENTER;
	_sideField2->GetTransform()->GetPos().x += 40;
	_sideField2->GetTransform()->GetPos().y += 20;

	_floorCol = make_shared<RectCollider>(Vector2(1280, 100));
	_floorCol->GetTransform()->SetParent(_transform);
	_floorCol->GetTransform()->SetPosition(CENTER);
	_floorCol->GetTransform()->GetPos().y -= 350.0f;

	_sideCol = make_shared<RectCollider>(Vector2(100, 1280));
	_sideCol->GetTransform()->SetParent(_transform);
	_sideCol->GetTransform()->SetPosition(Vector2(-50, 0));

	_colliders.push_back(_floorCol);
	_colliders.push_back(_sideCol);
}

Stage1_Panic::~Stage1_Panic()
{
}

void Stage1_Panic::Update()
{
	_floorCol->Update();
	_sideCol->Update();

	_sky->Update();
	_cloud6->Update();
	_cloud2->Update();
	_cloud4->Update();
	_cloud3->Update();
	_cloud1->Update();
	_cloud5->Update();
	_sideField2->Update();
	_sideField1->Update();
	_mainField1->Update();
	_field6->Update();
	_field5->Update();
	_field2->Update();
	_field1->Update();
	_field4->Update();
	_field3->Update();
	_mainBG->Update();
	_postField1->Update();
	_postField2->Update();

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

void Stage1_Panic::PreRender()
{
	_sky->Render();
	_cloud6->Render();
	_cloud2->Render();
	_cloud4->Render();
	_cloud3->Render();
	_cloud1->Render();
	_cloud5->Render();

}

void Stage1_Panic::Render()
{
	_sideField2->Render();
	_sideField1->Render();
	_mainField1->Render();
	_field6->Render();
	_field5->Render();
	_field2->Render();
	_field1->Render();
	_field4->Render();
	_field3->Render();
	_mainBG->Render();
}

void Stage1_Panic::PostRender()
{
	_postField1->Render();
	_postField2->Render();
	_floorCol->Render();
	_sideCol->Render();
}
