#include "framework.h"
#include "OverWorld_Player.h"

OverWorld_Player::OverWorld_Player()
{
	_transform = make_shared<Transform>();

	CreateAction("OverWorld_IDLE", Action::Type::LOOP);
	//CreateAction("OverWorld_RUN", Action::Type::LOOP);
	//CreateAction("OverWorld_UP", Action::Type::LOOP);
	//CreateAction("OverWorld_DOWN", Action::Type::LOOP);
	//CreateAction("OverWorld_WD", Action::Type::LOOP);
	//CreateAction("OverWorld_SD", Action::Type::LOOP);
	//CreateAction("OverWorld_CLEAR", Action::Type::END);

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_oldState = State::IDLE;
	_actions[State::IDLE]->Play();

	_route = make_shared<Route>();
}

OverWorld_Player::~OverWorld_Player()
{
}

void OverWorld_Player::SetRight()
{
	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 0;
	}
}

void OverWorld_Player::SetLeft()
{
	for (auto sprite : _sprites)
	{
		sprite->GetLeftRight() = 1;
	}
}

void OverWorld_Player::Update()
{

	if (KEY_DOWN(VK_LBUTTON))
	{
		AStar(_transform->GetPos(), MOUSE_POS);
	}

	for (auto sprite : _sprites)
		sprite->Update();

	for (auto action : _actions)
		action->Update();

	_transform->UpdateSRT();
}

void OverWorld_Player::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
}

void OverWorld_Player::Init()
{
}

void OverWorld_Player::AStar(Vector2 start, Vector2 end)
{
	Vector2 frontPos[8] =
	{
		Vector2 {0, 1},
		Vector2 {1, 0},
		Vector2 {0, -1},
		Vector2 {-1, 0},

		Vector2 {1, 1},
		Vector2 {-1, 1},
		Vector2 {1, -1},
		Vector2 {-1, -1}
	};

	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	vector<vector<float>> best = vector<vector<float>>(30, vector<float>(15, 100000.0f));
	_discorvered = vector<vector<bool>>(30, vector<bool>(15, false));
	_parent = vector<vector<Vector2>>(30, vector<Vector2>(15, Vector2(0,0)));

	Vertex startV;
	startV.pos = start;
	startV.g = 0;
	startV.h = start.Manhattan(Vector2((int)end.x, (int)end.y));
	startV.f = startV.g + startV.h;
	startV.index = _targetIndex;
	pq.push(startV);

	best[startV.index.x][startV.index.y] = startV.f;
	_discorvered[startV.index.x][startV.index.y] = true;
	_parent[startV.index.x][startV.index.y] = start;

	while (true)
	{
		if (pq.empty() == true)
			break;

		Vertex here = pq.top();
		float f = here.f;
		pq.pop();

		if ((abs(here.pos.x) - abs(end.x) > -15 && abs(here.pos.x) - abs(end.x) < 15) &&
			(abs(here.pos.y) - abs(end.y) > -15 && abs(here.pos.y) - abs(end.y) < 15))
		{
			_targetIndex = here.index;
			break;
		}

		if (best[here.index.x][here.index.y] < f)
			continue;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = { 0, 0 };
			Vector2 thereIndex = here.index + frontPos[i];

			if(i >= 4)
				there = here.pos + frontPos[i] * 25;
			else
				there = here.pos + frontPos[i] * 30;
			
			if (here.pos == there && i < 4)
				continue;

			if ((here.pos.x - there.x > 0 && here.pos.x - there.x < 10) &&
				(here.pos.y - there.y > 0 && here.pos.y - there.y < 10) && i >= 4)
				continue;

			float distance = (there - here.pos).Length();
			float nextG = distance + here.g;
			float nextH = there.Manhattan(end);
			float nextF = nextG + nextH;

			if (best[thereIndex.x][thereIndex.y] < nextF)
				continue;

			Vertex thereV;
			thereV.pos = there;
			thereV.g = nextG;
			thereV.h = nextH;
			thereV.f = nextF;
			thereV.index = thereIndex;
			best[thereV.index.x][thereV.index.y] = nextF;
			pq.push(thereV);
			_discorvered[thereV.index.x][thereV.index.y] = true;
			_parent[thereV.index.x][thereV.index.y] = here.index;
		}
	}

	Vector2 endIndex = _targetIndex;
	Vector2 temp = _targetIndex;
	_path.push_back(endIndex);
	
	while (true)
	{
		if (temp == startV.index)
			break;
		
		_path.push_back(_parent[temp.x][temp.y]);

		temp = _parent[temp.x][temp.y];
	}
	std::reverse(_path.begin(), _path.end());
}

void OverWorld_Player::SetAction(State state)
{
	_curState = state;

	if (_curState == _oldState)
		return;

	_actions[_curState]->Play();
	_actions[_oldState]->Reset();
	_oldState = _curState;
}

void OverWorld_Player::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/OverWorld/Character/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/OverWorld/Character/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = "CUP_" + name;
	_actions.emplace_back(make_shared<Action>(xml.GetClips(), actionName, type));
	_sprites.emplace_back(make_shared<Sprite>(srvPath, xml.AverageSize()));
}
