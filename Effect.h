#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>

class Effect
{
public:
	Effect();
	~Effect();
	void Update();
	void Draw();
	void AtkEffect();
private:
	Effekseer::ManagerRef m_efkManager;
	EffekseerRendererDX11::RendererRef m_efkRenderer;
	Effekseer::Handle m_efkHandle;


	Effekseer::EffectRef m_effect1;
	//Effekseer::EffectRef m_effect2;
};

#endif // !__EFFECT_H__


