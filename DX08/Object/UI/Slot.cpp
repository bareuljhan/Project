#include "framework.h"
#include "Slot.h"

Slot::Slot()
{
	_quad = make_shared<Quad>(L"Resource/Texture/CupHead/Equip.png");
	_quad->GetTransform()->SetScale(Vector2(0.15f, 0.13f));
}

Slot::~Slot()
{
}

void Slot::Update()
{
	_quad->Update();
}

void Slot::Render()
{
	_quad->Render();
}
