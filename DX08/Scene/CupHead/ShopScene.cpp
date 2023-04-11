#include "framework.h"
#include "ShopScene.h"

ShopScene::ShopScene()
{
	DATA_M->LoadItemInfo();
	_inven = make_shared<Inventory>();
	_inven->SetPannelPos(Vector2(1100, CENTER_Y + 100));

	_shop = make_shared<Shop>();
	_shop->SetInventory(_inven);
}

ShopScene::~ShopScene()
{
}

void ShopScene::Init()
{
}

void ShopScene::Finalize()
{
}

void ShopScene::Update()
{
	_shop->Update();

	if (KEY_PRESS('I') || KEY_PRESS('i'))
	{
		_inven->Update();
	}

}

void ShopScene::Render()
{
	_shop->Render();
	if (KEY_PRESS('I') || KEY_PRESS('i'))
	{
		_inven->Render();
	}
}

void ShopScene::PostRender()
{
	_shop->PostRender();

	if (KEY_PRESS('I') || KEY_PRESS('i'))
	{
		_inven->PostRender();
	}
}
