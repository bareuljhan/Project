#pragma once
class FloralFury : public Scene
{
public:
	FloralFury();
	virtual ~FloralFury();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:	

	shared_ptr<Stage2_FloralFury> _map;
	shared_ptr<Flower> _boss1;
	shared_ptr<Player> _player;

	shared_ptr<Effect> _effect;
};

