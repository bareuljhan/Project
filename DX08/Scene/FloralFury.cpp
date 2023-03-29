#include "framework.h"
#include "FloralFury.h"

FloralFury::FloralFury()
{
	_player = make_shared<Player>();
	_player->GetTransform()->SetPosition(Vector2(300, 155));

	_map = make_shared<Stage2_FloralFury>();
	_map->SetPlayer(_player);

	_boss1 = make_shared<Flower>();

	wstring file = L"Resource/Texture/CupHead/Effect/pod_one_planing.png";
	_effect = make_shared<Effect>(file, Vector2(2, 2), Vector2(200, 200), 0.05f);
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(50, 50), 0.05f);

	file = L"Resource/Texture/CupHead/Effect/pod_two_planing.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(50, 50), 0.05f);

	file = L"Resource/Texture/CupHead/Effect/pod_three_planing.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(50, 50), 0.05f);

	file = L"Resource/Texture/CupHead/Effect/AcornDeath.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(70, 70), 0.05f);

	file = L"Resource/Texture/CupHead/Effect/BoomerangDeath.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(120, 120), 0.05f);
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
		for (auto bullet : _boss1->GetBalls())
		{
			if (bullet->Collision(_player->GetBodyCollider()))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
		}
		for (auto bullet : _boss1->GetBullets())
		{
			if (bullet->Collision(_player->GetBodyCollider()))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
		}
		for (auto ball : _boss1->GetPuffBalls())
		{
			if (ball->Collision(_player->GetBodyCollider()))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
		}
		if (_boss1->GetBulletOne()->GetChomperOne()->Collision(_player->GetBodyCollider()))
		{
			_player->GetDamaged(1);
			_player->isInvincible = true;
		}
		if (_boss1->GetBulletThr()->GetChomperTwo()->Collision(_player->GetBodyCollider()))
		{
			_player->GetDamaged(1);
			_player->isInvincible = true;
		}
		if (_boss1->GetBulletTwo()->GetVine()->Collision(_player->GetBodyCollider()))
		{
			_player->GetDamaged(1);
			_player->isInvincible = true;
		}

		for (auto vine : _boss1->GetGround())
		{
			if (vine->Collision(_player->GetBodyCollider()))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
			}
		}
	}

	for (auto bullet : _boss1->GetBalls())
	{
		if (bullet->Collision(_map->GetFloorCollider()) || bullet->Collision(_map->GetSideCollider()) && bullet->GetCurState() != HandATK::State::BOOMERANG)
		{
			EFFECT->Play("AcornDeath", bullet->GetTransform()->GetPos(), false);
			bullet->isEnd = true;
		}
		if (bullet->Collision(_map->GetSideTwoCollider()))
		{
			EFFECT->Play("BoomerangDeath", bullet->GetTransform()->GetPos(), false);
			bullet->isEnd = true;
			bullet->delay = 0.0f;
		}
	}
	if (_boss1->GetBulletOne()->Collision(_map->GetFloorCollider()))
	{
		_boss1->GetBulletOne()->isFloorOne = true;
		EFFECT->Play("pod_one_planing", _boss1->GetBulletOne()->GetTransform()->GetPos(), false);
	}
	if (_boss1->GetBulletTwo()->Collision(_map->GetFloorCollider()))
	{
		_boss1->GetBulletTwo()->isFloorTwo = true;
		EFFECT->Play("pod_two_planing", _boss1->GetBulletTwo()->GetTransform()->GetPos(), false);
	}
	if (_boss1->GetBulletThr()->Collision(_map->GetFloorCollider()))
	{
		_boss1->GetBulletThr()->isFloorThr = true;
		EFFECT->Play("pod_three_planing", _boss1->GetBulletThr()->GetTransform()->GetPos(), false);
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
	for (auto ball : _boss1->GetPuffBalls())
	{
		if (ball->Collision(_map->GetSideCollider()))
		{
			ball->Disable();
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