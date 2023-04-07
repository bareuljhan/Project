#include "framework.h"
#include "ShopScene.h"

ShopScene::ShopScene()
{
	DATA_M->LoadItemInfo();

	_shop = make_shared<Shop>();
	_inven = make_shared<Inventory>();
	_inven->SetPannelPos(Vector2(1100, CENTER_Y + 100));

}

ShopScene::~ShopScene()
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


	if (ImGui::Button("BUY", { 100, 100 }))
	{
		_inven->BuyItem("Postion");
	}
}
