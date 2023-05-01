#include "framework.h"
#include "ShopScene.h"

ShopScene::ShopScene()
{
	DATA_M->LoadItemInfo();

	_shop = make_shared<Shop>();

	_button = make_shared<Button>(L"Resource/Texture/CupHead/Button/Exit.png");
	_button->SetScale({ 0.4f, 0.35f });
	_button->SetPostion(Vector2(1080, 250));
	_button->SetEvent(std::bind(&ShopScene::NextScene, this));
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
	_button->Update();

	if (KEY_PRESS('I') || KEY_PRESS('i'))
	{
		INVEN_M->GetInven()->Update();
	}
}

void ShopScene::Render()
{
	_shop->Render();
	if (KEY_PRESS('I') || KEY_PRESS('i'))
	{
		INVEN_M->GetInven()->Render();
	}
}

void ShopScene::PostRender()
{
	if (SCENE->GetValue() >= 0.7f) return;
	_shop->PostRender();

	if (KEY_PRESS('I') || KEY_PRESS('i'))
	{
		INVEN_M->GetInven()->PostRender();
	}
	_button->PostRender();
}

void ShopScene::NextScene()
{
	SCENE->SetScene("OverWorld"); 
	Audio::GetInstance()->Play("MUS_InkwellIsleOne_Piano");
	Audio::GetInstance()->SetVolume("MUS_InkwellIsleOne_Piano", 0.5f);
	Audio::GetInstance()->Play("amb_worldmap_daybirds");
	Audio::GetInstance()->SetVolume("amb_worldmap_daybirds", 0.5f);
}
