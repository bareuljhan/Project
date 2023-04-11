#pragma once
class Tutorial : public Scene
{
public:
	Tutorial();
	virtual ~Tutorial();

	void PreRender();
	virtual void Init() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender()override;

private:
	shared_ptr<Tutorial_BG> _bg;
	shared_ptr<Tutorial_Iner_BG> _iner;
	shared_ptr<Player> _player;

	shared_ptr<Button> _button;


	shared_ptr<RenderTarget> _renderTarget;
	shared_ptr<Quad> _rtvQuad;
};

