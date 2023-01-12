////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		Cursor.cpp
//		
//		更新日時	更新した人	更新内容
//		----------------------------------
//		2022/12/13	森本		Cursor.h/cpp作成
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

#include "Cursor.h"
#include "Gauge.h"
#include "Input.h"
#include "DirectXTex/Texture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Cursor.cpp:コンストラクタ
//
//	クラス名：CCursor
//
//	変数名			型名						概要
//	m_fCursorPos	Float3						HPバーの位置
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
CCursor::CCursor()
{
	m_fCursorPos = DirectX::XMFLOAT3(400.0f, 250.0f, 0.0f);
	m_nCursolCount = 0;
	LoadTextureFromFile("Assets/Cursor_Left.png", &m_pBar);
}

CCursor::~CCursor()
{
	m_pBar->Release();
}

void CCursor::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];;
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(m_fCursorPos.x, m_fCursorPos.y, m_fCursorPos.z);
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
	CGauge::SetSize(DirectX::XMFLOAT2(70, -70.0f));
	CGauge::SetTexture(m_pBar);
	CGauge::Draw();
}

void CCursor::Update()
{
	if (IsKeyTrigger(VK_UP))
	{
		m_nCursolCount--;
		if (m_nCursolCount < 0)
			m_nCursolCount = 2;
	}

	if (IsKeyTrigger(VK_DOWN))
	{
		m_nCursolCount++;
		if (m_nCursolCount > 2)
			m_nCursolCount = 0;
	}

	switch(m_nCursolCount)
	{
	case 0:
		m_fCursorPos = DirectX::XMFLOAT3(400.0f, 250.0f, 0.0f);
		Draw();
		break;

	case 1:
		m_fCursorPos = DirectX::XMFLOAT3(400.0f, 400.0f, 0.0f);
		Draw();
		break;

	case 2:
		m_fCursorPos = DirectX::XMFLOAT3(300.0f, 550.0f, 0.0f);
		Draw();
		break;
	}
}