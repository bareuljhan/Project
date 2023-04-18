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

	_oldState = WELCOME;
	_actions[_curState]->Play();

	SetStoreItems();

	_icons[0]->SetPosition(Vector2(280, 130));
	_icons[1]->SetPosition(Vector2(780, 130));

	for (int i = 0; i < 5; i++)
	{
		shared_ptr<Coin> coin = make_shared<Coin>();
		coin->GetTransform()->SetScale(Vector2(0.2f, 0.2f));
		_coins.push_back(coin);
	}
	_coins[0]->GetTransform()->SetPosition(Vector2(360, 100));
	_coins[1]->GetTransform()->SetPosition(Vector2(410, 100));
	_coins[2]->GetTransform()->SetPosition(Vector2(860, 100));
	_coins[3]->GetTransform()->SetPosition(Vector2(910, 100));
	_coins[4]->GetTransform()->SetPosition(Vector2(960, 100));

	_buyButton = make_shared<Button>(L"Resource/Texture/CupHead/Shop/Buy.png");
	_buyButton->SetPostion(Vector2(200, 250));
	_buyButton->SetScale(Vector2(0.5f, 0.5f));
	_buyButton->SetEvent(std::bind(&Shop::Buy, this));

	_sellButton = make_shared<Button>(L"Resource/Texture/CupHead/Shop/Sell.png");
	_sellButton->SetPostion(Vector2(400, 255));
	_sellButton->SetScale(Vector2(0.4f, 0.4f));
	_sellButton->SetEvent(std::bind(&Shop::Sell, this));
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

	TableMove();
	TableReturn();

	for (auto icon : _icons)
		icon->Update();

	_bg->Update();
	_table->Update();
	_cutton->Update();
	_left->Update();
	_right->Update();
	_chalk->Update();

	_buyButton->Update();
	_sellButton->Update();

	for (auto coin : _coins)
		coin->Update();
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

	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();

}

void Shop::PostRender()
{
	RECT rect;
	rect.left = 350;
	rect.right = 550;
	rect.top = 550;
	rect.bottom = 650;

	RECT rect1;
	rect1.left = 850;
	rect1.right = 1050;
	rect1.top = 550;
	rect1.bottom = 650;

	if (_left->GetTransform()->GetPos().x <= 100 && _right->GetTransform()->GetPos().x >= 1150)
	{
		DirectWrite::GetInstance()->RenderText(L"Need Coin", rect);
		DirectWrite::GetInstance()->RenderText(L"Need Coin", rect1);
	}
	
	for (auto icon : _icons)
		icon->Render();
	for (auto coin : _coins)
		coin->Render();

	_buyButton->PostRender();
	_sellButton->PostRender();
	_left->Render();
	_right->Render();
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

void Shop::SetStoreItems()
{
	for (int i = 0; i < 2; i++)
	{
		shared_ptr<ItemIconButton> icon = make_shared<ItemIconButton>();
		icon->SetScale(Vector2(0.9f, 0.9f));
		icon->GetButton()->SetIntEvent(std::bind(&Inventory::SetCurIndex, this, i));
		_icons.push_back(icon);
	}

	_itemDates[0] = DATA_M->GetItemByName("Postion");
	_itemDates[1] = DATA_M->GetItemByName("Coffee");
	_icons[0]->SetItem(_itemDates[0]);
	_icons[1]->SetItem(_itemDates[1]);
}	

void Shop::Buy()
{
	if (!ValidIndex()) return;

	if (INVEN_M->GetInven()->AddItem(_itemDates[_curIndex].name))
		INVEN_M->GetInven()->SubMoney(_itemDates[_curIndex].price);
}

void Shop::Sell()
{
	INVEN_M->GetInven()->SellItem();
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
