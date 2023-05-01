#include "framework.h"
#include "OverWorld.h"

OverWorld::OverWorld()
{
	_map = make_shared<OverWorld_BG>();
	_player = make_shared<OverWorld_Player>();
	_player->GetTransform()->GetScale() *= 0.5f;
	_player->GetTransform()->SetPosition(Vector2(260, 465));
	
	_button = make_shared<Button>(L"Resource/Texture/CupHead/Button/StartButton.png");
	_button->SetScale({ 0.4f, 0.4f });
	_button->SetPostion(Vector2(500, 50));
	_button->SetEvent(std::bind(&OverWorld::NextScene, this));

	_route = make_shared<Route>();

}

OverWorld::~OverWorld()
{
}

void OverWorld::Init()
{
}

void OverWorld::Finalize()
{
}

void OverWorld::Update()
{
	_map->Update();
	_player->Update();
	_route->Update();

	if (_map->OozeCol()->IsCollision(_player->GetBodyCollider()))
	{
		_button->Update();
		_isOoze = true;
		_isShop = false;
		_isPanic = false;
	}
	if (_map->PanicCol()->IsCollision(_player->GetBodyCollider()))
	{
		_button->Update();
		_isPanic = true;
		_isOoze = false;
		_isShop = false;
	}
	if (_map->ShopCol()->IsCollision(_player->GetBodyCollider()))
	{
		_button->Update();
		_isShop = true;
		_isOoze = false;
		_isPanic = false;
	}
}

void OverWorld::Render()
{
	_map->Render();
	_player->Render();
	if(KEY_PRESS('Q'))
		_route->Render();

	if (_map->OozeCol()->IsCollision(_player->GetBodyCollider()))
	{
		_button->PostRender();
	}
	if (_map->PanicCol()->IsCollision(_player->GetBodyCollider()))
	{
		_button->PostRender();
	}
	if (_map->ShopCol()->IsCollision(_player->GetBodyCollider()))
	{
		_button->PostRender();
	}
	//ImGui::InputFloat2("Mouse_POS", static_cast<float*>(MOUSE_POS.x), MOUSE_POS.y);

}

void OverWorld::NextScene()
{
	_player->isIn = true;

	if (_isOoze == true)
	{
		SCENE->SetScene("FloralFury");
		_player->isIn = false;
		Audio::GetInstance()->Stop("MUS_InkwellIsleOne_Piano");
		Audio::GetInstance()->Stop("amb_worldmap_daybirds");
		Audio::GetInstance()->Play("bgm_level_flower(temp)");
		Audio::GetInstance()->SetVolume("bgm_level_flower(temp)", 0.5f);
	}
	if (_isPanic == true)
	{
		SCENE->SetScene("PanicStage");
		_player->isIn = false;
		Audio::GetInstance()->Stop("MUS_InkwellIsleOne_Piano");
		Audio::GetInstance()->Stop("amb_worldmap_daybirds");
		Audio::GetInstance()->Play("bgm_level_veggies");
		Audio::GetInstance()->SetVolume("bgm_level_veggies", 0.5f);	
	}
	if (_isShop == true)
	{
		SCENE->SetScene("ShopScene");
		_player->isIn = false;
		Audio::GetInstance()->Stop("MUS_InkwellIsleOne_Piano");
		Audio::GetInstance()->Stop("amb_worldmap_daybirds");
	}
}
