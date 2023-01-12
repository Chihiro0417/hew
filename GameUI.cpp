////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GameUI.cpp
//		
//		�X�V����	�X�V�����l	�X�V���e
//		----------------------------------
//		2022/12/16�@�X�{		���g�̕ύX
//		
//		
//		
//		���e
//		�EUI�֌W���ꊇ�ŌĂт�����悤�ɂ���t�@�C���ł�
//		�@UI�֘A�̃N���X��ǉ������ۂ�GameUI.h�ŕϐ��錾���Ă�����ŌĂт����Ă�������
//
//		���ӓ_
//		�EGame3D.cpp���ł̊֐��̌Ăяo�������肢���܂�
//		�EDraw�̏��Ԃɒ��ӁI�I
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "GameUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	GameUI.cpp:�R���X�g���N�^
//
//	�N���X���FGameUI
//
//	�ϐ���						�^��						�T�v
//	m_pPlayerHp					CPlayerHp*					�v���C���[HP�̌Ăяo��
//	m_pPlayerHpSilhouette		CPlayerHpSilhouette*		�v���C���[HP�̌Ăяo��
//	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameUI::GameUI()
{
	m_pPlayerHp = new CPlayerHp;
	m_pPlayerSp = new CPlayerSp;
	m_pPlayerHpSilhouette = new CCreateUI("Assets/HpBarSilhouette.png", DirectX::XMFLOAT2(200.0f, -30.0f),DirectX::XMFLOAT3(55.0f, 630.0f, 0.0f));
	m_pBarFrame = new CCreateUI("Assets/BarFrame.png", DirectX::XMFLOAT2(210.0f, -80.0f),DirectX::XMFLOAT3(50.0f, 650.0f, 0.0f));
	m_pControllerLeft = new CControllerLeft();
	m_pControllerRight = new CControllerRight();
	
}

GameUI::~GameUI()
{
	
}

void GameUI::Draw()
{
	m_pBarFrame->Draw();
	m_pPlayerHpSilhouette->Draw();
	m_pPlayerHp->Draw();
	m_pPlayerSp->Draw();


	m_pControllerLeft->Draw();
	m_pControllerRight->Draw();

}

void GameUI::Update()
{
	m_pPlayerHp->Update();
	m_pPlayerSp->Update();
	m_pControllerLeft->Update();
	m_pControllerRight->Update();
}

//////////////////////////////////////////////////////////////////////////////////////
//
//	GameUI.cpp�FDamage�֐�
//
//	class�FGameUI
//
//	
//	�g�p�ꏊ
//	�EGame3D.cpp�̓G�ƃv���C���[�̓����蔻���
//	
//	
//////////////////////////////////////////////////////////////////////////////////////
void GameUI::Damage()
{
	m_pPlayerHp->PlayerDamage();
}
