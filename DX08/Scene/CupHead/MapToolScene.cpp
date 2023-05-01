#include "framework.h"
#include "MapToolScene.h"

MapToolScene::MapToolScene()
{
	_sky = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/sky.png");
	_floor = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage2/FloralFuryBG.png");
	_cloud = make_shared<Quad>(L"Resource/Texture/CupHead/StageMap/Stage1/cloud2.png");
}

MapToolScene::~MapToolScene()
{
}

void MapToolScene::Update()
{
}

void MapToolScene::Render()
{
}

void MapToolScene::PostRender()
{
}

void MapToolScene::Save()
{
	
}

void MapToolScene::Load()
{
}
