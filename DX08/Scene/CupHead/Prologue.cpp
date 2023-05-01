#include "framework.h"
#include "Prologue.h"

Prologue::Prologue()
{
	_startScreen = make_shared<StartScreen>();

	_intro = make_shared<PrologueAni>();

}

Prologue::~Prologue()
{
}

void Prologue::Init()
{
	Audio::GetInstance()->Play("bgm_title_screen");
	Audio::GetInstance()->SetVolume("bgm_title_screen", 0.3f);
}

void Prologue::Finalize()
{
}

void Prologue::Update()
{
	SetScreen();

	if (isNext == true)
	{
		_intro->Update();
	}
	else
		_startScreen->Update();
	
}

void Prologue::Render()
{
	if (isNext == true)
	{
		_intro->Render();
		Audio::GetInstance()->Stop("bgm_title_screen");
	}
	else
	{
		_startScreen->Render();
	}

	if (isNext == true && KEY_UP(VK_LBUTTON) || _intro->isEnd == true)
	{
		SCENE->SetScene("Tutorial");
		Audio::GetInstance()->Play("MUS_Tutorial");
		Audio::GetInstance()->SetVolume("MUS_Tutorial", 0.06f);
	}	
}

void Prologue::PostRender()
{
	if(isNext == false)
		_startScreen->PostRender();
}

void Prologue::SetScreen()
{
	if (KEY_DOWN(VK_RETURN))
	{
		isNext = true;
	}
}
