#pragma once
class CupHead : public Scene
{
public:
	CupHead();
	virtual ~CupHead();

	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<Player> _player;
};

