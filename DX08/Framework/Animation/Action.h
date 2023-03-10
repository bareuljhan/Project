#pragma once
class Action
{
public:
	struct Clip
	{
		Vector2 _startPos;
		Vector2 _size;
		shared_ptr<SRV> _srv;

		Clip(float x, float y, float w, float h, shared_ptr<SRV> srv)
		:_startPos(x,y)
		,_size(w,h)
		,_srv(srv)
		{
		}
	};
	enum Type
	{
		END,
		LOOP,
		PINGPONG
	};

	Action(vector<Clip> clips, string name = "", Type type = LOOP, float speed = 0.1f);
	~Action();

	void Update();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	Clip GetCurClip() { return _clips[_curClipIndex]; }
	Action::Type GetRepeatType() { return _repeatType; }
	string GetName() { return _name; }

	bool IsPlay() { return _isPlay; }

	void SetCallBack(function<void(void)> endEvent) { _endEvent = endEvent; }

	void SetTargetClip(int value) { _targetClip = value; }
	void SetCallBack_Target(function<void(void)> endEvent) { _spudderATKEvent = endEvent; }
	void SetCallBack_Skill(function<void(void)> endEvent) { _skillEvent = endEvent; }
	void CallBack_SpudderDead(function<void(void)> endEvent) { _deathEvent = endEvent; }
	
	bool isEnd = false;
	UINT _curClipIndex = 0;
private:
	string _name;
	vector<Clip> _clips;

	Type _repeatType;

	bool _isPlay = false;


	float _time = 0.0f;
	float _speed = 2.0f;
	
	bool _isReverse = false;

	// 콜백함수 : 정의를 미리 해 둔 상태에서 나중에 필요에 따라 호출 할 수 있는 함수
	// 리스너 패턴, 옵저버 패턴
	function<void(void)> _endEvent = nullptr;

	int _targetClip = 26;
	function<void(void)> _spudderATKEvent = nullptr;

	int _skillTargetClip = 6;
	function<void(void)> _skillEvent = nullptr;
	
	int _spudderDeathTargetClip = 7;
	function<void(void)> _deathEvent = nullptr;
};