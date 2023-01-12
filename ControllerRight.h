////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		PlayerHp.h
//
//		�C���N���[�h���
//		�EGameUI.h
//		
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef __CONTROLLER_RIGHT__
#define __CONTROLLER_RIGHT__

#include <DirectXMath.h>
#include "DirectX.h"
#include "CreateUI.h"
#include "Cursor.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		CPlayerHp�N���X
//		
//		���ɌĂяo�����ꏊ�������Ă����Ă�������
//		
//		�N���X�Ăяo�����
//		�EGameUI.h/cpp
//		
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CControllerRight
{
public:
	CControllerRight();
	~CControllerRight();

	void Draw();
	void Update();

	DirectX::XMFLOAT3 GetPos();

	bool GetStop();

private:
	ID3D11ShaderResourceView* m_pBar;
	CCreateUI* m_pMenu;
	CCreateUI* m_pPAUSE;
	CCreateUI* m_pGRID;
	CCreateUI* m_pRESUME;
	CCreateUI* m_pOPTION;
	CCreateUI* m_pEXITGAME;
	CCursor* m_pCursor;


	DirectX::XMFLOAT3 m_fControllerRightPos;

	int m_nHeal;
	int m_nFrame;
	bool m_bInv;
	int m_nInvTime;

	int m_nUsePause;
	bool m_bPressKey;
	float m_pPosX;
	bool m_bCreateMenu;
};


#endif // __CONTROLLER_RIGHT__
