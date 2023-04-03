#pragma once
class Route
{
public:
	struct Node
	{
		int x;
		int y;
		bool obticle;

		float g;
		float h;
		float f;
		Node* parent;
	};

	Route();
	~Route();

	void Update();
	void Render();

	Node* CreateNode(int x, int y)
	{
		Node* node = new Node;
		node->x = x;
		node->y = y;

		return node;
	}

	void CreateRoute();

	vector<vector<Node*>> CreateMapData()
	{
		_mapData = vector<vector<Node*>>(15, vector<Node*>(30));
		_blocks = vector<vector<shared_ptr<Quad>>>(15, vector<shared_ptr<Quad>>(30));

		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				// 노드 생성
				Node* node = CreateNode(i, j);
				node->x = i;
				node->y = j;
				
				shared_ptr<Quad> block = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/AbleQuad.png");
				block->GetTransform()->SetPosition(Vector2(200, 150));
				Vector2 blockPos = block->GetTransform()->GetPos();
				Vector2 distance = Vector2(31 * i, 31 * j);
				block->GetTransform()->GetScale() *= 0.21f;

				if (i > 0) // 위쪽 노드
				{
					block->GetTransform()->SetPosition(Vector2(blockPos.x, blockPos.y + distance.y));
					_nodes.push_back(_mapData[i - 1][j]);
				}
				if (j > 0) // 왼쪽 노드
				{
					block->GetTransform()->SetPosition(Vector2(blockPos.x - distance.x, blockPos.y));
					_nodes.push_back(_mapData[i][j - 1]);

				}
				if (i < 15 - 1) // 아래쪽 노드
				{
					block->GetTransform()->SetPosition(Vector2(blockPos.x, blockPos.y - distance.y));
					_nodes.push_back(_mapData[i + 1][j]);

				}
				if (j < 30 - 1) // 오른쪽 노드
				{
					block->GetTransform()->SetPosition(Vector2(blockPos.x + distance.x, blockPos.y));
					_nodes.push_back(_mapData[i][j + 1]);

				}

				_mapData[i][j] = node;
				_blocks[i][j] = block;
			}
		}
		return _mapData;
	}

private:
	vector<vector<Node*>> _mapData;
	vector<Node*> _nodes;
	vector<vector<shared_ptr<Quad>>> _blocks;
};