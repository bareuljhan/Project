#include "framework.h"
#include "Route.h"

Route::Route()
{
	CreateRoute();
}

Route::~Route()
{
}

void Route::Update()
{
	for (auto block : _blocks)
	{
		block->Update();
	}
}

void Route::Render()
{
	for (auto block : _blocks)
	{
		block->Render();
	}
}

void Route::CreateRoute()
{
	for (int x = 0; x < 30; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			shared_ptr<Quad> block = make_shared<Quad>(L"Resource/Texture/CupHead/OverWorld/Map/AbleQuad.png");
			block->SetType(Quad::Type::DISABLE);
			block->GetTransform()->SetPosition(Vector2(230, 150));
			Vector2 distance = Vector2(32.9f * x, 32.9f * y);
			block->GetTransform()->GetScale() *= 0.21f;
			block->GetTransform()->SetPosition(block->GetTransform()->GetPos() + distance);
			_blocks.push_back(block);
		}
	}
}
