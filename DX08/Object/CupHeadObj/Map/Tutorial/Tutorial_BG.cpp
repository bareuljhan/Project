#include "framework.h"
#include "Tutorial_BG.h"

Tutorial_BG::Tutorial_BG()
{
	_backGround = make_shared<Quad>(L"Resource/Texture/CupHead/Tutorial/Tutorial_backGround2.png");

	_backGround->GetTransform()->SetPosition(CENTER);
	_backGround->GetTransform()->GetScale() *= 1.256f;
}

Tutorial_BG::~Tutorial_BG()
{
}

void Tutorial_BG::Update()
{
	_backGround->Update();

}

void Tutorial_BG::Render()
{
	_backGround->Render();
}

Vector2 Tutorial_BG::LeftBottom()
{
	Vector2 curPos = _backGround->GetTransform()->GetWorldPos();
	Vector2 size = _backGround->GetImageSize() * 0.5f;
	return (curPos - size);
}

Vector2 Tutorial_BG::RightTop()
{
	Vector2 curPos = _backGround->GetTransform()->GetWorldPos();
	Vector2 size = _backGround->GetImageSize() * 0.5;
	return (curPos + size);
}

