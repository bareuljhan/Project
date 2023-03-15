#pragma once
class PanicStage : public Scene
{
public:
	PanicStage();
	~PanicStage();
	
	void Update();
	void Render();

private:
	shared_ptr<Stage1_Panic> _bg;
	shared_ptr<Player> _player;
	shared_ptr<Spudder> _boss1;
	shared_ptr<Carrot> _monster;
	shared_ptr<Vaggie_Carrot> _boss2;

};

