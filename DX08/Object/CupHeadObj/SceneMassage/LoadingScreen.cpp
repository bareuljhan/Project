#include "framework.h"
#include "LoadingScreen.h"

LoadingScreen::LoadingScreen()
{
	_quad = make_shared<Quad>(L"Resource/Texture/CupHead/Loading.png");
	_quad->SetPS(ADD_PS(L"Shader/FadePixelShader.hlsl"));

	_quad->GetTransform()->SetPosition(CENTER);
	_quad->GetTransform()->SetScale(Vector2(3.6f, 3.0f));

	_buffer = make_shared<FadeBuffer>();
	_buffer->_data.fadeValue = 1.0f;
	_delay = 0.0f;

	CreateAction("LoadingAni", Action::Type::LOOP);

	_sprite->GetTransform()->SetPosition(Vector2(1180, 110));
	_action->Play();
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::Update()
{
	if (isReady == false) return;
	_quad->Update();
	_buffer->Update();

	_delay += DELTA_TIME;
	
	if (_delay > 4.0f && _delay < 13.0f)
	{
		_buffer->_data.fadeValue -= DELTA_TIME * 0.1f;
	}
	if(_delay >= 13.0f)
	{
		_buffer->_data.fadeValue = 0.0f;
		_delay = 0.0f;
		isReady = false;
	}

	if (_buffer->_data.fadeValue > 0.4f)
	{
		_sprite->Update();
		_action->Update();
	}
}

void LoadingScreen::Render()
{
	if (isReady == false) return;
	_buffer->SetPSBuffer(0);
	_quad->Render();

	if (_delay > 5.0f && _delay < 15.0f)
	{
		_buffer->_data.fadeValue -= DELTA_TIME * 0.01f;
	}
	if (_buffer->_data.fadeValue > 0.6f)
	{
		_sprite->SetActionClip(_action->GetCurClip());
		_sprite->Render();
	}
}

void LoadingScreen::CreateAction(string name, Action::Type type)
{
	string xmlPath = "Resource/XML/Screen/" + name + ".xml";
	wstring srvPath(name.begin(), name.end());
	srvPath = L"Resource/Texture/CupHead/Screen/" + srvPath + L".png";

	MyXML xml = MyXML(xmlPath, srvPath);

	string actionName = name;
	_action = make_shared<Action>(xml.GetClips(), actionName, type);
	_sprite = make_shared<Sprite>(srvPath, xml.AverageSize());
}
