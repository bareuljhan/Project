#include "framework.h"
#include "EpilogueAni.h"

EpilogueAni::EpilogueAni()
{
	CreateAction();

	_sprite->GetTransform()->SetPosition(CENTER);
	_sprite->GetTransform()->GetScale() *= 3.0f;
	_action->Play();
}

EpilogueAni::~EpilogueAni()
{
}

void EpilogueAni::Update()
{
	_action->Update();
	_sprite->Update();
}

void EpilogueAni::Render()
{
	_sprite->SetActionClip(_action->GetCurClip());
	_sprite->Render();
}

void EpilogueAni::CreateAction()
{
	string xmlPath = "Resource/XML/Prologue/Epilogue.xml";
	wstring srvPath = L"Resource/Texture/CupHead/Prologue/Epilogue.png";

	MyXML xml = MyXML(xmlPath, srvPath);

	_action = make_shared<Action>(xml.GetClips(), "Epilogue");
	Vector2 averageSize = xml.AverageSize() * 0.3f;
	_sprite = make_shared<Sprite>(srvPath, averageSize);
}
