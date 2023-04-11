#include "framework.h"
#include "OverWorld.h"

OverWorld::OverWorld()
{
	_map = make_shared<OverWorld_BG>();
	_player = make_shared<OverWorld_Player>();
	_player->GetTransform()->GetScale() *= 0.5f;
	_player->GetTransform()->SetPosition(Vector2(260, 465));
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
}

void OverWorld::Render()
{
	_map->Render();
	_player->Render();
	if(KEY_PRESS('Q'))
		_route->Render();

	//ImGui::InputFloat2("Mouse_POS", static_cast<float*>(MOUSE_POS.x), MOUSE_POS.y);
}
