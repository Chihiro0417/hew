////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GameUI.h
//
//		下に呼び出した場所を書いていってください
//
//		インクルード情報
//		・Game3D.h
//		
//
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __GAME_UI__
#define __GAME_UI__

#include <DirectXMath.h>
#include "DirectX.h"
#include "PlayerHp.h"
#include "PlayerSp.h"
#include "ControllerLeft.h"
#include "ControllerRight.h"
#include "CreateUI.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GameUIクラス
//		
//		下に呼び出した場所を書いていってください
//		
//		クラス呼び出し情報
//		・Game3D.h/cpp
//		
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GameUI 
{
public:
	GameUI();
	~GameUI();

	void Draw();
	void Update();

	void Damage();

private:
	CPlayerHp* m_pPlayerHp;
	CPlayerSp* m_pPlayerSp;
	CCreateUI* m_pPlayerHpSilhouette;
	CCreateUI* m_pBarFrame;
	CControllerLeft* m_pControllerLeft;
	CControllerRight* m_pControllerRight;
};






#endif // __GAME_UI__