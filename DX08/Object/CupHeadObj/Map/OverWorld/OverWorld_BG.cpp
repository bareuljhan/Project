#include "framework.h"
#include "OverWorld_BG.h"

OverWorld_BG::OverWorld_BG()
{
	CreateHome("home");
	CreatePanic("Panic");
	CreateShip("ship");
	CreateShop("shop");
	CreateMausoleum("Mausoleum");
	CreateOoze("Ooze");
	CreateZeppelin("Zeppelin");	
	CreateDieHouse("DieHouse");

	CreateRoute();


	_home->GetTransform()->GetScale() *= 0.25f;
	_home->GetTransform()->SetPosition(Vector2(250, 470));
	_homeAction->Play();
	
	_panic->GetTransform()->GetScale() *= 0.25f;
	_panic->GetTransform()->SetPosition(Vector2(585, 228));
	_panicAction->Play();

	_ship->GetTransform()->GetScale() *= 0.25f;
	_ship->GetTransform()->SetPosition(Vector2(665, 110));
	_shipAction->Play();

	_shop->GetTransform()->GetScale() *= 0.25f;
	_shop->GetTransform()->SetPosition(Vector2(705, 345));
	_shopAction->Play();

	_mausoleum->GetTransform()->GetScale() *= 0.21f;
	_mausoleum->GetTransform()->SetPosition(Vector2(1015, 191));
	_mausoleumAction->Play();

	_ooze->GetTransform()->GetScale() *= 0.35f;
	_ooze->GetTransform()->SetPosition(Vector2(690, 500));
	_oozeWaveAction->Play();

	_zeppelin->GetTransform()->GetScale() *= 0.35f;
	_zeppelin->GetTransform()->SetPosition(Vector2(1020, 620));
	_zeppelinAction->Play();
	
	_dieHouse->GetTransform()->GetScale() *= 0.35f;
	_dieHouse->GetTransform()->SetPosition(Vector2(1220, 320));
	_dieHouseAction->Play();


	_seaRight = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Ocean/oceanRight.png");
	_seaRight->GetTransform()->SetPosition(Vector2(CENTER_X + 313, CENTER_Y));
	_seaRight->GetTransform()->GetScale() *= 0.35f;

	_seaLeft = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Ocean/oceanLeft.png");
	_seaLeft->GetTransform()->GetScale() *= 0.35;
	_seaLeft->GetTransform()->SetPosition(Vector2(320, 360));

	_leftMain = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_large_left.png");
	_leftMain->GetTransform()->GetScale() *= 0.31;
	_leftMain->GetTransform()->SetPosition(Vector2(668.0f, 391.0f));

	_rightMain = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_large_right.png");
	_rightMain->GetTransform()->GetScale() *= 0.31;
	_rightMain->GetTransform()->SetPosition(Vector2(1051.0f, 385.0f));

	_leftSide = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_small_island_main.png");
	_leftSide->GetTransform()->GetScale() *= 0.31;
	_leftSide->GetTransform()->SetPosition(Vector2(300.0f, 405.0f));

	_islandTree = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_tree_island.png");
	_islandTree->GetTransform()->GetScale() *= 0.35f;
	_islandTree->GetTransform()->SetPosition(Vector2(750.0f, 90.0f));

	_sideDock = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_dock.png");
	_sideDock->GetTransform()->GetScale() *= 0.3f;
	_sideDock->GetTransform()->SetPosition(Vector2(170.0f, 295.0f));

	_sideBoat = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_boat.png");
	_sideBoat->GetTransform()->GetScale() *= 0.26f;
	_sideBoat->GetTransform()->SetPosition(Vector2(135.0f, 295.0f));

	_lightHouse = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_lighthouse.png");
	_lightHouse->GetTransform()->GetScale() *= 0.3f;
	_lightHouse->GetTransform()->SetPosition(Vector2(93.0f, 530.0f));

	_buoy = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_buoy.png");
	_buoy->GetTransform()->GetScale() *= 0.3f;
	_buoy->GetTransform()->SetPosition(Vector2(33.0f, 430.0f));

	_mainBridge = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_bridge_main.png");
	_mainBridge->GetTransform()->GetScale() *= 0.3f;
	_mainBridge->GetTransform()->SetPosition(Vector2(505.0f, 375.0f));

	_frogsBridge = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_bridge_frogs.png");
	_frogsBridge->GetTransform()->GetScale() *= 0.3f;
	_frogsBridge->GetTransform()->SetPosition(Vector2(845.0f, 270.0f));

	_slimeStairs = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_stairs_slime.png");
	_slimeStairs->GetTransform()->GetScale() *= 0.35f;
	_slimeStairs->GetTransform()->SetPosition(Vector2(1020.0f, 540.0f));

	_slimeStairs2 = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_stairs_slime.png");
	_slimeStairs2->GetTransform()->GetScale() *= 0.28f;
	_slimeStairs2->GetTransform()->SetPosition(Vector2(640.0f, 530.0f));

	_rightStairs = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_stairs_king_dice.png");
	_rightStairs->GetTransform()->GetScale() *= 0.25f;
	_rightStairs->GetTransform()->SetPosition(Vector2(1080.0f, 370.0f));

	_veggieStairs = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_stairs_veggie.png");
	_veggieStairs->GetTransform()->GetScale() *= 0.22f;
	_veggieStairs->GetTransform()->SetPosition(Vector2(670.0f, 210.0f));

	_bridge = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_bridge.png");
	_bridge->GetTransform()->GetScale() *= 0.22f;
	_bridge->GetTransform()->SetPosition(Vector2(926.0f, 580.0f));


	_bridge2 = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/world1_bridge2.png");
	_bridge2->GetTransform()->GetScale() *= 0.27f;
	_bridge2->GetTransform()->SetPosition(Vector2(740.0f, 420.0f));

}

OverWorld_BG::~OverWorld_BG()
{
}

void OverWorld_BG::Update()
{
	_seaLeft->Update();
	_seaRight->Update();
	_leftMain->Update();
	_rightMain->Update();
	_leftSide->Update();
	_islandTree->Update();
	_sideDock->Update();
	_sideBoat->Update();
	_lightHouse->Update();
	_buoy->Update();
	_mainBridge->Update();
	_frogsBridge->Update();
	_slimeStairs->Update();
	_slimeStairs2->Update();
	_rightStairs->Update();
	_veggieStairs->Update();
	_bridge->Update();
	_bridge2->Update();
	_homeAction->Update();
	_home->Update();
	_panicAction->Update();
	_panic->Update();
	_shipAction->Update();
	_ship->Update();
	_shopAction->Update();
	_shop->Update();
	_mausoleumAction->Update();
	_mausoleum->Update();
	_oozeWaveAction->Update();
	_ooze->Update();	
	_zeppelinAction->Update();
	_zeppelin->Update();
	_dieHouseAction->Update();
	_dieHouse->Update();
	for (auto block : _blocks)
	{
		block->Update();
	}
}

void OverWorld_BG::Render()
{
	_seaLeft->Render();
	_seaRight->Render();
	_lightHouse->Render();
	_leftMain->Render();
	_rightMain->Render();
	_leftSide->Render();
	_home->SetActionClip(_homeAction->GetCurClip());
	_home->Render();
	_panic->SetActionClip(_panicAction->GetCurClip());
	_panic->Render();
	_ship->SetActionClip(_shipAction->GetCurClip());
	_ship->Render();
	_shop->SetActionClip(_shopAction->GetCurClip());
	_shop->Render();	
	_mausoleum->SetActionClip(_mausoleumAction->GetCurClip());
	_mausoleum->Render();
	_ooze->SetActionClip(_oozeWaveAction->GetCurClip());
	_ooze->Render();
	_zeppelin->SetActionClip(_zeppelinAction->GetCurClip());
	_zeppelin->Render();
	_dieHouse->SetActionClip(_dieHouseAction->GetCurClip());
	_dieHouse->Render();
	_islandTree->Render();
	_sideDock->Render();
	_sideBoat->Render();
	_buoy->Render();
	_mainBridge->Render();
	_frogsBridge->Render();
	_slimeStairs->Render();
	_slimeStairs2->Render();
	_rightStairs->Render();
	_veggieStairs->Render();
	_bridge->Render();
	_bridge2->Render();

	for (auto block : _blocks)
	{
		block->Render();
	}
}

void OverWorld_BG::CreateHome(string name)
{
	string xmlPath = "Resource/XML/OverWorld/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Map/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_homeAction = make_shared<Action>(xml.GetClips(), actionName);
	_home = make_shared<Sprite>(srvPath, xml.AverageSize());
}

void OverWorld_BG::CreatePanic(string name)
{
	string xmlPath = "Resource/XML/OverWorld/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Map/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_panicAction = make_shared<Action>(xml.GetClips(), actionName);
	_panic = make_shared<Sprite>(srvPath, xml.AverageSize());
}

void OverWorld_BG::CreateShip(string name)
{
	string xmlPath = "Resource/XML/OverWorld/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Map/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_shipAction = make_shared<Action>(xml.GetClips(), actionName);
	_ship = make_shared<Sprite>(srvPath, xml.AverageSize());
}

void OverWorld_BG::CreateShop(string name)
{
	string xmlPath = "Resource/XML/OverWorld/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Map/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_shopAction = make_shared<Action>(xml.GetClips(), actionName);
	_shop = make_shared<Sprite>(srvPath, xml.AverageSize());
}

void OverWorld_BG::CreateMausoleum(string name)
{
	string xmlPath = "Resource/XML/OverWorld/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Map/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_mausoleumAction = make_shared<Action>(xml.GetClips(), actionName);
	_mausoleum = make_shared<Sprite>(srvPath, xml.AverageSize());
}

void OverWorld_BG::CreateOoze(string name)
{
	string xmlPath = "Resource/XML/OverWorld/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Map/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_oozeWaveAction = make_shared<Action>(xml.GetClips(), actionName);
	_ooze = make_shared<Sprite>(srvPath, xml.AverageSize());
}

void OverWorld_BG::CreateZeppelin(string name)
{
	string xmlPath = "Resource/XML/OverWorld/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Map/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_zeppelinAction = make_shared<Action>(xml.GetClips(), actionName);
	_zeppelin = make_shared<Sprite>(srvPath, xml.AverageSize());
}

void OverWorld_BG::CreateDieHouse(string name)
{
	string xmlPath = "Resource/XML/OverWorld/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Map/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_dieHouseAction = make_shared<Action>(xml.GetClips(), actionName);
	_dieHouse = make_shared<Sprite>(srvPath, xml.AverageSize());
}

void OverWorld_BG::CreateRoute()
{
	for (int x = 0; x < 30; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			shared_ptr<Quad> block = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/AbleQuad.png");
			block->SetType(Quad::Type::DISABLE);
			block->GetTransform()->SetPosition(Vector2(230, 150));
			Vector2 distance = Vector2(32.9f * x, 32.9f * y);
			block->GetTransform()->GetScale() *= 0.21f;
			block->GetTransform()->SetPosition(block->GetTransform()->GetPos() + distance);
			_blocks.push_back(block);
		}
	}
	for (int i = 35; i < 40; i++)
	{
		_blocks[i]->SetType(Quad::Type::ABLE);
	}
	for (int i = 180; i < 192; i++)
	{
		_blocks[i]->SetType(Quad::Type::ABLE);
	}	
	for (int i = 206; i < 237; i+=15)
	{
		_blocks[i]->SetType(Quad::Type::ABLE);
	}
	for (int i = 237; i < 358; i+=15)
	{
		_blocks[i]->SetType(Quad::Type::ABLE);
	}	
	for (int i = 356; i < 387; i+=15)
	{
		_blocks[i]->SetType(Quad::Type::ABLE);
	}	
	for (int i = 125; i < 171; i+=15)
	{
		_blocks[i]->SetType(Quad::Type::ABLE);
	}
	for (int i = 165; i < 210; i+=15)
	{
		_blocks[i]->SetType(Quad::Type::ABLE);
	}
	_blocks[49]->SetType(Quad::Type::ABLE);
	_blocks[64]->SetType(Quad::Type::ABLE);
	_blocks[79]->SetType(Quad::Type::ABLE);
	_blocks[80]->SetType(Quad::Type::ABLE);
	_blocks[81]->SetType(Quad::Type::ABLE);
	_blocks[95]->SetType(Quad::Type::ABLE);
	_blocks[96]->SetType(Quad::Type::ABLE);
	_blocks[109]->SetType(Quad::Type::ABLE);
	_blocks[110]->SetType(Quad::Type::ABLE);
	_blocks[169]->SetType(Quad::Type::ABLE);
	_blocks[208]->SetType(Quad::Type::ABLE);
	_blocks[207]->SetType(Quad::Type::ABLE);

	_blocks[223]->SetType(Quad::Type::ABLE);
	_blocks[224]->SetType(Quad::Type::ABLE);
	_blocks[239]->SetType(Quad::Type::ABLE);
	_blocks[254]->SetType(Quad::Type::ABLE);
	_blocks[255]->SetType(Quad::Type::ABLE);
	_blocks[270]->SetType(Quad::Type::ABLE);
	_blocks[271]->SetType(Quad::Type::ABLE);

	_blocks[286]->SetType(Quad::Type::ABLE);
	_blocks[287]->SetType(Quad::Type::ABLE);
	_blocks[302]->SetType(Quad::Type::ABLE);
	_blocks[301]->SetType(Quad::Type::ABLE);
	_blocks[317]->SetType(Quad::Type::ABLE);
	_blocks[332]->SetType(Quad::Type::ABLE);
	_blocks[331]->SetType(Quad::Type::ABLE);

	_blocks[330]->SetType(Quad::Type::ABLE);
	_blocks[329]->SetType(Quad::Type::ABLE);
	_blocks[314]->SetType(Quad::Type::ABLE);
	_blocks[313]->SetType(Quad::Type::ABLE);
	_blocks[312]->SetType(Quad::Type::ABLE);
	_blocks[327]->SetType(Quad::Type::ABLE);
	_blocks[342]->SetType(Quad::Type::ABLE);
	_blocks[200]->SetType(Quad::Type::ABLE);
	_blocks[201]->SetType(Quad::Type::ABLE);
	_blocks[215]->SetType(Quad::Type::ABLE);
	_blocks[216]->SetType(Quad::Type::ABLE);
}