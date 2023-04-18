#pragma once
class LoadingScreen
{
public:
	LoadingScreen();
	~LoadingScreen();

	void Update();
	void Render();
private:
	shared_ptr<Quad> _quad;
	shared_ptr<FadeBuffer> _buffer;
};

