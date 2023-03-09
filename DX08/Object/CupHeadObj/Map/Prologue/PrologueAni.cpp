#include "framework.h"
#include "PrologueAni.h"

PrologueAni::PrologueAni()
{
	CreateAction();

	_sprite->GetTransform()->SetPosition(CENTER);
	_sprite->GetTransform()->GetScale() *= 3.0f;
	_action->Play();
}

PrologueAni::~PrologueAni()
{
}

void PrologueAni::Update()
{
	_action->Update();
	_sprite->Update();
}

void PrologueAni::Render()
{
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void PrologueAni::CreateAction()
{
	string xmlPath = "Resource/XML/Prologue/Intro.xml";
	wstring srvPath = L"Resource/Texture/CupHead/Prologue/Intro.png";

	MyXML xml = MyXML(xmlPath, srvPath);

	_action = make_shared<Action>(xml.GetClips(), "Prologue");
	Vector2 averageSize = xml.AverageSize() * 0.3f;
	_sprite = make_shared<Sprite>(srvPath, averageSize);
}
