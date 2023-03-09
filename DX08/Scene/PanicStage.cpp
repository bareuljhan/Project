#include "framework.h"
#include "PanicStage.h"

PanicStage::PanicStage()
{
	_bg = make_shared<Stage1_Panic>();
	_player = make_shared<Player>();
	_bg->SetPlayer(_player);
	_boss1 = make_shared<Spudder>();

	_player->GetTransform()->GetPos() += Vector2(300, 150);

	_boss1->GetTransform()->GetPos().x += 1050;
	_boss1->GetTransform()->GetPos().y += 240;

}

PanicStage::~PanicStage()
{
}

void PanicStage::Update()
{
	_bg->Update();
	_player->Update();
	_boss1->Update();

	for (auto bullet : _player->GetBullets())
	{
		if (bullet->Collision(_boss1->GetBodyCollider()))
		{
			_boss1->GetDamaged(_player->GetATK());
		}
	}

	for (auto monsterBullet : _boss1->GetBullets())
	{
		if (monsterBullet->Collision(_player->GetBodyCollider()))
		{
			_player->GetDamaged(1);
		}
	}
}

void PanicStage::Render()
{
	_bg->PreRender();
	_bg->Render();
	_player->Render();
	_boss1->Render();
	_bg->PostRender();

	_player->GetHpPNG()->PostRender();
}
