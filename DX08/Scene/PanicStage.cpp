#include "framework.h"
#include "PanicStage.h"

PanicStage::PanicStage()
{
	_player = make_shared<Player>();
	_player->GetTransform()->SetPosition(Vector2(300, 170));

	_bg = make_shared<Stage1_Panic>();
	_bg->GetTransform()->SetPosition(CENTER);
	_bg->SetPlayer(_player);

	_boss1 = make_shared<Spudder>();
	_boss1->GetTransform()->SetPosition(Vector2(1050, 240));

	_boss2 = make_shared<Vaggie_Carrot>();


	_monster = make_shared<Carrot>();

}

PanicStage::~PanicStage()
{
}

void PanicStage::Update()
{
	_bg->Update();
	_player->Update();
	_boss1->Update();

	if (_boss1->isNextMonster == true)
	{
		_boss2->Update();
		_monster->Update();
		_monster->Move(_player);
	}


	for (auto bullet : _player->GetBullets())
	{
		if (_boss1->GetBodyCollider()->isActive != false)
		{
			if (bullet->Collision(_boss1->GetBodyCollider()))
			{
				_boss1->GetDamaged(_player->GetATK());
			}
		}
		if (_monster->GetBodyCollider()->isActive != false)
		{
			if (bullet->Collision(_monster->GetBodyCollider()))
			{
				_monster->GetDamaged(_player->GetATK());
			}
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
	if (_boss1->isNextMonster == true)
	{
		_boss2->Render();
	}
	_bg->MidleRender();
	_boss1->Render();
	_player->Render();
	if (_boss1->isNextMonster == true)
	{
		_monster->Render();
	}
	_bg->PostRender();

	_player->GetHpPNG()->PostRender();
}
