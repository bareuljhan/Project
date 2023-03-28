// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <malloc.h>
#include <memory.h>
#include <memory>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <algorithm>
#include <string>
#include <functional>
#include <wrl/client.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// DirectXTex
#include "../DirectXTex/DirectXTex.h"

// FMOD
#include "Library/FMOD/inc/fmod.hpp"
#pragma comment(lib, "Library/FMOD/fmod_vc.lib")


// ImGui
#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui_impl_dx11.h"
#include "../ImGUI/imgui_impl_win32.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

using namespace std;
using namespace DirectX;

#include "Types.h"

// Framework
#include "Framework/Device/Device.h"

// Math
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"

// Render
#include "Framework/Render/ConstantBuffer.h"
#include "Framework/Render/GlobalBuffer.h"
#include "Framework/Render/VertexLayout.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/ShaderManager.h"
#include "Framework/Render/RenderTarget.h"

// Collider
#include "Framework/Collider/Collider.h"
#include "Framework/Collider/RectCollider.h"
#include "Framework/Collider/CircleCollider.h"

// Utillity
#include "Framework/Utillity/InputManager.h"
#include "Framework/Utillity/Timer.h"
#include "Framework/Utillity/tinyxml2.h"
#include "Framework/Utillity/Audio.h"
#include "Framework/Utillity/MathUtility.h"

// Camera
#include "Framework/Camera/Camera.h"

// Texture
#include "Framework/Texture/SRV.h"
#include "Framework/Texture/SRVManager.h"
#include "Framework/Texture/SamplerState.h"
#include "Framework/Texture/BlendState.h"
#include "Framework/Texture/StateManager.h"

// Action
#include "Framework/Animation/Action.h"
#include "Framework/Animation/MyXML.h"

// Object
#include "Object/BagicObj/Quad.h"
#include "Object/BagicObj/Sprite.h"
#include "Object/BagicObj/Effect.h"
#include "Object/BagicObj/EffectManager.h"

// Prologue
#include "Object/CupHeadObj/Map/Prologue/StartScreen.h"

// UI
#include "Object/UI/Button.h"
#include "Object/UI/Hp.h"

// GameObj
#include "Object/CupHeadObj/Bullet.h"
#include "Object/CupHeadObj/Player.h"

// ClearMessage
#include "Object/CupHeadObj/Message/ClearMessage.h"

// Map
#include "Object/CupHeadObj/Map/Prologue/PrologueAni.h"
#include "Object/CupHeadObj/Map/Epilogue/EpilogueAni.h"
#include "Object/CupHeadObj/Map/OverWorld/OverWorld_BG.h"
#include "Object/CupHeadObj/Map/OverWorld/OverWorld_Player.h"
#include "Object/CupHeadObj/Map/StageMap/Stage1_Panic.h"
#include "Object/CupHeadObj/Map/StageMap/Stage2_FloralFury.h"
#include "Object/CupHeadObj/Map/Tutorial/Tutorial_BG.h"
#include "Object/CupHeadObj/Map/Tutorial/Tutorial_Iner_BG.h"

// Monster
#include "Object/CupHeadObj/Monster/Stage1/Spudder_Bullet.h"
#include "Object/CupHeadObj/Monster/Stage1/Vaggie_Bullet.h"
#include "Object/CupHeadObj/Monster/Stage1/Vaggie_Beam.h"

// Stage1
#include "Object/CupHeadObj/Monster/Stage1/Spudder.h"
#include "Object/CupHeadObj/Monster/Stage1/Carrot.h"
#include "Object/CupHeadObj/Monster/Stage1/Vaggie_Carrot.h"

// Stage2
#include "Object/CupHeadObj/Monster/Stage2/Chomper.h"
#include "Object/CupHeadObj/Monster/Stage2/PodBullet.h"
#include "Object/CupHeadObj/Monster/Stage2/HandATK.h"
#include "Object/CupHeadObj/Monster/Stage2/Flower.h"

// Scene
#include "Scene/Scene.h"

// Program
#include "Program/Program.h"