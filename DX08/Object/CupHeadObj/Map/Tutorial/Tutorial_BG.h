#pragma once
class Player;

class Tutorial_BG
{
public:
	Tutorial_BG();
	~Tutorial_BG();

	void Update();
	void Render();

	Vector2 LeftBottom();
	Vector2 RightTop();
private:

	shared_ptr<Quad> _backGround;

};

