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
	}
	else
	{
		_startScreen->Render();
	}

	if (isNext == true && KEY_UP(VK_LBUTTON) || _intro->isEnd == true)
	{
		SCENE->SetScene("Tutorial");
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
