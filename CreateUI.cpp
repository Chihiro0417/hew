#include "CreateUI.h"
#include "Gauge.h"
#include "DirectXTex/Texture.h"

CCreateUI::CCreateUI(const char* Filename, DirectX::XMFLOAT2 Size, DirectX::XMFLOAT3 Pos)
{
	if (strcmp(Filename, "") != 0)
		LoadTextureFromFile(Filename, &m_pBar);
	m_Filename = Filename;

	m_fSize = Size;
	m_fPos = Pos;
}

CCreateUI::~CCreateUI()
{
	if (strcmp(m_Filename, "") != 0)
		m_pBar->Release();
}

void CCreateUI::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(m_fPos.x, m_fPos.y, m_fPos.z);
	DirectX::XMStoreFloat4x4(&mat[0],
		DirectX::XMMatrixTranspose(T));
	DirectX::XMStoreFloat4x4(&mat[1],
		DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&mat[2],
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(
				0.0f,		// ��ʍ��[�̍��W
				1280.0f,	// ��ʉE�[�̍��W
				720.0f,		// ��ʉ��[�̍��W
				0.0f,		// ��ʏ�[�̍��W
				-1.0f,		// �y���W�Ŏʂ���͈͂̎�O
				1.0f		// �y���W�Ŏʂ���͈͂̉�
			)));

	CGauge::SetWorld(mat[0]);
	CGauge::SetView(mat[1]);
	CGauge::SetProjection(mat[2]);
	CGauge::SetSize(DirectX::XMFLOAT2(m_fSize.x, m_fSize.y));
	CGauge::SetTexture(m_pBar);
	CGauge::Draw();
}

void CCreateUI::Update()
{
}
