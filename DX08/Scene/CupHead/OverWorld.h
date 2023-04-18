#pragma once
class OverWorld : public Scene
{
public:
	OverWorld();
	virtual ~OverWorld();
	virtual void Init() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Render() override;

	void NextScene();
private:
	shared_ptr<OverWorld_BG> _map;
	shared_ptr<OverWorld_Player> _player;
	shared_ptr<Route> _route;

	shared_ptr<Button> _button;

	bool _isOoze = false;
	bool _isShop = false;
	bool _isPanic = false;
};

