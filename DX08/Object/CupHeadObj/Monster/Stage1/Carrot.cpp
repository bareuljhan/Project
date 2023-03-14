#include "framework.h"
#include "Carrot.h"

Carrot::Carrot()
{
	_transform = make_shared<Transform>();

	CreateAction("Carret_Intro", Action::Type::END);
	CreateAction("Carret_IDLE", Action::Type::END);
	CreateAction("Carret_Move", Action::Type::PINGPONG);
	CreateAction("Carret_Dead", Action::Type::LOOP);

	_actions[0]->CallBack_Carret(std::bind(&Carrot::SetIDLE, this));
	_actions[1]->CarretMove_CallBack(std::bind(&Carrot::SetMove, this));

	for (auto sprite : _sprites)
	{
		sprite->GetTransform()->SetParent(_transform);
		sprite->GetTransform()->GetScale() *= 0.8f;
	}

	_collider = make_shared<RectCollider>(Vector2(100, 100));
	_collider->GetTransform()->SetParent(_transform);

	_oldState = State::INTRO;
	_actions[State::INTRO]->Play();

	_mosaicBuffer = make_shared<CupMosaicBuffer>();
	_mosaicBuffer->_data.value1 = 2500;
}

Carrot::~Carrot()
{
}

void Carrot::Update()
{
	if (_mosaicBuffer->_data.value1 == 0) return;

	_collider->Update();

	if (isDead == true)
		Dead();

	for (auto action : _actions)
		action->Update();
	for (auto sprite : _sprites)
		sprite->Update();

	_transform->UpdateSRT();
}

void Carrot::Render()
{
	if (_mosaicBuffer->_data.value1 == 0) return;

	_mosaicBuffer->SetPSBuffer(2);

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	_collider->Render();
}

void Carrot::SetMove()
{
	SetAction(State::MOVE);

	this->GetTransform()->GetPos().y -= 20.0f;
}

void Carrot::GetDamaged(float amount)
{
	if (amount <= 0) return;

	_hp -= amount;

	if (_hp <= 0)
	{
		_hp = 0.0f;
		isDead = true;
		_collider->isActive = false;
	}
}

void Carrot::Dead()
{
	for (auto sprite : _sprites)
	{
		sprite->SetPS(ADD_PS(L"Shader/MosaicPixelShader.hlsl"));
	}
	SetAction(State::DEAD);
	
	_mosaicBuffer->_data.value1 -= DELTA_TIME;

}

void Carrot::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Carrot::SetIDLE()
{
	SetAction(State::IDLE);
}

void Carrot::Move(shared_ptr<Player> player)
{
	if (_curState != MOVE) return;
	if (player->isDead == true) return;

	Vector2 dir = (player->GetTransform()->GetWorldPos() - _transform->GetPos()).NormalVector2();

	_transform->GetPos().x += dir.x * _speed * DELTA_TIME;
}

void Carrot::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Monster/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Monster/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "Monster_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
