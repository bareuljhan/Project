#include "framework.h"
#include "Route.h"

Route::Route()
{
	CreateNode(30, 15);
	CreateMapData();
}

Route::~Route()
{
}

void Route::Update()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			_blocks[i][j]->Update();
		}
	}
}

void Route::Render()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			_blocks[i][j]->Render();
		}
	}
}

void Route::CreateRoute()
{

}