////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		PlayerSp.cpp
//		
//		更新日時	更新した人	更新内容
//		----------------------------------
//		2022/12/19	森本		PlayerSp.h/cpp作成
//		
//		
//		内容
//		・プレイヤーのSPバー関連のプログラムです
//
//
//		注意点
//		・このcppの関数はGameUI.cppで基本的に呼びだしてください
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PlayerSp.h"
#include "Input.h"
#include "Gauge.h"
#include "DirectXTex/Texture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	PlayerSp.cpp:コンストラクタ
//
//	クラス名：CPlayerSp
//
//	変数名			型名						概要
//	m_fPlayerSpPos	Float3						HPバーの位置
//	m_fSp			float						HPバーの長さ
//	m_fUseSp		float						必殺技に必要なSPの量
//	m_nHeal			int							回復するまでのフレームのカウント
//	m_nFrame		float						フレームのカウント
//	m_bInv			bool						無敵時間の処理用
//	m_bInvTime		int							無敵時間
//	m_pBar			ID3D11ShaderResourceView	HPバーのテクスチャ
//	※HPバーに貼るテクスチャは上下左右がきっちり揃っている画像でないとダメージを受けた際にズレていってしまう
//	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPlayerSp::CPlayerSp()
{
	m_fPlayerSpPos = DirectX::XMFLOAT3(55.0f, 670.0f, 0.0f);
	m_fSp = 10.0f;
	m_fUseSp = 50.0;
	m_nHeal = 0;
	m_nFrame = 0;
	m_bInv = false;
	m_nInvTime = 120;
	LoadTextureFromFile("Assets/SpBar.png", &m_pBar);
}

CPlayerSp::~CPlayerSp()
{
	m_pBar->Release();
}

void CPlayerSp::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];;
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(m_fPlayerSpPos.x, m_fPlayerSpPos.y, m_fPlayerSpPos.z);
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
	CGauge::SetSize(DirectX::XMFLOAT2(m_fSp, -30.0f));
	CGauge::SetTexture(m_pBar);
	CGauge::Draw();
}

void CPlayerSp::Update()
{
	// 回復関連（不完全）
	m_nHeal++;
	if (m_fSp < 200)
	{
		if (m_nHeal > 300)
		{
			m_fSp += 10;
			CGauge::Draw();
			m_nHeal = 0;
		}
	}
	else
	{
		m_nHeal = 0;
	}


	// 無敵時間関連
	if (m_bInv == true)
		m_nFrame++;

	if (m_nFrame > 120)
	{
		m_bInv = false;
		m_nFrame = 0;
	}

	if (!m_bInv == true)
	{
		if (IsKeyPress(VK_RETURN))
		{
			if (m_fSp >= m_fUseSp)
			{
				m_fSp -= m_fUseSp;
				m_nHeal = 0;
				m_bInv = true;
			}
		}
	}
}

