#include "framework.h"
#include "FloralFury.h"

FloralFury::FloralFury()
{
	_player = make_shared<Player>();
	_player->GetTransform()->SetPosition(Vector2(300, 300));
	_player->SetGravity(6.0f);

	_map = make_shared<Stage2_FloralFury>();
	_map->SetPlayer(_player);

	_boss1 = make_shared<Flower>();

	_win = make_shared<WinScreen>();
	_ready = make_shared<ReadyScreen>();

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

	_button = make_shared<Button>(L"Resource/Texture/CupHead/Button/exitButton.png");
	_button->SetScale({ 1.5f, 1.5f });
	_button->SetPostion(Vector2(640, 350));

	_button->SetEvent(std::bind(&FloralFury::NextScene, this));
}

FloralFury::~FloralFury()
{
}

void FloralFury::Init()
{
}

void FloralFury::Finalize()
{
}

void FloralFury::Update()
{
	if (SCENE->GetValue() >= 0.51f) return;

	if (SCENE->GetValue() >= 0.5f)
	{
		_player->GetAction()->Pause();
		_boss1->GetAction()->Pause();
	}
	else
	{
		if (_ready->isEnd == false)
			_ready->Update();
		_player->GetAction()->Start();
		_boss1->GetAction()->Start();
	}

	_map->Update();
	_boss1->Update();
	_player->Update();


	_boss1->BallAttack(_player);
	if (_boss1->isDead == true)
	{
		_button->Update();
		_win->Update();
	}
	if (_boss1->isDead == true && _win->isEnd == false)
	{
		_player->GetAction()->Pause();
		_boss1->GetAction()->Pause();
	}
	if (_boss1->isDead == true && _win->isEnd == true)
	{
		_player->GetAction()->Start();
		_boss1->GetAction()->Start();
	}
	if (_player->isInvincible == false)
	{
		for (auto bullet : _boss1->GetBalls())
		{
			if (bullet->Collision(_player->GetBodyCollider()))
			{
				_player->GetDamaged(1);
				_player->isInvincible = true;
				bullet->delay = 0.0f;
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
	if (SCENE->GetValue() >= 0.51f) return;

	_map->PreRender();
	_map->Render();
	_boss1->Render();

	_map->PostRender();

	if (_boss1->isDead == true)
	{
		_win->Render();
		_button->PostRender();
	}
	if (_ready->isEnd == false)
		_ready->Render();

}

void FloralFury::PostRender()
{
	if (SCENE->GetValue() >= 0.51f) return;
	_player->Render();
	_player->GetHpPNG()->PostRender();
	ImGui::SliderFloat("PlayerPosX", &_player->GetTransform()->GetPos().y, 0, 1000);
}

void FloralFury::NextScene()
{
	SCENE->SetScene("OverWorld");
	Audio::GetInstance()->Play("MUS_InkwellIsleOne_Piano");
	Audio::GetInstance()->SetVolume("MUS_InkwellIsleOne_Piano", 0.5f);
	Audio::GetInstance()->Play("amb_worldmap_daybirds");
	Audio::GetInstance()->SetVolume("amb_worldmap_daybirds", 0.5f);
}
