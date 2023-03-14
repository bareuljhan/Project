#include "framework.h"
#include "Tutorial.h"

Tutorial::Tutorial()
{
	_bg = make_shared<Tutorial_BG>();
	
	_player = make_shared<Player>();
	_player->GetTransform()->SetPosition(Vector2(CENTER_X - 250, CENTER_Y - 100));
	_player->GetTransform()->GetScale() *= 0.9f;

	_player->SetSpeed(50.0f);

	_iner = make_shared<Tutorial_Iner_BG>();
	_iner->GetTransform()->SetPosition(CENTER);
	_iner->SetPlayer(_player);

	_button = make_shared<Button>(L"Resource/Texture/CupHead/Button/exitButton.png");
	_button->SetScale({ 1.5f, 1.5f });
	_button->SetPostion(Vector2(640, 350));

	_renderTarget = make_shared <RenderTarget>();
	_rtvQuad = make_shared<Quad>(Vector2(WIN_WIDTH, WIN_HEIGHT));
	_rtvQuad->SetSRV(_renderTarget->GetSRV());
	_rtvQuad->GetTransform()->SetPosition(CENTER);
	_rtvQuad->Update();
}

Tutorial::~Tutorial()
{
}

void Tutorial::Update()
{
	_bg->Update();
	_player->Update();
	_iner->Update();
	
	if(_player->GetBlockCollider()->IsCollision(_iner->GetExitCol()))
		_button->Update();

	for (auto bullet : _player->GetBullets())
	{
		if (bullet->isCollision == true)
		{
			_iner->Damaged(_player->GetATK());
		}
	}
}

void Tutorial::PreRender()
{
	_renderTarget->Set();
	_iner->Render();
	_player->Render();
}

void Tutorial::Render()
{
	_rtvQuad->Render();
}

void Tutorial::PostRender()
{
	_bg->Render();

	if (_player->GetBlockCollider()->IsCollision(_iner->GetExitCol()))
		_button->PostRender();	
	_player->GetHpPNG()->PostRender();
}

