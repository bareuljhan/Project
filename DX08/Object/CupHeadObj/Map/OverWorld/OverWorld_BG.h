#pragma once
class OverWorld_BG
{
public:
	OverWorld_BG();
	~OverWorld_BG();

	void Update();
	void Render();

	void CreateHome(string name);
	void CreatePanic(string name);
	void CreateShip(string name);
	void CreateShop(string name);
	void CreateMausoleum(string name);
	void CreateOoze(string name);
	void CreateZeppelin(string name);
	void CreateDieHouse(string name);
	void CreateNPCApple(string name);
	void CreateNPCAxe(string name);


	shared_ptr<Collider> OozeCol() { return _oozeCol; }
	shared_ptr<Collider> PanicCol() { return _panicCol; }
	shared_ptr<Collider> ShopCol() { return _shopCol; }
private:

	shared_ptr<Sprite> _home;
	shared_ptr<Action> _homeAction;
	shared_ptr<Sprite> _panic;
	shared_ptr<Action> _panicAction;
	shared_ptr<Sprite> _ship;
	shared_ptr<Action> _shipAction;
	shared_ptr<Sprite> _shop;
	shared_ptr<Action> _shopAction;	
	shared_ptr<Sprite> _mausoleum;
	shared_ptr<Action> _mausoleumAction;
	shared_ptr<Sprite> _ooze;
	shared_ptr<Action> _oozeWaveAction;	
	shared_ptr<Sprite> _zeppelin;
	shared_ptr<Action> _zeppelinAction;
	shared_ptr<Sprite> _dieHouse;
	shared_ptr<Action> _dieHouseAction;
	shared_ptr<Sprite> _appleSp;
	shared_ptr<Action> _appleAc;
	shared_ptr<Sprite> _axeSp;
	shared_ptr<Action> _axeAc;

	shared_ptr<Quad> _seaLeft;
	shared_ptr<Quad> _seaRight;
	shared_ptr<Quad> _leftMain;
	shared_ptr<Quad> _rightMain;
	shared_ptr<Quad> _leftSide;
	shared_ptr<Quad> _sideBoat;
	shared_ptr<Quad> _sideDock;
	shared_ptr<Quad> _islandTree;
	shared_ptr<Quad> _lightHouse;
	shared_ptr<Quad> _buoy;
	shared_ptr<Quad> _mainBridge;
	shared_ptr<Quad> _frogsBridge;
	shared_ptr<Quad> _slimeStairs;
	shared_ptr<Quad> _slimeStairs2;
	shared_ptr<Quad> _rightStairs;
	shared_ptr<Quad> _veggieStairs;
	shared_ptr<Quad> _bridge;
	shared_ptr<Quad> _bridge2;

	shared_ptr<Collider> _NpcCol1;
	shared_ptr<Collider> _NpcCol2;
	shared_ptr<Collider> _oozeCol;
	shared_ptr<Collider> _panicCol;
	shared_ptr<Collider> _shopCol;

};

