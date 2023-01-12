#include "Main.h"
#include "Effect.h"
#include "DirectX.h"
#include "Input.h"

EffectManager::EffectManager()
:efkPos(0.0f,0.0f,0.0f)
{
	//--- effekseer関連初期化
	m_efkManager = Effekseer::Manager::Create(8000);

	auto graphicsDevice = EffekseerRendererDX11::CreateGraphicsDevice(
		GetDevice(), GetContext());
	m_efkRenderer = EffekseerRendererDX11::Renderer::Create(graphicsDevice, 8000);

	m_efkManager->SetSpriteRenderer(m_efkRenderer->CreateSpriteRenderer());
	m_efkManager->SetRibbonRenderer(m_efkRenderer->CreateRibbonRenderer());
	m_efkManager->SetRingRenderer(m_efkRenderer->CreateRingRenderer());
	m_efkManager->SetTrackRenderer(m_efkRenderer->CreateTrackRenderer());
	m_efkManager->SetModelRenderer(m_efkRenderer->CreateModelRenderer());

	m_efkManager->SetTextureLoader(m_efkRenderer->CreateTextureLoader());
	m_efkManager->SetModelLoader(m_efkRenderer->CreateModelLoader());
	m_efkManager->SetMaterialLoader(m_efkRenderer->CreateMaterialLoader());
	m_efkManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());


	//--- effect読み込み
	m_effect1 = Effekseer::Effect::Create(m_efkManager, u"Assets/effect/atk.efkefc");
	//m_effect2 = Effekseer::Effect::Create(m_efkManager, u"Assets/Effect/Laser01.efkefc");
}

EffectManager::~EffectManager()
{
	//m_effect2.Reset();
	m_effect1.Reset();
	m_efkRenderer.Reset();
	m_efkManager.Reset();
}

void EffectManager::Update()
{
	// マネージャーの更新
	Effekseer::Manager::UpdateParameter updateParameter;
	m_efkManager->Update(updateParameter);

	// 時間を更新する
	static float time = 0.0f;
	m_efkRenderer->SetTime(time);

	if (IsKeyTrigger(VK_RETURN))
	{
		m_efkHandle = m_efkManager->Play(m_effect1, 0, 0, 0);//0.0.0が座標
		m_efkManager->SetScale(m_efkHandle, 1.0f, 1.0f, 1.0f);	//サイズ変換
	}
	//if (IsKeyTrigger(VK_UP))
	//{
	//	m_efkHandle = m_efkManager->Play(m_effect2, 0, 0, 0);
	time++;

	//}
}

void EffectManager::Draw()
{
	auto viewerPosition = Effekseer::Vector3D(10.0f, 5.0f, 20.0f);
	::Effekseer::Matrix44 projectionMatrix;
	projectionMatrix.PerspectiveFovRH(
		90.0f / 180.0f * 3.14f, (float)GetAppWidth() / GetAppHeight(),
		1.0f, 500.0f);

	::Effekseer::Matrix44 cameraMatrix;

	cameraMatrix.LookAtRH(viewerPosition,
		Effekseer::Vector3D(0.0f, 0.0f, 0.0f),
		Effekseer::Vector3D(0.0f, 1.0f, 0.0f));

	//// DXで使うならAtLHにする、多分こんな感じ？↓
	// DirectX::XMMatrixLookAtLH(
	//	DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0),
	//	DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0),
	//	DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0)

	// レイヤーパラメータの設定
	Effekseer::Manager::LayerParameter layerParameter;
	layerParameter.ViewerPosition = viewerPosition;
	m_efkManager->SetLayerParameter(0, layerParameter);



	// 投影行列を設定
	m_efkRenderer->SetProjectionMatrix(projectionMatrix);
	// カメラ行列を設定
	m_efkRenderer->SetCameraMatrix(cameraMatrix);

	// エフェクトの描画開始処理を行う。
	m_efkRenderer->BeginRendering();

	// エフェクトの描画を行う。
	Effekseer::Manager::DrawParameter drawParameter;
	drawParameter.ZNear = 0.0f;
	drawParameter.ZFar = 1.0f;
	drawParameter.ViewProjectionMatrix =
		m_efkRenderer->GetCameraProjectionMatrix();
	m_efkManager->Draw(drawParameter);

	// エフェクトの描画終了処理を行う。
	m_efkRenderer->EndRendering();


}
void EffectManager::AtkEffect(float x, float y, float z)
{
	efkPos.x = x;
	efkPos.y = y;
	efkPos.z = z;
	m_efkHandle = m_efkManager->Play(m_effect1,efkPos.x, efkPos.y, efkPos.z);//0.0.0が座標
	m_efkManager->SetScale(m_efkHandle, 5.0f, 5.0f, 5.0f);	//サイズ変換
	EffectManager::Draw();
}
