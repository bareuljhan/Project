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


			if (_curClipIndex >= _clips.size())
			{
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
					_isReverse = false;
				
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