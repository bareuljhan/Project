#include "framework.h"
#include "PanicStage.h"

PanicStage::PanicStage()
{
	_player = make_shared<Player>();
	_player->GetTransform()->SetPosition(Vector2(300, 800));

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
		_boss2->BulletAttack(_player);
		_boss2->BeamAttack(_player);
		_monster->Move(_player);
	}

	for (auto bullet : _player->GetBullets())
	{
		//if (_player->isDead == true) break;

		if (_boss1->GetBodyCollider()->isActive != false)
		{
			if (bullet->Collision(_boss1->GetBodyCollider()))
			{
				_boss1->GetDamaged(_player->GetATK());
			}
		}
		if (_monster->GetBodyCollider()->isActive != false && _boss1->isNextMonster == true)
		{
			if (bullet->Collision(_monster->GetBodyCollider()))
			{
				_monster->GetDamaged(_player->GetATK());
			}
		}
		if (_boss2->BulletOneCollider()->isActive != false && _boss1->isNextMonster == true)
		{
			if (bullet->Collision(_boss2->BulletOneCollider()))
				_boss2->GetBulletOne()->GetDamage(_player->GetATK());
		}	
		if (_boss2->BulletTwoCollider()->isActive != false && _boss1->isNextMonster == true)
		{
			if (bullet->Collision(_boss2->BulletTwoCollider()))
				_boss2->GetBulletTwo()->GetDamage(_player->GetATK());
		}
		if (_boss2->GetBodyCollider()->isActive != false && _boss1->isNextMonster == true)
		{
			if (bullet->Collision(_boss2->GetBodyCollider()))
			{
				_boss2->GetDamaged(_player->GetATK());
			}
		}
	}

	if (_player->isInvincible == false)
	{
		for (auto monsterBullet : _boss1->GetBullets())
		{
			if (_boss1->isDead == true) break;

			if (monsterBullet->Collision(_player->GetBodyCollider()))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
		}

		for (auto monsterbullet : _boss2->GetBullets())
		{
			if (_boss2->isDead == true) break;

			if (monsterbullet->Collision(_player->GetBlockCollider()))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
		}

		if (_monster->GetBodyCollider()->IsCollision(_player->GetBodyCollider()) && _monster->isDead == false)
		{
			_player->GetDamaged(1);
			if (_player->GetTransform()->GetPos().x >= _monster->GetTransform()->GetPos().x)
			{
				_player->GetTransform()->SetPosition(Vector2(_player->GetTransform()->GetPos().x + 80, _player->GetTransform()->GetPos().y));
				_player->isInvincible = true;
			}
			else
			{
				_player->GetTransform()->SetPosition(Vector2(_player->GetTransform()->GetPos().x - 80, _player->GetTransform()->GetPos().y));
				_player->isInvincible = true;
			}
		}

		for (auto beam : _boss2->GetBeams())
		{
			if (_boss2->isDead == true) break;

			if (beam->Collision(_player->GetBodyCollider()))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
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
	_player->Render();
	_boss1->Render();

	if (_boss1->isNextMonster == true)
	{
		_monster->Render();
	}
	_bg->PostRender();

	_boss2->BulletRender();


	_player->GetHpPNG()->PostRender();
}
