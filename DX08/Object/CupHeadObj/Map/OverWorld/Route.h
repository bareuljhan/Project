#pragma once
class Route
{
public:
	struct Node
	{
		int x;
		int y;
		bool obticle;

		shared_ptr<Quad> blocks;
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
		
		node->obticle = false;
		node->blocks = make_shared<Quad>();

		return node;
	}

	vector<vector<Node*>> CreateMapData()
	{
		_mapData = vector<vector<Node*>>(30, vector<Node*>(15));

		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				// 노드 생성
				Node* node = CreateNode(i, j);
				node->x = i;
				node->y = j;
				
				shared_ptr<Quad> block = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/AbleQuad.png");
				block->GetTransform()->SetPosition(Vector2(200, 150));
				Vector2 blockPos = Vector2(block->GetTransform()->GetPos().x + 30 * i, block->GetTransform()->GetPos().y + 30 * j);
				block->GetTransform()->GetScale() *= 0.21f;

				if (i > 0) // 위쪽 노드
				{
					block->GetTransform()->SetPosition(Vector2(blockPos));
					_nodes.push_back(_mapData[i - 1][j]);
				}
				if (j > 0) // 왼쪽 노드
				{
					block->GetTransform()->SetPosition(Vector2(blockPos));
					_nodes.push_back(_mapData[i][j - 1]);

				}
				if (i < 30 - 1) // 아래쪽 노드
				{
					block->GetTransform()->SetPosition(Vector2(blockPos));
					_nodes.push_back(_mapData[i + 1][j]);

				}
				if (j < 15 - 1) // 오른쪽 노드
				{
					block->GetTransform()->SetPosition(Vector2(blockPos));
					_nodes.push_back(_mapData[i][j + 1]);

				}

				node->blocks = block;
				_mapData[i][j] = node;
			}
		}
		return _mapData;
	}

	vector<Node*> GetNodes(){ return _nodes; }
	vector<vector<Node*>> GetMapData() { return _mapData; }

private:
	vector<vector<Node*>> _mapData;
	vector<Node*> _nodes;
};