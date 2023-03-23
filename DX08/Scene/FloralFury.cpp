#include "framework.h"
#include "FloralFury.h"

FloralFury::FloralFury()
{
	_player = make_shared<Player>();
	_player->GetTransform()->SetPosition(Vector2(300, 155));

	_map = make_shared<Stage2_FloralFury>();
	_map->SetPlayer(_player);

	_boss1 = make_shared<Flower>();
}

FloralFury::~FloralFury()
{
}

void FloralFury::Update()
{
	_map->Update();
	_boss1->Update();
	_player->Update();

	_boss1->BallAttack(_player);
	if (_player->isInvincible == false)
	{
		if (_boss1->GetPodBullet()->GetColliderOne()->isActive == true)
		{
			if (_boss1->GetPodBullet()->GetColliderOne()->IsCollision(_player->GetBodyCollider(), 0))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
			//else if (_boss1->GetPodBullet()->GetColliderOne()->IsCollision(_map->GetFloorCollider(), 0))
			//{

			//}
			if (_boss1->GetPodBullet()->GetColliderTwo()->IsCollision(_player->GetBodyCollider(), 1))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
			if (_boss1->GetPodBullet()->GetColliderThr()->IsCollision(_player->GetBodyCollider(), 2))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
		}
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
	}
}
 
void FloralFury::Render()
{
	_map->PreRender();
	_map->Render();
	_boss1->Render();


	_map->PostRender();


}

void FloralFury::PostRender()
{
	_player->Render();
	_player->GetHpPNG()->PostRender();
	ImGui::SliderFloat("PlayerPosX", &_player->GetTransform()->GetPos().y, 0, 1000);
}
