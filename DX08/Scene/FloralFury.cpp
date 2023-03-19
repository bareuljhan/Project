#include "framework.h"
#include "FloralFury.h"

FloralFury::FloralFury()
{
	_map = make_shared<Stage2_FloralFury>();
}

FloralFury::~FloralFury()
{
}

void FloralFury::Update()
{
	_map->Update();

}

void FloralFury::Render()
{
	_map->PreRender();
	_map->Render();
	_map->PostRender();
}