#include "framework.h"
#include "Slot.h"

Slot::Slot()
{
	_quad = make_shared<Quad>(L"Resource/Texture/CupHead/Slot.png");
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
