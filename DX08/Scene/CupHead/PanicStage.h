#pragma once
class PanicStage : public Scene
{
public:
	PanicStage();
	virtual ~PanicStage();
	virtual void Init() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<WinScreen> _win;
	shared_ptr<ReadyScreen> _ready;

	shared_ptr<Stage1_Panic> _bg;
	shared_ptr<Player> _player;
	shared_ptr<Spudder> _boss1;
	shared_ptr<Carrot> _monster;
	shared_ptr<Vaggie_Carrot> _boss2;

};

