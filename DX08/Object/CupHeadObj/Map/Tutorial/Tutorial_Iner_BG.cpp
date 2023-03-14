#include "framework.h"
#include "Tutorial_Iner_BG.h"

Tutorial_Iner_BG::Tutorial_Iner_BG()
{
	_transform = make_shared<Transform>();

	_jumpCube = make_shared<Quad>(L"Resource/Texture/CupHead/Tutorial/Tutorial_cube.png");
	_mainSheet = make_shared<Quad>(L"Resource/Texture/CupHead/Tutorial/Tutorial_backGround.png");
	_exit = make_shared<Quad>(L"Resource/Texture/CupHead/Tutorial/tutorial_exit_door.png");
	_cylinder1 = make_shared<Quad>(L"Resource/Texture/CupHead/Tutorial/tutorial_cylinder_1.png");
	_cylinder2 = make_shared<Quad>(L"Resource/Texture/CupHead/Tutorial/tutorial_cylinder_2.png");
	_pyramidTarget = make_shared<Quad>(L"Resource/Texture/CupHead/Tutorial/tutorial_pyramid_topper.png");
	_target = make_shared<Quad>(L"Resource/Texture/CupHead/Tutorial/tutorial_target.png");


	_floorCol = make_shared<RectCollider>(Vector2(4000, 100));
	_floorCol->GetTransform()->SetParent(_transform);
	_floorCol->GetTransform()->SetPosition(Vector2(1400, -320));

	_cubeCol = make_shared<RectCollider>(Vector2(170,150));
	_cubeCol->GetTransform()->SetParent(_transform);
	_cubeCol->GetTransform()->SetPosition(_jumpCube->GetTransform()->GetPos());
	_cubeCol->GetTransform()->SetPosition(Vector2(-70, -200));

	_cylinder1Col = make_shared<RectCollider>(Vector2(170, 330));
	_cylinder1Col->GetTransform()->SetParent(_transform);
	_cylinder1Col->GetTransform()->SetPosition(_cylinder1->GetTransform()->GetPos());
	_cylinder1Col->GetTransform()->SetPosition(Vector2(690, -100));

	_cylinder2Col = make_shared<RectCollider>(Vector2(175, 330));
	_cylinder2Col->GetTransform()->SetParent(_cylinder2->GetTransform());
	_cylinder2Col->GetTransform()->SetPosition(_cylinder2->GetTransform()->GetPos());
	_cylinder2Col->GetTransform()->SetPosition(Vector2(-95, 0));
	

	_cylinder3Col = make_shared<RectCollider>(Vector2(160, 70));
	_cylinder3Col->GetTransform()->SetParent(_cylinder2->GetTransform());
	_cylinder3Col->GetTransform()->SetPosition(_cylinder2->GetTransform()->GetPos());
	_cylinder3Col->GetTransform()->SetPosition(Vector2(90, -90));
	
	_exitCol = make_shared<RectCollider>(Vector2(170, 200));
	_exitCol->GetTransform()->SetParent(_exit->GetTransform());
	_exitCol->GetTransform()->SetPosition(_exit->GetTransform()->GetPos());

	_targetCol = make_shared<CircleCollider>(40);
	_targetCol->GetTransform()->SetParent(_target->GetTransform());
	_targetCol->GetTransform()->SetPosition(_target->GetTransform()->GetPos());

	_mainSheet->GetTransform()->GetScale() *= 7.0f;
	_mainSheet->GetTransform()->SetPosition(Vector2(CENTER_X + 300, CENTER_Y -300));
	_mainSheet->GetTransform()->SetParent(_transform);

	_jumpCube->GetTransform()->SetParent(_transform);
	_jumpCube->GetTransform()->SetPosition(Vector2(CENTER_X -700, CENTER_Y -550));

	_exit->GetTransform()->SetParent(_transform);
	_exit->GetTransform()->SetPosition(Vector2(3200, -150));

	_cylinder1->GetTransform()->SetParent(_transform);
	_cylinder1->GetTransform()->SetPosition(Vector2(700, -100));

	_cylinder2->GetTransform()->SetParent(_transform);
	_cylinder2->GetTransform()->SetPosition(Vector2(1500, -100));

	_pyramidTarget->GetTransform()->GetScale() *= 2.2f;
	_pyramidTarget->GetTransform()->SetParent(_transform);
	_pyramidTarget->GetTransform()->SetPosition(Vector2(2400, -90));

	_target->GetTransform()->SetParent(_transform);
	_target->GetTransform()->SetPosition(Vector2(2390, 115));

	_colliders.push_back(_floorCol);
	_colliders.push_back(_cubeCol);
	_colliders.push_back(_cylinder1Col);
	_colliders.push_back(_cylinder2Col);
	_colliders.push_back(_cylinder3Col);
}
Tutorial_Iner_BG::~Tutorial_Iner_BG()
{
}

void Tutorial_Iner_BG::Update()
{
	Init();

	_floorCol->Update();
	_cubeCol->Update();
	_exitCol->Update();
	_cylinder1Col->Update();
	_cylinder2Col->Update();
	_cylinder3Col->Update();

	if (_isDestroy == false)
	{
		_targetCol->Update();
		_target->Update();
	}

	_jumpCube->Update();
	_mainSheet->Update();
	_exit->Update();
	_cylinder1->Update();
	_cylinder2->Update();
	_pyramidTarget->Update();

	_transform->UpdateSRT();


	if (_player.expired() == false)
	{
		shared_ptr<CircleCollider> circle = _player.lock()->GetBlockCollider();
		HIT_RESULT result;

		for (auto rect : _colliders)
		{
			result = rect->Block(circle);
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

void Tutorial_Iner_BG::Render()
{
	
	_mainSheet->Render();
	_jumpCube->Render();
	_exit->Render();
	_cylinder1->Render();
	_cylinder2->Render();
	_pyramidTarget->Render();

	if (_isDestroy == false)
	{
		_target->Render();
		_targetCol->Render();
	}

	_cubeCol->Render();
	_exitCol->Render();
	_cylinder1Col->Render();
	_cylinder2Col->Render();
	_cylinder3Col->Render();
	_floorCol->Render();
}

Vector2 Tutorial_Iner_BG::LeftBottom()
{
	Vector2 curPos = _mainSheet->GetTransform()->GetWorldPos();
	Vector2 size = _mainSheet->GetImageSize();
	return (curPos - size);
}

Vector2 Tutorial_Iner_BG::RightTop()
{
	Vector2 curPos = _mainSheet->GetTransform()->GetWorldPos();
	Vector2 size = _mainSheet->GetImageSize();
	return (curPos + size);
}

void Tutorial_Iner_BG::Damaged(float amount)
{
	if (amount <= 0.0f)
		return;

	_targetHP -= amount;

	if (_targetHP < 0.0f)
	{
		_targetHP = 0.0f;
		_isDestroy = true;
	}
}

void Tutorial_Iner_BG::Init()
{
	if (KEY_PRESS('A') || KEY_PRESS('Z'))
	{
		Vector2 temp = _transform->GetPos();
		temp.x += _speed * DELTA_TIME;
		_transform->SetPosition(temp);
	}
	if (KEY_PRESS('D') || KEY_PRESS('C'))
	{
		Vector2 temp = _transform->GetPos();
		temp.x -= _speed * DELTA_TIME;
		_transform->SetPosition(temp);
	}
}
