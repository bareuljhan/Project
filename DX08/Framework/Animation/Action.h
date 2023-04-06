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

	Action(vector<Clip> clips, string name = "", Type type = LOOP, float speed = 0.05f);
	~Action();

	void Update();

	void Play();
	void Pause();
	void Start();
	void Stop();
	void Reset();

	Clip GetCurClip() { return _clips[_curClipIndex]; }
	Action::Type GetRepeatType() { return _repeatType; }
	string GetName() { return _name; }

	bool IsPlay() { return _isPlay; }
	void NextScreen(function<void(void)> endEvent) { _ready = endEvent; }

	void SetCallBack(function<void(void)> endEvent) { _endEvent = endEvent; }

	void SetTargetClip(int value) { _targetClip = value; }
	void SetCallBack_Target(function<void(void)> endEvent) { _spudderATKEvent = endEvent; }
	void SetIDLE_CallBack(function<void(void)> endEvent) { _setIdle = endEvent; }
	void SetCallBack_Skill(function<void(void)> endEvent) { _skillEvent = endEvent; }
	void CallBack_TS(function<void(void)> endEvent) { _carrotIntro = endEvent; }
	void CarretMove_CallBack(function<void(void)> endEvent) { _carrotMove = endEvent; }
	void VaggieSpawn(function<void(void)> endEvent) { _vaggieSpawn = endEvent; }
	void VaggieIdle(function<void(void)> endEvent) { _vaggieIDLE = endEvent; }
	void VaggieBeam(function<void(void)> endEvent) { _vaggieBEAM = endEvent; }
	void VaggieDestroy(function<void(void)> endEvent) { _destroy = endEvent; }
	void PodEffect(function<void(void)> endEvent) { _podEffect = endEvent; }
	void HandEffect(function<void(void)> endEvent) { _handEffect = endEvent; }
	void FlowerGround(function<void(void)> endEvent) { _flowerGround = endEvent; }
	void HandATK(function<void(void)> endEvent) { _handATK = endEvent; }
	void VineRespawn(function<void(void)> endEvent) { _vineGen = endEvent; }
	void PuffBall(function<void(void)> endEvent) { _puffBall = endEvent; }
	void ReviveCallBack(function<void(void)> endEvent) { _revive = endEvent; }
	void Ready(function<void(void)> endEvent) { _ready = endEvent; }
	void CupIntro(function<void(void)> endEvent) { _cupIntro = endEvent; }
	
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
	function<void(void)> _ready = nullptr;

	function<void(void)> _endEvent = nullptr;
	int _targetClip = 26;
	function<void(void)> _spudderATKEvent = nullptr;
	int _skillTargetClip = 6;

	function<void(void)> _setIdle = nullptr;
	function<void(void)> _skillEvent = nullptr;
	function<void(void)> _carrotIntro = nullptr;
	function<void(void)> _carrotMove = nullptr;
	function<void(void)> _vaggieSpawn = nullptr;
	function<void(void)> _vaggieIDLE = nullptr;
	function<void(void)> _vaggieBEAM = nullptr;
	function<void(void)> _destroy = nullptr;
	function<void(void)> _podEffect = nullptr;
	function<void(void)> _handEffect = nullptr;
	function<void(void)> _flowerGround = nullptr;
	function<void(void)> _handATK = nullptr;
	function<void(void)> _vineGen = nullptr;
	function<void(void)> _puffBall = nullptr;
	function<void(void)> _revive = nullptr;
	function<void(void)> _cupIntro = nullptr;
};