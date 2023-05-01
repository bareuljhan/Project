#include "framework.h"
#include "Route.h"

Route::Route()
{
	CreateNode(40, 22);
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
		for (int j = 0; j < 22; j++)
		{
			_mapData[i][j]->blocks->Update();
		}
	}
}

void Route::Render()
{
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			_mapData[i][j]->blocks->Render();
		}
	}
}

void Route::CreateObticle()
{
	for (int i = 0; i < 22; i++)
	{
		_mapData[0][i]->obticle = true;
		_mapData[39][i]->obticle = true;
	}
	for (int i = 0; i < 40; i++)
	{
		_mapData[i][0]->obticle = true;
		_mapData[i][21]->obticle = true;
	}

	for (int x = 1; x <= 15; x++)
	{
		for (int y = 1; y <= 7; y++)
			_mapData[x][y]->obticle = true;
	}
	for (int x = 1; x <= 21; x++)
		_mapData[x][20]->obticle = true;
	for (int x = 1; x <= 18; x++)
		_mapData[x][19]->obticle = true;
	for (int x = 1; x <= 18; x++)
		_mapData[x][18]->obticle = true;
	for (int x = 7; x <= 17; x++)
		_mapData[x][17]->obticle = true;
	for (int x = 7; x <= 17; x++)
		_mapData[x][16]->obticle = true;
	for (int y = 12; y <= 15; y++)
	{
		for (int x = 11; x <= 18; x++)
			_mapData[x][y]->obticle = true;
	}
	for (int y = 11; y <= 14; y++)
		_mapData[10][y]->obticle = true;
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 22; j++)
		{
			if (_mapData[i][j]->obticle == true)
			{
				_mapPos.push_back(_mapData[i][j]->blocks->GetTransform()->GetPos());
			}
		}
	}

}
