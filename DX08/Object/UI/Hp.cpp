#include "framework.h"
#include "Hp.h"

Hp::Hp(Vector2 size)
{
	_hp1 = make_shared<Quad>(L"Resource/Texture/CupHead/Hp/hp1.png", size);
	
	_hp2 = make_shared<Quad>(L"Resource/Texture/CupHead/Hp/hp2.png", size);

	_hp3 = make_shared<Quad>(L"Resource/Texture/CupHead/Hp/hp3.png", size);
	
	_hp4 = make_shared<Quad>(L"Resource/Texture/CupHead/Hp/hp4.png", size);
	_hp4->SetPS(ADD_PS(L"Shader/UI/HpSliderPixelShader.hlsl"));

	_dead = make_shared<Quad>(L"Resource/Texture/CupHead/Hp/dead.png", size);

	_buffer = make_shared<HpBuffer>();
	_buffer->_data.ratio = 0.5f;
}
Hp::~Hp()
{
}

void Hp::Update()
{
	_hp4->Update();
	_hp3->Update();
	_hp2->Update();
	_hp1->Update();
	_dead->Update();
	_buffer->Update();
}

void Hp::PostRender()
{
	_buffer->SetPSBuffer(1);
	_dead->Render();
	_hp1->Render();
	_hp2->Render();
	_hp3->Render();
	_hp4->Render();
}

void Hp::SetOne()
{
	_hp1->SetPS(ADD_PS(L"Shader/UI/HpSliderPixelShader.hlsl"));
}

void Hp::SetTwo()
{
	_hp2->SetPS(ADD_PS(L"Shader/UI/HpSliderPixelShader.hlsl"));
}

void Hp::SetThree()
{
	_hp3->SetPS(ADD_PS(L"Shader/UI/HpSliderPixelShader.hlsl"));
}

void Hp::SetFour()
{
	_hp4->SetPS(ADD_PS(L"Shader/UI/HpSliderPixelShader.hlsl"));
}

void Hp::Dead(wstring file, Vector2 size)
{
	_dead = make_shared<Quad>(file, size);
}

void Hp::SetPosition(Vector2 pos)
{
	_hp1->GetTransform()->SetPosition(pos);
	_hp2->GetTransform()->SetPosition(pos);
	_hp3->GetTransform()->SetPosition(pos);
	_hp4->GetTransform()->SetPosition(pos);
	_dead->GetTransform()->SetPosition(pos);
}

void Hp::SetScale(Vector2 scale)
{
}