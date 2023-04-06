#include "framework.h"
#include "ItemIcon.h"

ItemIcon::ItemIcon()
{
	_sprite = make_shared<Sprite>(L"Resource/Texture/CupHead/Item/Item.png", Vector2(1.0f, 2.2f), Vector2(100, 80));
	_button = make_shared<Button>(Vector2(80, 70));
	_button->SetParent(_sprite->GetTransform());
}

ItemIcon::~ItemIcon()
{
}

void ItemIcon::Update()
{
	_sprite->Update();
	_button->Update();
}

void ItemIcon::Render()
{
	_sprite->Render();
	_button->PostRender();
}
