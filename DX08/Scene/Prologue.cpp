#include "framework.h"
#include "Prologue.h"

Prologue::Prologue()
{
	_intro = make_shared<PrologueAni>();
}

Prologue::~Prologue()
{
}

void Prologue::Update()
{
	_intro->Update();
}

void Prologue::Render()
{
	_intro->Render();
}
