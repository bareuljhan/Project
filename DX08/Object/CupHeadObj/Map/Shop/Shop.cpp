#include "framework.h"
#include "Shop.h"

Shop::Shop()
{
	_transform = make_shared<Transform>();

	CreateAction("Shop_INTRO", Action::Type::END);
	CreateAction("Shop_IDLE", Action::Type::LOOP);
	_actions[WELCOME]->CallBack_TS(std::bind(&Shop::SetIDLE, this));
	
	_bg = make_shared<Quad>(L"Resource/Texture/CupHead/Shop/shop-background.png");

	_table = make_shared<Quad>(L"Resource/Texture/CupHead/Shop/shop_table.png");
	_cutton = make_shared<Quad>(L"Resource/Texture/CupHead/Shop/shop_draped_fabric.png");

	_left = make_shared<Quad>(L"Resource/Texture/CupHead/Shop/shop_drawer_left.png");
	_right = make_shared<Quad>(L"Resource/Texture/CupHead/Shop/shop_drawer_right.png");

	_chalk = make_shared<Quad>(L"Resource/Texture/CupHead/Shop/shop_table_chalkboard.png");
	
	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_transform->SetPosition(Vector2(CENTER_X, CENTER_Y + 78));

	_bg->GetTransform()->SetPosition(Vector2(640, 515));
	_cutton->GetTransform()->SetPosition(Vector2(640, 560));
	_table->GetTransform()->SetPosition(Vector2(640, 140));
	_left->GetTransform()->SetPosition(Vector2(300, 130));
	_right->GetTransform()->SetPosition(Vector2(980, 130));
	_chalk->GetTransform()->SetPosition(Vector2(640, 100));


	_bg->GetTransform()->SetScale(Vector2(0.9f, 0.9f));
	_cutton->GetTransform()->SetScale(Vector2(0.95f, 0.95f));
	_table->GetTransform()->SetScale(Vector2(1.04f, 0.75f));
	_left->GetTransform()->SetScale(Vector2(1.06f, 0.75f));
	_right->GetTransform()->SetScale(Vector2(1.06f, 0.75f));

	_inven = make_shared<Inventory>();

	_oldState = WELCOME;
	_actions[_curState]->Play();
}

Shop::~Shop()
{
	_transform = nullptr;
}

void Shop::Update()
{
	if (KEY_DOWN(VK_RETURN))
	{
		isMove = true;
	}
	if (KEY_DOWN('Q') || KEY_DOWN('q'))
	{
		isReturn = true;
	}

	if (KEY_PRESS('I') || KEY_PRESS('i'))
	{
		_inven->Update();
	}

	TableMove();
	TableReturn();

	_bg->Update();
	_table->Update();
	_cutton->Update();
	_left->Update();
	_right->Update();
	_chalk->Update();

	for (auto sprite : _sprites)
		sprite->Update();
	for (auto action : _actions)
		action->Update();


	_transform->UpdateSRT();
}

void Shop::Render()
{
	_chalk->Render();
	_bg->Render();
	_table->Render();
	_cutton->Render();
	_left->Render();
	_right->Render();

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

	if (KEY_PRESS('I') || KEY_PRESS('i'))
	{
		_inven->Render();
	}
}

void Shop::PostRender()
{
	if (KEY_PRESS('I') || KEY_PRESS('i'))
	{
		_inven->PostRender();
	}
}

void Shop::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void Shop::TableMove()
{
	if (isMove == false) return;
	Vector2 temp = _left->GetTransform()->GetPos();
	Vector2 rTemp = _right->GetTransform()->GetPos();
	temp.x -= _speed * DELTA_TIME;
	rTemp.x += _speed * DELTA_TIME;

	_left->GetTransform()->SetPosition(temp);
	_left->GetTransform()->UpdateSRT();
	_right->GetTransform()->SetPosition(rTemp);
	_right->GetTransform()->UpdateSRT();

	if (temp.x <= -100 && rTemp.x >= 1400)
	{
		isMove = false;
	}
}

void Shop::TableReturn()
{
	if (isReturn == false) return;

	Vector2 temp = _left->GetTransform()->GetPos();
	Vector2 rTemp = _right->GetTransform()->GetPos();
	temp.x += _speed * DELTA_TIME;
	rTemp.x -= _speed * DELTA_TIME;

	_left->GetTransform()->SetPosition(temp);
	_left->GetTransform()->UpdateSRT();
	_right->GetTransform()->SetPosition(rTemp);
	_right->GetTransform()->UpdateSRT();

	if (temp.x >= 300 && rTemp.x <= 980)
	{
		isReturn = false;
	}
}

void Shop::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Shop/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Shop/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
