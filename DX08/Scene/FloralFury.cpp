#include "framework.h"
#include "FloralFury.h"

FloralFury::FloralFury()
{
	_player = make_shared<Player>();
	_player->GetTransform()->SetPosition(Vector2(300, 155));

	_map = make_shared<Stage2_FloralFury>();
	_map->SetPlayer(_player);

	_boss1 = make_shared<Flower>();
}

FloralFury::~FloralFury()
{
}

void FloralFury::Update()
{
	_map->Update();
	_boss1->Update();
	_player->Update();
}
 
void FloralFury::Render()
{
	_map->PreRender();
	_map->Render();
	_boss1->Render();
	_player->Render();

	_map->PostRender();

	ImGui::SliderFloat("PlayerPosX", &_player->GetTransform()->GetPos().y, 0, 1000);
}