#include "framework.h"
#include "Route.h"

Route::Route()
{
	CreateNode(40, 20);
	CreateMapData();
	CreateObticle();
}

Route::~Route()
{
}

void Route::Update()
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			_mapData[i][j]->blocks->Update();
		}
	}
}

void Route::Render()
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			_mapData[i][j]->blocks->Render();
		}
	}
}

void Route::CreateObticle()
{
	for (int i = 0; i < 20; i++)
	{
		_mapData[0][i]->obticle = true;
		_mapData[39][i]->obticle = true;
	}
	for (int i = 0; i < 40; i++)
	{
		_mapData[i][0]->obticle = true;
		_mapData[i][19]->obticle = true;
	}
}
