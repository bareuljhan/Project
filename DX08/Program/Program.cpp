#include "framework.h"
#include "Program.h"

#include "../Scene/Prologue.h"
#include "../Scene/OverWorld.h"
#include "../Scene/ShopScene.h"
#include "../Scene/Tutorial.h"
#include "../Scene/PanicStage.h"
#include "../Scene/FloralFury.h"

Program::Program()
{
	Timer::GetInstance()->SetLockFPS(120);
	_scene = make_shared<ShopScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	if (KEY_DOWN(VK_F1))
		Collider::isDebug = !Collider::isDebug;

	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();
	AUDIO->Update();
	CAMERA->Update();

	_scene->Update();
	EFFECT->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	CAMERA->SetProjectionBuffer();
	CAMERA->SetCameraWorldBuffer();

	_scene->PreRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	Device::GetInstance()->SetMainRenderTarget();

	ALPHA->SetState();

	_scene->Render();
	EFFECT->Render();

	DirectWrite::GetInstance()->GetDC()->BeginDraw();

	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0, 0, 100, 100 };
	DirectWrite::GetInstance()->RenderText(fps, rect);

	CAMERA->PostRender();
	_scene->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDC()->EndDraw();
	Device::GetInstance()->Present();
}