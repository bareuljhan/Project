#pragma once
class ClearMessage
{
public:
	ClearMessage();
	~ClearMessage();

	void Update();
	void Render();
private:
	shared_ptr<Quad> _quad;

};

