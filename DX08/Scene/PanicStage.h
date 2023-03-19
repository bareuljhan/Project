#pragma once
class PanicStage : public Scene
{
public:
	PanicStage();
	virtual ~PanicStage();
	
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Stage1_Panic> _bg;
	shared_ptr<Player> _player;
	shared_ptr<Spudder> _boss1;
	shared_ptr<Carrot> _monster;
	shared_ptr<Vaggie_Carrot> _boss2;

};

