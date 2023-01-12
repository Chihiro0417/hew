////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		ControllerLeft.cpp
//		
//		更新日時	更新した人	更新内容
//		----------------------------------
//		2022/12/13	森本		ControllerLeft.h/cpp作成
//		2022/12/14　森本		コメントの追加
//		
//		
//		
//		内容
//		・プレイヤーのHPバー関連のプログラムです
//
//
//		注意点
//		・このcppの関数はGameUI.cppで基本的に呼びだしてください
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ControllerLeft.h"
#include "Gauge.h"
#include "Input.h"
#include "DirectXTex/Texture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ControllerLeft.cpp:コンストラクタ
//
//	クラス名：CControllerLeft
//
//	変数名			型名						概要
//	m_fControllerLeftPos	Float3						HPバーの位置
//	m_fHp			float						HPバーの長さ
//	m_fDamage		float						ダメージ量（これによってHPバーの減り方が変わる）
//	m_nHeal			int							回復するまでのフレームのカウント
//	m_nFrame		float						フレームのカウント
//	m_bInv			bool						無敵時間の処理用
//	m_bInvTime		int							無敵時間
//	m_pBar			ID3D11ShaderResourceView	HPバーのテクスチャ
//	※HPバーに貼るテクスチャは上下左右がきっちり揃っている画像でないとダメージを受けた際にズレていってしまう
//	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CControllerLeft::CControllerLeft()
{
	m_fControllerLeftPos = DirectX::XMFLOAT3(55.0f, 1100.0f, 0.0f);
	m_nHeal = 0;
	m_nFrame = 0;
	m_bInv = false;
	m_bPressKey = false;
	m_nInvTime = 120;
	m_nUsePause = 1;
	LoadTextureFromFile("Assets/Frame_Left.png", &m_pBar);
}

CControllerLeft::~CControllerLeft()
{
	m_pBar->Release();
}

void CControllerLeft::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];;
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(m_fControllerLeftPos.x, m_fControllerLeftPos.y, m_fControllerLeftPos.z);
	DirectX::XMStoreFloat4x4(&mat[0],
		DirectX::XMMatrixTranspose(T));
	DirectX::XMStoreFloat4x4(&mat[1],
		DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&mat[2],
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(
				0.0f,		// 画面左端の座標
				1280.0f,	// 画面右端の座標
				720.0f,		// 画面下端の座標
				0.0f,		// 画面上端の座標
				-1.0f,		// Ｚ座標で写せる範囲の手前
				1.0f		// Ｚ座標で写せる範囲の奥
			)));

	CGauge::SetWorld(mat[0]);
	CGauge::SetView(mat[1]);
	CGauge::SetProjection(mat[2]);
	CGauge::SetSize(DirectX::XMFLOAT2(70, -650.0f));
	CGauge::SetTexture(m_pBar);
	CGauge::Draw();
}

void CControllerLeft::Update()
{
	m_fGetPosX = m_pControllerRight.GetPos().x;
	if (IsKeyPress(VK_ESCAPE))
	{
		m_bPressKey = true;
	}

	switch (m_nUsePause)
	{
	case 1:
		if (m_bPressKey)
		{
			m_fControllerLeftPos.y -= 30.0f;
			Draw();
			if (m_fControllerLeftPos.y < 375.0f)
			{
				m_bPressKey = false;
				m_nUsePause = 2;
			}
		}
		break;

	case 2:		// ポーズ解除
		if (m_bPressKey)
		{
			if (m_pControllerRight.GetStop())
			{
				m_fControllerLeftPos.y += 30.0f;
				Draw();
				if (m_fControllerLeftPos.y > 1200.0f)
				{
					m_bPressKey = false;
					m_nUsePause = 1;
				}
			}
		}
		break;
	}
	
}