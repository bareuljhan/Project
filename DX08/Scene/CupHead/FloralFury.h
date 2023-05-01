#pragma once
class FloralFury : public Scene
{
public:
	FloralFury();
	virtual ~FloralFury();
	virtual void Init() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void NextScene();
private:	
	shared_ptr<WinScreen> _win;
	shared_ptr<ReadyScreen> _ready;

	shared_ptr<Stage2_FloralFury> _map;
	shared_ptr<Flower> _boss1;
	shared_ptr<Player> _player;

	shared_ptr<Effect> _effect;

	shared_ptr<Button> _button;
};

