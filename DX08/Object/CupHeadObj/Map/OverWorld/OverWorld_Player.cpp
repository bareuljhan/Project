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


	_quad = make_shared<Quad>();
	_oldState = State::IDLE;
	_actions[State::IDLE]->Play();
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
	_transform->Update();

	if (KEY_DOWN(VK_LBUTTON))
	{
		AStar(GetTransform()->GetPos(), MOUSE_POS);
	}

	for (auto sprite : _sprites)
		sprite->Update();

	for (auto action : _actions)
		action->Update();
}

void OverWorld_Player::Render()
{
	_sprites[_curState]->SetActionClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Render();
}

bool OverWorld_Player::CanGo(Vector2 pos)
{
	if (_quad->GetType() == Quad::Type::DISABLE)
		return false;
	return true;
}

void OverWorld_Player::Init()
{
}

void OverWorld_Player::AStar(Vector2 start, Vector2 end)
{
	Vector2 frontPos[8]
	{
		Vector2 {0.0f, -32.9f}, // DOWN 2
		Vector2 {0.0f, 32.9f}, // UP 0
		Vector2 {-32.9f, 0.0f}, // LEFT 1
		Vector2 {32.9f, 0.0f}, // RIGHT 3

		Vector2 {32.9f, -32.9f}, // RIGHT_DOWN
		Vector2 {-32.9f, -32.9f}, // LEFT_DOWN
		Vector2 {32.9f, 32.9f}, // RIGHT UP
		Vector2 {-32.9f, 32.9f} // LEFT UP
	};
	
	priority_queue<Vertex, vector<Vertex>, greater<Vertex>> pq;
	vector<vector<float>> best = vector<vector<float>>(38, vector<float>(20, 100000.0f));
	_discorvered = vector<vector<bool>>(38, vector<bool>(20, false));
	_parent = vector<vector<Vector2>>(38, vector<Vector2>(20, Vector2(-1, -1)));

	Vertex startV;
	startV.pos = start;
	startV.g = 0;
	startV.h = start.Manhattan(end);
	startV.f = startV.g + startV.h;
	pq.push(startV);
	best[2][10] = startV.f;
	_discorvered[2][10] = true;
	_parent[2][10] = start;

	while (true)
	{
		if (pq.empty() == true)
			break;

		Vertex here = pq.top();
		float f = here.f;
		pq.pop();

		if (here.pos == end)
			break;

		if (best[here.pos.x][here.pos.y] < f)
			continue;

		for (int i = 0; i < 8; i++)
		{
			Vector2 there = here.pos + frontPos[i];
			if (CanGo(there) == false)
				continue;
			if (here.pos == there)
				continue;

			float distance = (there - here.pos).Length();
			float nextG = distance + here.g;
			float nextH = there.Manhattan(end);
			float nextF = nextG + nextH;

			if (best[there.x][there.y] < nextF)
				continue;

			Vertex thereV;
			thereV.pos = there;
			thereV.g = nextG;
			thereV.h = nextH;
			thereV.f = nextF;
			best[there.x][there.y] = nextF;
			pq.push(thereV);
			_discorvered[there.x][there.y] = true;
			_parent[there.x][there.y] = here.pos;
		}
	}

	Vector2 pos = end;
	while (true)
	{
		pos = _parent[pos.x][pos.y];
		if (pos == start)
			break;
	}
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
