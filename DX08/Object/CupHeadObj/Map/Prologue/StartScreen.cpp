#include "framework.h"
#include "StartScreen.h"

StartScreen::StartScreen()
{
	CreateAction(Action::Type::PINGPONG);

	_sprite->GetTransform()->SetPosition(Vector2(CENTER_X, CENTER_Y - 70));
	_sprite->GetTransform()->GetScale() *= 3.2f;
	_action->Play();

	_quad = make_shared<Quad>(L"Resource/Texture/CupHead/Prologue/Screen_backGround.png");
	_quad->GetTransform()->SetPosition(CENTER);
}

StartScreen::~StartScreen()
{
}

void StartScreen::Update()
{
	_quad->Update();

	_action->Update();
	_sprite->Update();
}

void StartScreen::Render()
{
	_quad->Render();

	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();

}

void StartScreen::PostRender()
{

	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->RenderText(L"PRESS ENTER KEY", rect);
}

void StartScreen::CreateAction(Action::Type type)
{
	string xmlPath = "Resource/XML/Prologue/Screen.xml";
	wstring srvPath = L"Resource/Texture/CupHead/Prologue/Screen.png";

	MyXML xml = MyXML(xmlPath, srvPath);

	_action = make_shared<Action>(xml.GetClips(), "StartScreen", type);
	Vector2 averageSize = xml.AverageSize() * 0.3f;
	_sprite = make_shared<Sprite>(srvPath, averageSize);
}
