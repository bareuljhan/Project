#include "framework.h"
#include "Flower.h"

Flower::Flower()
{
	_transform = make_shared<Transform>();

	CreateAction("FlowerIntro", Action::Type::END);
	CreateAction("FlowerIdle", Action::Type::PINGPONG);
	CreateAction("FlowerGatling", Action::Type::END);
	CreateAction("FlowerHand", Action::Type::END);
	CreateAction("FlowerTrans", Action::Type::END);
	CreateAction("Phase2IDLE", Action::Type::PINGPONG);
	CreateAction("FlowerSpit", Action::Type::END);
	CreateAction("FlowerDeath", Action::Type::LOOP);

	_actions[GATLING]->PodEffect(std::bind(&Flower::PlayEffect, this));
	_actions[GATLING]->FlowerGround(std::bind(&Flower::PotBallATK, this));

	_actions[HANDATK]->HandEffect(std::bind(&Flower::PlayHandEffect, this));
	_actions[TRANSFORM]->FlowerGround(std::bind(&Flower::GroundEffect, this));

	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_transform);
		sprite->GetTransform()->SetPosition(Vector2(0, 50));
		sprite->GetTransform()->SetScale(Vector2(0.9f, 0.9f));
	}

	_hitCollider = make_shared<RectCollider>(Vector2(200, 200));
	_hitCollider->GetTransform()->SetParent(_transform);
	_hitCollider->GetTransform()->SetPosition(Vector2(40, 150));

	_transform->SetPosition(Vector2(1000, 300));

	_oldState = INTRO;
	_curState = INTRO;

	_actions[_curState]->Play();

	_muzzle = make_shared<Transform>();

	for (int i = 0; i < 3; i++)
	{
		shared_ptr<HandATK> ball = make_shared<HandATK>();
		ball->isActive = false;
		_balls.push_back(ball);

		shared_ptr<PodBullet> bullet = make_shared<PodBullet>();
		bullet->isActive = false;
		_podBullets.push_back(bullet);
	}

	wstring file = L"Resource/Texture/CupHead/Monster/GatlingFX.png";
	_effect = make_shared<Effect>(file, Vector2(2, 2), Vector2(200, 200), 0.05f);
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(200, 200), 0.1f);

	file = L"Resource/Texture/CupHead/Effect/HandFX.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(100, 300), 0.08f);

	file = L"Resource/Texture/CupHead/Effect/FlowerGround.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(800, 130), 0.1f);

	file = L"Resource/Texture/CupHead/Effect/FlowerVine.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(800, 130), 0.11f);

	file = L"Resource/Texture/CupHead/Effect/BossExpension.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(500, 500), 0.06f);

	_mosaicBuffer = make_shared<CupMosaicBuffer>();
}

Flower::~Flower()
{
	_transform = nullptr;
}

void Flower::Update()
{
	if (_mosaicBuffer->_data.value1 == 50) return;

	for (auto bullet : _podBullets)
		bullet->Update();
	
	if (isDead == true)
		Dead();

	_efCheck += DELTA_TIME;
	_vineDelay += DELTA_TIME;

	if (_vineDelay >= 0.5 && (_curState == NEWIDLE || _curState == DEAD || _curState == ATK))
	{
		EFFECT->Play("FlowerVine", Vector2(_transform->GetPos().x - 600, _transform->GetPos().y - 150), false);
		_vineDelay = 0.0f;
	}

	for(auto ball : _balls)
		ball->Update();

	AttackPattern();

	for (auto action : _actions)
		action->Update();
	for (auto sprite : _sprites)
		sprite->Update();

	_transform->UpdateSRT();
}

void Flower::Render()
{
	if (_mosaicBuffer->_data.value1 == 50) return;

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
	
	for (auto bullet : _podBullets)
		bullet->Render();

	for (auto ball : _balls)
		ball->Render();

	if(_curState != INTRO)
		_hitCollider->Render();

}

void Flower::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Flower::AttackPattern()
{
	if (_hp > 300.0f)
	{
		if (_curState == INTRO && _actions[INTRO]->isEnd == true)
		{
			SetIDLE();
			_hitCollider->Update();
			_actions[INTRO]->isEnd = false;
		}
		if (_curState == GATLING && _actions[_curState]->isEnd == true)
		{
			SetIDLE();
			_actions[_curState]->isEnd = false;
		}
		if (_curState == IDLE && _actions[_curState]->isEnd == true && (_count % 3 == 0 || _count % 3 == 2))
		{
			SetHandATK();
			_actions[_curState]->isEnd = false;
		}
		if (_curState == HANDATK && _actions[_curState]->isEnd == true)
		{
			SetIDLE();
			_actions[_curState]->isEnd = false;
		}
		if (_curState == IDLE && _actions[_curState]->isEnd == true && _count % 3 == 1)
		{
			SetGatling();
			_actions[_curState]->isEnd = false;
		}

	}
	else
	{
		if(_curState == INTRO || _curState == IDLE || _curState == GATLING || _curState == HANDATK)
			SetAction(State::TRANSFORM);
		_count = 0;
		if (_curState == TRANSFORM && _actions[_curState]->isEnd == true)
		{
			SetNewIDLE();
			_actions[_curState]->isEnd = false;
		}
		if (_curState == NEWIDLE && _actions[_curState]->isEnd == true)
		{
			SetATK();
			_actions[_curState]->isEnd = false;
		}	
		if (_curState == ATK && _actions[_curState]->isEnd == true)
		{
			SetNewIDLE();
			_actions[_curState]->isEnd = false;
		}
	}
}

void Flower::SetIDLE()
{
	_count++;
	SetAction(State::IDLE);
}

void Flower::SetGatling()
{
	SetAction(State::GATLING);
}

void Flower::SetHandATK()
{
	SetAction(State::HANDATK);
}

void Flower::SetNewIDLE()
{
	SetAction(State::NEWIDLE);
	_count++;
}

void Flower::SetATK()
{
	SetAction(State::ATK);
}

void Flower::PlayEffect()
{
	isUpdate = true;
	EFFECT->Play("GatlingFX", Vector2(950, 650), false);
}

void Flower::PlayHandEffect()
{
	EFFECT->Play("HandFX", Vector2(850, 400), false);
}

void Flower::GroundEffect()
{
	EFFECT->Play("FlowerGround", Vector2(_transform->GetPos().x - 600, _transform->GetPos().y - 150), false);
}

void Flower::GetDamaged(float amount)
{
	if (amount <= 0) return;

	_hp -= amount;
	
	if (_hp <= 0)
	{
		_hp == 0.0;
		isDead = true;
	}
}

void Flower::Dead()
{
	for (auto sprite : _sprites)
	{
		sprite->SetPS(ADD_PS(L"Shader/MosaicPixelShader.hlsl"));
	}
	SetAction(State::DEAD);

	_mosaicBuffer->_data.value1 -= DELTA_TIME;
	_hitCollider->isActive = false;

	if (_efCheck >= 0.8f)
	{
		EFFECT->Play("BossExpension", Vector2(_transform->GetPos().x, _transform->GetPos().y), true);
		_efCheck = 0.0f;
	}
}

void Flower::BallAttack(shared_ptr<Player> player)
{
	if (isDead == true) return;
	if (_curState != HANDATK) return;

	_shootDelay += DELTA_TIME;

	if (_shootDelay >= 1.4)
		_shootDelay = 0.0f;

	if (_count % 3 == 2 && _count == 2)
	{
		if (_shootDelay >= 0.8)
		{
			if (_balls[0]->isActive == false)
			{
				_muzzle->SetPosition(Vector2(850, 500));
				Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
				_balls[0]->SetAction(HandATK::State::BALL);
				_balls[0]->Enable();
				_balls[0]->SetFireDir(dir);
				_balls[0]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			}
			if (_balls[1]->isActive == false && _shootDelay >= 0.9)
			{
				_muzzle->SetPosition(Vector2(850, 400));
				Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
				_balls[1]->SetAction(HandATK::State::BALL);
				_balls[1]->Enable();
				_balls[1]->SetFireDir(dir);
				_balls[1]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			}
			if (_balls[2]->isActive == false && _shootDelay >= 1.1)
			{
				_muzzle->SetPosition(Vector2(850, 300));
				Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
				_balls[2]->SetAction(HandATK::State::BALL);
				_balls[2]->Enable();
				_balls[2]->SetFireDir(dir);
				_balls[2]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			}
		}
	}
	if (_count % 3 == 2 && _count > 2)
	{
		if (_shootDelay >= 1.3)
		{
			if (_balls[0]->isActive == false)
			{
				_muzzle->SetPosition(Vector2(850, 500));
				Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
				_balls[0]->SetAction(HandATK::State::BALL);
				_balls[0]->Enable();
				_balls[0]->SetFireDir(dir);
				_balls[0]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			}
			if (_balls[1]->isActive == false && _shootDelay >= 0.9)
			{
				_muzzle->SetPosition(Vector2(850, 400));
				Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
				_balls[1]->SetAction(HandATK::State::BALL);
				_balls[1]->Enable();
				_balls[1]->SetFireDir(dir);
				_balls[1]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			}
			if (_balls[2]->isActive == false && _shootDelay >= 1.0)
			{
				_muzzle->SetPosition(Vector2(850, 300));
				Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
				_balls[2]->SetAction(HandATK::State::BALL);
				_balls[2]->Enable();
				_balls[2]->SetFireDir(dir);
				_balls[2]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			}
		}
	}

	if (_count % 3 == 0 && _count == 3)
	{
		if (_shootDelay >= 1.2)
		{
			if (_balls[0]->isActive == false)
			{
				_muzzle->SetPosition(Vector2(850, 400));
				Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
				_balls[0]->SetAction(HandATK::State::BOOMERANG);
				_balls[0]->Enable();
				_balls[0]->SetFireDir(dir);
				_balls[0]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			}
		}
	}

	if (_count % 3 == 0 && _count > 3)
	{
		if (_shootDelay >= 1.2)
		{
			if (_balls[0]->isActive == false)
			{
				_muzzle->SetPosition(Vector2(850, 400));
				Vector2 dir = (player->GetTransform()->GetWorldPos() - _muzzle->GetPos()).NormalVector2();
				_balls[0]->SetAction(HandATK::State::BOOMERANG);
				_balls[0]->Enable();
				_balls[0]->SetFireDir(dir);
				_balls[0]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
			}
		}
	}
}

void Flower::PotBallATK()
{
	if (_podBullets[0]->isActive == false)
	{
		_muzzle->SetPosition(Vector2(750, 900));
		_podBullets[0]->Enable();
		_podBullets[0]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
	}
	if (_podBullets[1]->isActive == false)
	{
		_muzzle->SetPosition(Vector2(300, 1100));
		_podBullets[1]->Enable();
		_podBullets[1]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
	}
	if (_podBullets[2]->isActive == false)
	{
		_muzzle->SetPosition(Vector2(500, 800));
		_podBullets[2]->Enable();
		_podBullets[2]->GetTransform()->SetPosition(_muzzle->GetWorldPos());
	}
}

void Flower::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}