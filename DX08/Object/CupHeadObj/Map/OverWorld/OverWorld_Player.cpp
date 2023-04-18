#include "framework.h"
#include "OverWorld_Player.h"

OverWorld_Player::OverWorld_Player()
{
	_transform = make_shared<Transform>();

	CreateAction("OverWorld_IDLE", Action::Type::LOOP);
	CreateAction("OverWorld_DOWN", Action::Type::LOOP);
	CreateAction("OverWorld_UP", Action::Type::LOOP);
	CreateAction("OverWorld_SIDE", Action::Type::LOOP);
	//CreateAction("OverWorld_CLEAR", Action::Type::END);

	for (auto sprite : _sprites)
		sprite->GetTransform()->SetParent(_transform);

	_oldState = State::IDLE;
	_actions[State::IDLE]->Play();

	_collider = make_shared<RectCollider>(Vector2(50,50));
	_collider->GetTransform()->SetParent(_transform);

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
	_collider->Update();

	if (KEY_DOWN(VK_LBUTTON))
	{
		AStar(_transform->GetPos(), MOUSE_POS);
	}
	
	MoveTO();

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

	_collider->Render();
}

void OverWorld_Player::Init()
{
}

void OverWorld_Player::MoveTO()
{
	if (isRun == false) return;
	if (isIn == true) return;
	if (_posIndex == _path.size())
	{
		SetAction(State::IDLE);
		isRun = false;
		_posIndex = 1;
		return;
	}
	Vector2 dir = (_path[_posIndex] - _path[_posIndex - 1]).NormalVector2();
	Vector2 temp = _transform->GetPos();
	temp += dir * _speed * DELTA_TIME;
	_transform->SetPosition(temp);
	_transform->Update();
	if (dir.x < 0 && dir.y < 0)
	{
		SetAction(State::RUN_DOWN);
		if (_transform->GetPos().x - _pathPos[_posIndex].x <= 3 && _transform->GetPos().y - _pathPos[_posIndex].y <= 3)
		{
			_posIndex++;
		}
	}
	else if (dir.x < 0 && dir.y >= 0)
	{
		if (dir.y == 0)
		{
			SetLeft();
			SetAction(State::RUN);
		}
		if (dir.y != 0)
			SetAction(State::RUN_UP);
		if (_transform->GetPos().x - _pathPos[_posIndex].x <= 3 && _transform->GetPos().y - _pathPos[_posIndex].y >= -3)
		{
			_posIndex++;
		}
	}
	else if (dir.x >= 0 && dir.y < 0)
	{
		SetAction(State::RUN_DOWN);
		if (_transform->GetPos().x - _pathPos[_posIndex].x >= -3 && _transform->GetPos().y - _pathPos[_posIndex].y <= 3)
		{
			_posIndex++;
		}
	}
	else
	{
		if (dir.x == 1 && dir.y == 0)
		{
			SetRight();
			SetAction(State::RUN);
		}
		if (dir.y != 0)
			SetAction(State::RUN_UP);
		if (_transform->GetPos().x - _pathPos[_posIndex].x >= -3	 && _transform->GetPos().y - _pathPos[_posIndex].y >= -3)
		{
			_posIndex++;
		}
	}
}

void OverWorld_Player::AStar(Vector2 start, Vector2 end)
{
	_path.clear();
	_pathPos.clear();

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
	vector<vector<float>> best = vector<vector<float>>(40, vector<float>(22, 100000.0f));
	_discorvered = vector<vector<bool>>(40, vector<bool>(22, false));
	_parent = vector<vector<Vector2>>(40, vector<Vector2>(22, Vector2(0,0)));

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
			(abs(here.pos.y) - abs(end.y) > -15 && abs(here.pos.y) - abs(end.y) < 15) )
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
				there = here.pos + frontPos[i] * 28;
			else
				there = here.pos + frontPos[i] * 30;

			shared_ptr<Quad> block = _route->GetMapData()[thereIndex.x][thereIndex.y]->blocks;
			Vector2 leftTop = Vector2(block->GetVertex()[0].pos.x, block->GetVertex()[0].pos.y);
			Vector2 rightTop = Vector2(block->GetVertex()[1].pos.x, block->GetVertex()[1].pos.y);
			Vector2 leftBottom = Vector2(block->GetVertex()[2].pos.x, block->GetVertex()[2].pos.y);
			Vector2 rightBottom = Vector2(block->GetVertex()[3].pos.x, block->GetVertex()[3].pos.y);
			
			if (_route->GetMapData()[thereIndex.x][thereIndex.y]->obticle == true)
				return;
							
			if ((here.pos.y - there.y >= 0 && here.pos.y - there.y <= 16) && i == 0)
				continue;	
			if ((here.pos.x - there.x >= 0 && here.pos.x - there.x <= 16) && i == 1)
				continue;
			if ((here.pos.y - there.y <= 0 && here.pos.y - there.y >= -16) && i == 2)
				continue;
			if ((here.pos.x - there.x <= 0 && here.pos.x - there.x >= -16) && i == 3)
				continue;


			if (here.pos.Length() - rightTop.Length() <= 0 && here.pos.Length() - rightTop.Length() >= -12 && i == 4)
				continue;

			if ((here.pos.x - leftTop.x <= 0 && here.pos.x - leftTop.x >= -15) &&
				(here.pos.y - leftTop.y >= 0 && here.pos.y - leftTop.y <= 15) && i == 5)
				continue;
			
			if ((here.pos.x - rightBottom.x >= 0 && here.pos.x - rightBottom.x <= 15) &&
				(here.pos.y - rightBottom.y <= 0 && here.pos.y - rightBottom.y >= -15) && i == 6)
				continue;
			
			if (here.pos.Length() - leftBottom.Length() >= 0 && here.pos.Length() - leftBottom.Length() <= 12 && i == 7)
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

	for (int i = 0; i < _path.size(); i++)
	{
		_pathPos.push_back(_route->GetMapData()[_path[i].x][_path[i].y]->blocks->GetTransform()->GetPos());
	}

	isRun = true;
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
