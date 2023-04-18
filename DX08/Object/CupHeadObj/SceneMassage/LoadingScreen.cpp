#include "framework.h"
#include "LoadingScreen.h"

LoadingScreen::LoadingScreen()
{
	_quad = make_shared<Quad>(L"Resource/Texture/CupHead/Loading.png");
	_quad->SetPS(ADD_PS(L"Shader/FadePixelShader.hlsl"));

	_buffer = make_shared<FadeBuffer>();
	_buffer->_data.fadeValue = 1.0f;
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::Update()
{
	_quad->Update();
	_buffer->Update();

	_buffer->_data.fadeValue -= 0.001f;

	if (_buffer->_data.fadeValue <= 0)
		_buffer->_data.fadeValue = 0.0f;
}

void LoadingScreen::Render()
{
	_quad->Render();
	_buffer->SetPSBuffer(0);
}
