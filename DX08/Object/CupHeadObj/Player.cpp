#include "framework.h"
#include "Player.h"

Player::Player()
{
	_transform = make_shared<Transform>();

	CreateAction("Idle", Action::Type::LOOP);
	CreateAction("Run", Action::Type::LOOP);
	CreateAction("Jump", Action::Type::LOOP);
	CreateAction("DuckIdle", Action::Type::LOOP);
	CreateAction("AimStraightShot", Action::Type::END);
	CreateAction("AimUpShot", Action::Type::LOOP);
	CreateAction("AimDiagonalUpShot", Action::Type::LOOP);
	CreateAction("DuckShot", Action::Type::END);
	CreateAction("GroundDash", Action::Type::LOOP);
	CreateAction("AirStraightReadySpecial", Action::Type::END);
	CreateAction("RunShot", Action::Type::END);

	_actions[State::DUCKSHOT]->SetCallBack(std::bind(&Player::SetDUCK, this));
	_actions[State::SHOT]->SetCallBack(std::bind(&Player::SetIDLE, this));
	_actions[State::SKILLSHOT]->SetCallBack(std::bind(&Player::SetIDLE, this));
	_actions[State::SKILLSHOT]->SetCallBack_Skill(std::bind(&Player::SkillShot, this));
	_actions[State::RUNSHOT]->SetCallBack(std::bind(&Player::SetRun, this));

	_blockCollider = make_shared<CircleCollider>(73);
	_blockCollider->GetTransform()->GetPos().y -= 100;


	_transform = _blockCollider->GetTransform();

	_hitCollider = make_shared<RectCollider>(Vector2(100, 100));
	_hitCollider->SetRed();
	_hitCollider->GetTransform()->SetParent(_transform);

	_origin = _hitCollider->GetTransform()->GetScale();
	_originPos = _hitCollider->GetTransform()->GetPos();

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	for (int i = 0; i < _poolCount; i++)
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		bullet->isActive = false;
		_bullets.push_back(bullet);
	}

	_muzzle = make_shared<Transform>();
	_muzzle->SetParent(_transform);
	_muzzle->GetPos().x = 50;

	_oldState = State::IDLE;
	_actions[State::IDLE]->Play();

	wstring file = L"Resource/Texture/CupHead/Effect/DashDust.png";
	_effect = make_shared<Effect>(file, Vector2(2, 2), Vector2(200, 200), 0.05f);
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(70, 70), 0.05f);

	file = L"Resource/Texture/CupHead/Effect/muzzleEffect.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(70, 70), 0.06f);

	file = L"Resource/Texture/CupHead/Effect/JumpDust.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(200, 100), 0.06f);

	file = L"Resource/Texture/CupHead/Effect/SpecialShootEffect.png";
	EFFECT->AddEffect(file, Vector2(2, 2), Vector2(200, 200), 0.06f);

	_health = make_shared<Hp>(Vector2(80, 40));
	_health->SetPosition(Vector2(50, 50));
}

Player::~Player()
{
	_transform = nullptr;
}

void Player::Update()
{
	_blockCollider->Update();
	_hitCollider->Update();

	SetColliderSize();
	SkillAction();
	DuckShot();
	DiagonalShot();
	AimUpShot();
	Shot();
	Jump();
	Input();

	for (auto bullet : _bullets)
		bullet->Update();

	_effect->Update();

	_sprites[_curState]->Update();
	_actions[_curState]->Update();

	_transform->UpdateSRT();



	_health->Update();

	_health->SetRatio(1.0f);

	if (_hp < 4 && _hp > 2)
	{
		_health->SetFour();
		_health->SetRatio(0.0f);
		_health->Update();
	}
	else if (_hp < 3 && _hp > 1)
	{
		_health->SetThree();
		_health->SetRatio(0.0f);
		_health->Update();
	}
	else if (_hp < 2 && _hp > 0)
	{
		_health->SetTwo();
		_health->SetRatio(0.0f);
		_health->Update();
	}

}

void Player::Render()
{
	for (auto bullet : _bullets)
		bullet->Render();

	_effect->Render();

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_blockCollider->Render();
	_hitCollider->Render();

}

void Player::SetRight()
{
	_isRight = true;

	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 0;
	}
}

void Player::SetLeft()
{
	_isRight = false;

	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 1;
	}
}

void Player::Input()
{
	if (_curState == State::SHOT || _curState == State::JUMP)
		return;

	if (KEY_PRESS('A'))
	{
		if (_curState == GROUNDDASH) return;

		if (_curState != State::JUMP)
			SetAction(State::RUN);

		_transform->GetPos().x -= _speed * DELTA_TIME;

		EFFECT->Play("DashDust", Vector2(_transform->GetPos().x + 50.0f, _transform->GetPos().y - 40.0f), true);

		SetLeft();
	}
	if (KEY_PRESS('A') && KEY_PRESS(VK_SHIFT))
	{
		if (_curState != State::JUMP)
			SetAction(State::GROUNDDASH);
		_transform->GetPos().x -= _dashSpeed * DELTA_TIME;
	}
	if (KEY_PRESS('D'))
	{
		if (_curState == GROUNDDASH) return;

		_transform->GetPos().x += _speed * DELTA_TIME;
		if (_curState != State::JUMP)
			SetAction(State::RUN);

		EFFECT->Play("DashDust", Vector2(_transform->GetPos().x - 50.0f, _transform->GetPos().y - 40.0f), false);

		SetRight();
	}
	if (KEY_PRESS('D') && KEY_PRESS(VK_SHIFT))
	{
		if (_curState != State::JUMP)
			SetAction(State::GROUNDDASH);
		_transform->GetPos().x -= _dashSpeed * DELTA_TIME;
	}
	if (KEY_PRESS('S'))
	{
		if (_curState != State::JUMP && _curState != State::RUN)
		{
			SetAction(State::DUCK);
		}
	}

	if (KEY_PRESS('Z'))
	{
		if (_curState == GROUNDDASH) return;

		if (_curState != State::JUMP)
			SetAction(State::RUNSHOT);

		_transform->GetPos().x -= _speed * DELTA_TIME;
		EFFECT->Play("DashDust", Vector2(_transform->GetPos().x + 50.0f, _transform->GetPos().y - 40.0f), true);
		Vector2 dir = Vector2(-1, 0);
		_muzzle->GetPos().x = -50;
		_muzzle->GetPos().y = -15;
		if (KEY_DOWN(VK_LBUTTON))
		{
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
		SetLeft();
	}
	if (KEY_PRESS('C'))
	{
		if (_curState == GROUNDDASH) return;

		if (_curState != State::JUMP)
			SetAction(State::RUNSHOT);

		_transform->GetPos().x += _speed * DELTA_TIME;
		EFFECT->Play("DashDust", Vector2(_transform->GetPos().x - 50.0f, _transform->GetPos().y - 40.0f), false);
		Vector2 dir = Vector2(1, 0);
		_muzzle->GetPos().x = 50;
		_muzzle->GetPos().y = -15;
		if (KEY_DOWN(VK_LBUTTON))
		{
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
		SetRight();
	}

	if (KEY_UP('A') || KEY_UP('D') || KEY_UP('S') || KEY_UP('Z') || KEY_UP('C'))
	{
		if (_curState != State::JUMP)
			SetAction(State::IDLE);
	}
}

void Player::Jump()
{
	if (KEY_DOWN(VK_SPACE))
	{
		_jumpPower = 500.0f;
		SetAction(State::JUMP);
	}

	_transform->GetPos().y += _jumpPower * DELTA_TIME;

	if (KEY_PRESS('A') && _curState == State::JUMP)
	{
		_transform->GetPos().x -= DELTA_TIME * _speed;
		SetLeft();
	}

	if (KEY_PRESS('D') && _curState == State::JUMP)
	{
		_transform->GetPos().x += DELTA_TIME * _speed;
		SetRight();
	}
	if (_curState == SHOT)
		return;

	if (_curState == JUMP && _isGround == true && _jumpPower <= 0.0f)
	{
		SetAction(IDLE);
		EFFECT->Play("JumpDust", Vector2(_transform->GetPos().x, _transform->GetPos().y - 30.0f), false);
	}
}

void Player::Shot()
{
	if (_curState != IDLE)
		return;

	if (KEY_DOWN(VK_LBUTTON))
	{
		SetAction(State::SHOT);
		_atk = 10.0f;
		if (_isRight)
		{
			Vector2 dir = Vector2(1, 0);
			_muzzle->GetPos().x = 50;
			_muzzle->GetPos().y = 0;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
		else
		{
			Vector2 dir = Vector2(-1, 0);
			_muzzle->GetPos().x = -50;
			_muzzle->GetPos().y = 0;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
	}
}

void Player::AimUpShot()
{
	if (_curState == JUMP) return;

	if (KEY_PRESS('W') && KEY_DOWN(VK_LBUTTON))
	{
		SetAction(State::AIMUPSHOT);
		_atk = 10.0f;
		if (_isRight)
		{
			Vector2 dir = Vector2(0, 1);
			_muzzle->GetPos().y = 50;
			_muzzle->GetPos().x = 25;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
		else
		{
			Vector2 dir = Vector2(0, 1);
			_muzzle->GetPos().y = 50;
			_muzzle->GetPos().x = -25;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
	}
	else if (KEY_UP('W'))
		SetIDLE();
}

void Player::DiagonalShot()
{
	if (_curState == JUMP) return;

	if (KEY_PRESS('E') && KEY_DOWN(VK_LBUTTON))
	{
		SetAction(State::DIAGONALSHOT);
		_atk = 10.0f;
		if (_isRight)
		{

			Vector2 dir = Vector2(1, 1);
			_muzzle->GetPos().y = 50;
			_muzzle->GetPos().x = 70;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
		else
		{
			Vector2 dir = Vector2(-1, 1);
			_muzzle->GetPos().y = 50;
			_muzzle->GetPos().x = -70;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
	}
	else if (KEY_UP('E'))
		SetIDLE();
}

void Player::DuckShot()
{
	if (_curState == JUMP) return;

	if (KEY_PRESS('X') && KEY_DOWN(VK_LBUTTON))
	{
		SetAction(State::DUCKSHOT);
		_atk = 10.0f;
		if (_isRight)
		{
			Vector2 dir = Vector2(1, 0);
			_muzzle->GetPos().y = -50;
			_muzzle->GetPos().x = 50;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
		else
		{
			Vector2 dir = Vector2(-1, 0);
			_muzzle->GetPos().y = -50;
			_muzzle->GetPos().x = -50;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("muzzleEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::BASIC);
					bullet->SetOldState(Bullet::State::SPECIAL);
					bullet->SetAction(Bullet::State::BASIC);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
	}
	else if(KEY_UP('X'))
		SetIDLE();
}

void Player::SkillShot()
{
	if (_curState == State::JUMP) return;
	if (_curState == State::IDLE) return;
	_atk = 40.0f;
		if (_isRight)
		{
			Vector2 dir = Vector2(1, 0);
			_muzzle->GetPos().x = 50;
			_muzzle->GetPos().y = 0;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("SpecialShootEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::SPECIAL);
					bullet->SetOldState(Bullet::State::BASIC);
					bullet->SetAction(Bullet::State::SPECIAL);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
		else
		{
			Vector2 dir = Vector2(-1, 0);
			_muzzle->GetPos().x = -50;
			_muzzle->GetPos().y = 0;
			for (auto bullet : _bullets)
			{
				if (bullet->isActive == false)
				{
					EFFECT->Play("SpecialShootEffect", _muzzle->GetWorldPos(), false);
					bullet->SetCurState(Bullet::State::SPECIAL);				
					bullet->SetOldState(Bullet::State::BASIC);
					bullet->SetAction(Bullet::State::SPECIAL);
					bullet->Enable();
					bullet->SetFireDir(dir);
					bullet->GetTransform()->GetPos() = _muzzle->GetWorldPos();
					bullet->GetTransform()->Update();
					break;
				}
			}
		}
		
}

void Player::SkillAction()
{
	if (KEY_UP(VK_RBUTTON))
	{
		SetAction(State::SKILLSHOT);
	}
}

void Player::Ground()
{
	
	_jumpPower = 0.0f;
	_isGround = true;
}

void Player::NGround()
{
	_jumpPower -= GRAVITY * GRAVITY * DELTA_TIME;
	_isGround = false;
}

void Player::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Player::SetIDLE()
{
	SetAction(State::IDLE);
}

void Player::SetRun()
{
	SetAction(State::RUN);
}

void Player::SetDUCK()
{
	SetAction(State::DUCK);
}

void Player::SetColliderSize()
{
	if (_curState == DUCK || _curState == DUCKSHOT)
	{
		_hitCollider->GetTransform()->GetScale() = Vector2(1.0f, 0.5f);
		_hitCollider->GetTransform()->GetPos() = Vector2(0.0f, -40.0f);
	}
	else
	{
		_hitCollider->GetTransform()->GetScale() = _origin;
		_hitCollider->GetTransform()->GetPos() = _originPos;
	}
}

void Player::GetDamaged(float amount)
{
	if (amount == 0.0f) return;
	
	_hp -= amount;
	if (_hp <= 0.0f)
	{
		_hp == 0.0f;
	}
}

void Player::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
