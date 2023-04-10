#pragma once
class Prologue : public Scene
{
public:
	Prologue();
	virtual ~Prologue();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void SetScreen();

	bool isNext = false;
private:
	shared_ptr<PrologueAni> _intro;
	shared_ptr<StartScreen> _startScreen;
};

