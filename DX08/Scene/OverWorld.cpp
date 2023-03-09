#include "framework.h"
#include "OverWorld.h"

OverWorld::OverWorld()
{
	_map = make_shared<OverWorld_BG>();
	_player = make_shared<OverWorld_Player>();
	_player->GetTransform()->GetScale() *= 0.5f;
	_player->GetTransform()->GetPos() = Vector2(265, 455);
}

OverWorld::~OverWorld()
{
}

void OverWorld::Update()
{
	_map->Update();
	_player->Update();
}

void OverWorld::Render()
{
	_map->Render();
	_player->Render();
}
