#pragma once
#include <Effekseer.h>
#include <EffekseerRendererDX11.h> 
#include "Game3D.h"

class EffectManager
{
public:
	EffectManager();
	~EffectManager();
	void Update();
	void Draw();
	void AtkEffect(float x, float y, float z);
private:
	Effekseer::ManagerRef m_efkManager;
	EffekseerRendererDX11::RendererRef m_efkRenderer;
	Effekseer::Handle m_efkHandle;


	Effekseer::EffectRef m_effect1;
	//Effekseer::EffectRef m_effect2;
	DirectX::XMFLOAT3 efkPos;
};



