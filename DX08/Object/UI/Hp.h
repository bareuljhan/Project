#pragma once
class Hp
{
public:
	Hp(Vector2 size);
	~Hp();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos);
	void SetScale(Vector2 scale);

	void SetOne(wstring file, Vector2 size);
	void SetTwo(wstring file, Vector2 size);
	void SetThree(wstring file, Vector2 size);
	void SetFour(wstring file, Vector2 size);
	void Dead(wstring file, Vector2 size);

	void SetRatio(float value) { _buffer->_data.ratio = value; }
private:
	shared_ptr<Quad> _hp1;
	shared_ptr<Quad> _hp2;
	shared_ptr<Quad> _hp3;
	shared_ptr<Quad> _hp4;
	shared_ptr<Quad> _dead;

	shared_ptr<HpBuffer> _buffer;
};

