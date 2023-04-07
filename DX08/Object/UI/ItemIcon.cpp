#include "framework.h"
#include "ItemIcon.h"

ItemIconButton::ItemIconButton()
{
	_sprite = make_shared<Sprite>(L"Resource/Texture/CupHead/Item/Item.png", Vector2(11, 5), Vector2(100, 80));
	_button = make_shared<Button>(Vector2(80, 70));
	_button->SetParent(_sprite->GetTransform());
}

ItemIconButton::~ItemIconButton()
{
}

void ItemIconButton::Update()
{
	_sprite->Update();
	_button->Update();
}

void ItemIconButton::Render()
{
	_sprite->Render();
	_button->PostRender();
}
