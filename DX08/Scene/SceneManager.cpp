#include "framework.h"
#include "SceneManager.h"

#include "../Scene/CupHead/Prologue.h"
#include "../Scene/CupHead/Tutorial.h"
#include "../Scene/CupHead/OverWorld.h"
#include "../Scene/CupHead/ShopScene.h"
#include "../Scene/CupHead/PanicStage.h"
#include "../Scene/CupHead/FloralFury.h"
#include "../Scene/CupHead/MapToolScene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	DATA_M->LoadItemInfo();
	
	_load = make_shared<LoadingScreen>();

	_sceneTable["Prologue"] = make_shared<Prologue>();
	_sceneTable["Tutorial"] = make_shared<Tutorial>();
	_sceneTable["OverWorld"] = make_shared<OverWorld>();
	_sceneTable["ShopScene"] = make_shared<ShopScene>();
	_sceneTable["PanicStage"] = make_shared<PanicStage>();
	_sceneTable["FloralFury"] = make_shared<FloralFury>();
	_sceneTable["MapToolScene"] = make_shared<MapToolScene>();

	_curScene = _sceneTable["Prologue"];

	Audio::GetInstance()->Add("MUS_Tutorial", "Resource/Sound/MUS_Tutorial.wav");
	Audio::GetInstance()->Add("bgm_title_screen", "Resource/Sound/bgm_title_screen.wav");
	Audio::GetInstance()->Add("MUS_InkwellIsleOne_Piano", "Resource/Sound/MUS_InkwellIsleOne_Piano.wav");
	Audio::GetInstance()->Add("amb_worldmap_daybirds", "Resource/Sound/amb_worldmap_daybirds.wav");
	Audio::GetInstance()->Add("bgm_level_veggies", "Resource/Sound/bgm_level_veggies.wav");
	Audio::GetInstance()->Add("bgm_level_flower(temp)", "Resource/Sound/bgm_level_flower(temp).wav");
}

SceneManager::~SceneManager()
{
	_curScene = nullptr;
}

void SceneManager::Update()
{
	if (_curScene == nullptr) return;
	_curScene->Update();
	if(_isLoading == true)
		_load->Update();
}

void SceneManager::Render()
{
	if (_curScene == nullptr) return;
	_curScene->Render();
	if (_isLoading == true)
		_load->Render();
}

void SceneManager::PreRender()
{
	if (_curScene == nullptr) return;
	_curScene->PreRender();
}

void SceneManager::PostRender()
{
	if (_curScene == nullptr) return;
	_curScene->PostRender();
}

void SceneManager::Init()
{
	_curScene->Init();
}

void SceneManager::SetScene(string name)
{
	if (_sceneTable.count(name) == 0)
		return;
	
	if (_curScene != _sceneTable["Prologue"])
	{
		_isLoading = true;
		_load->GetBuffer()->_data.fadeValue = 1.0f;
		_load->isReady = true;
	}

	if (_curScene != nullptr)
	{
		_curScene->Finalize();
	}
	_curScene = _sceneTable[name];
	_curScene->Init();
}
