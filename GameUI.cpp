////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		GameUI.cpp
//		
//		更新日時	更新した人	更新内容
//		----------------------------------
//		2022/12/16　森本		中身の変更
//		
//		
//		
//		内容
//		・UI関係を一括で呼びだせるようにするファイルです
//		　UI関連のクラスを追加した際はGameUI.hで変数宣言してこちらで呼びだしてください
//
//		注意点
//		・Game3D.cpp内での関数の呼び出しをお願いします
//		・Drawの順番に注意！！
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "GameUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	GameUI.cpp:コンストラクタ
//
//	クラス名：GameUI
//
//	変数名						型名						概要
//	m_pPlayerHp					CPlayerHp*					プレイヤーHPの呼び出し
//	m_pPlayerHpSilhouette		CPlayerHpSilhouette*		プレイヤーHPの呼び出し
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
//	GameUI.cpp：Damage関数
//
//	class：GameUI
//
//	
//	使用場所
//	・Game3D.cppの敵とプレイヤーの当たり判定内
//	
//	
//////////////////////////////////////////////////////////////////////////////////////
void GameUI::Damage()
{
	m_pPlayerHp->PlayerDamage();
}
