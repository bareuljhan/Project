#pragma once
class OverWorld : public Scene
{
public:
	OverWorld();
	~OverWorld();

	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<OverWorld_BG> _map;
	shared_ptr<OverWorld_Player> _player;

};

