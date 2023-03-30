#include "framework.h"
#include "Action.h"

Action::Action(vector<Clip> clips, string name, Type type, float speed)
:_clips(clips)
,_name(name)
,_repeatType(type)
,_speed(speed)
{
}

Action::~Action()
{
}

void Action::Update()
{
	if (_isPlay == false)
		return;

	_time += DELTA_TIME;

	if (_time > _speed)
	{
		_time = 0.0f;
		switch (_repeatType)
		{
		case Action::END:
		{
			_curClipIndex++;

			if (_curClipIndex == 4 && _carrotMove != nullptr)
			{
				_carrotMove();
			}	
			if (_curClipIndex == 6 && _skillEvent != nullptr)
			{
				_skillEvent();
			}		
			if (_curClipIndex == 6 && _setIdle != nullptr)
			{
				_setIdle();
			}	
			if (_curClipIndex == 26 && _carrotIntro != nullptr)
			{
				_carrotIntro();
			}	
			if (_curClipIndex == 17 && _vaggieSpawn != nullptr)
			{
				_vaggieSpawn();
			}
			if (_curClipIndex == 25 && _vaggieIDLE != nullptr)
			{
				_vaggieIDLE();
			}		
			if (_curClipIndex == 22 && _vaggieBEAM != nullptr)
			{
				_vaggieBEAM();
			}		
			if (_curClipIndex == 13 && _destroy != nullptr)
			{
				_destroy();
			}	
			if (_curClipIndex == 50 && _ready != nullptr)
			{
				_ready();
			}	
			if (_curClipIndex == 6 && _podEffect != nullptr)
			{
				_podEffect();
			}
			if (_curClipIndex == 16 && _handEffect != nullptr)
			{
				_handEffect();
			}
			if (_curClipIndex == 18 && _flowerGround != nullptr)
			{
				_flowerGround();
			}
			if (_curClipIndex == 17 && _handATK != nullptr)
			{
				_handATK();
			}	
			if (_curClipIndex == 7 && _vineGen != nullptr)
			{
				_vineGen();
			}	
			if (_curClipIndex == 11 && _puffBall != nullptr)
			{
				_puffBall();
			}		
			if (_curClipIndex == 28 && _revive != nullptr)
			{
				_revive();
			}	
			if (_curClipIndex == 44 && _cupIntro != nullptr)
			{
				_cupIntro();
			}


			if (_curClipIndex >= _clips.size())
			{
				isEnd = true;
				Stop();
			}
		}
			break;

		case Action::LOOP:
		{
			_curClipIndex++;
			_curClipIndex %= _clips.size();
			if (_curClipIndex == 26 && _spudderATKEvent != nullptr)
			{
				_spudderATKEvent();
			}

		}
			break;

		case Action::PINGPONG:
		{
			if (_isReverse)
			{
				_curClipIndex--;
				
				if (_curClipIndex == 1 && _vaggieIDLE != nullptr)
					_vaggieIDLE();

				if (_curClipIndex <= 0)
				{
					_isReverse = false;
					isEnd = true;
				}
				
			}
			else
			{
				_curClipIndex++;
				if (_curClipIndex >= _clips.size() - 1)
					_isReverse = true;
			}
		}
			break;
		default:
			break;
		}
	}
}

void Action::Play()
{
	_isPlay = true;
	_isReverse = false;
	_time = 0.0f;
	_curClipIndex = 0;
}

void Action::Pause()
{
	_isPlay = false;
}

void Action::Start()
{
	_isPlay = true;
}

void Action::Stop()
{
	_isPlay = false;
	_curClipIndex = 0;

	if (_endEvent != nullptr)
		_endEvent();
}

void Action::Reset()
{
	_isPlay = false;
	_curClipIndex = 0;
	_time = 0.0f;
}