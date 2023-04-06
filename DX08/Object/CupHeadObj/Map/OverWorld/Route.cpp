#include "framework.h"
#include "Route.h"

Route::Route()
{
	CreateNode(30, 15);
	CreateMapData();
	CreateObticle();
}

Route::~Route()
{
}

void Route::Update()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			_mapData[i][j]->blocks->Update();
		}
	}
}

void Route::Render()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			_mapData[i][j]->blocks->Render();
		}
	}
}

void Route::CreateObticle()
{
	for (int i = 0; i < 15; i++)
	{
		_mapData[0][i]->obticle = true;
		_mapData[29][i]->obticle = true;
	}
	for (int i = 0; i < 30; i++)
	{
		_mapData[i][0]->obticle = true;
		_mapData[i][14]->obticle = true;
	}
}
