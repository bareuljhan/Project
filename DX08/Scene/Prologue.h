#pragma once
class Prologue : public Scene
{
public:
	Prologue();
	virtual ~Prologue();

	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<PrologueAni> _intro;
};

