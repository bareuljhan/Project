#include "framework.h"
#include "CupHead.h"

CupHead::CupHead()
{
	_player = make_shared<Player>();
	_player->GetTransform()->SetPosition(CENTER);
}

CupHead::~CupHead()
{
}

void CupHead::Update()
{
	_player->Update();
}

void CupHead::Render()
{
	_player->Render();
}
