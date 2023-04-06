#include "framework.h"
#include "ShopScene.h"

ShopScene::ShopScene()
{
	_shop = make_shared<Shop>();
}

ShopScene::~ShopScene()
{
}

void ShopScene::Update()
{
	_shop->Update();
}

void ShopScene::Render()
{
	_shop->Render();
}

void ShopScene::PostRender()
{
	_shop->PostRender();
}
