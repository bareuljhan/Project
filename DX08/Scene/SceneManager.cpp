#include "framework.h"
#include "SceneManager.h"

#include "../Scene/CupHead/Prologue.h"
#include "../Scene/CupHead/Tutorial.h"
#include "../Scene/CupHead/OverWorld.h"
#include "../Scene/CupHead/ShopScene.h"
#include "../Scene/CupHead/PanicStage.h"
#include "../Scene/CupHead/FloralFury.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	DATA_M->LoadItemInfo();

	_sceneTable["Prologue"] = make_shared<Prologue>();
	_sceneTable["Tutorial"] = make_shared<Tutorial>();
	_sceneTable["OverWorld"] = make_shared<OverWorld>();
	_sceneTable["ShopScene"] = make_shared<ShopScene>();
	_sceneTable["PanicStage"] = make_shared<PanicStage>();
	_sceneTable["FloralFury"] = make_shared<FloralFury>();

	_curScene = _sceneTable["Prologue"];
}

SceneManager::~SceneManager()
{
	_curScene = nullptr;
}

void SceneManager::Update()
{
	if (_curScene == nullptr) return;
	_curScene->Update();
}

void SceneManager::Render()
{
	if (_curScene == nullptr) return;
	_curScene->Render();
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

	if (_curScene != nullptr)
	{
		_curScene->Finalize();
	}
	_curScene = _sceneTable[name];
	_curScene->Init();
}
