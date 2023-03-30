#include "framework.h"
#include "Program.h"

#include "../Scene/Prologue.h"
#include "../Scene/CupHead.h"
#include "../Scene/OverWorld.h"
#include "../Scene/Tutorial.h"
#include "../Scene/PanicStage.h"
#include "../Scene/FloralFury.h"

Program::Program()
{
	Timer::GetInstance()->SetLockFPS(120);
	_scene = make_shared<OverWorld>();
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

	ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	CAMERA->PostRender();
	_scene->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}