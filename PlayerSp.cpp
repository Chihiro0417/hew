////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		PlayerSp.cpp
//		
//		�X�V����	�X�V�����l	�X�V���e
//		----------------------------------
//		2022/12/19	�X�{		PlayerSp.h/cpp�쐬
//		
//		
//		���e
//		�E�v���C���[��SP�o�[�֘A�̃v���O�����ł�
//
//
//		���ӓ_
//		�E����cpp�̊֐���GameUI.cpp�Ŋ�{�I�ɌĂт����Ă�������
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PlayerSp.h"
#include "Input.h"
#include "Gauge.h"
#include "DirectXTex/Texture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	PlayerSp.cpp:�R���X�g���N�^
//
//	�N���X���FCPlayerSp
//
//	�ϐ���			�^��						�T�v
//	m_fPlayerSpPos	Float3						HP�o�[�̈ʒu
//	m_fSp			float						HP�o�[�̒���
//	m_fUseSp		float						�K�E�Z�ɕK�v��SP�̗�
//	m_nHeal			int							�񕜂���܂ł̃t���[���̃J�E���g
//	m_nFrame		float						�t���[���̃J�E���g
//	m_bInv			bool						���G���Ԃ̏����p
//	m_bInvTime		int							���G����
//	m_pBar			ID3D11ShaderResourceView	HP�o�[�̃e�N�X�`��
//	��HP�o�[�ɓ\��e�N�X�`���͏㉺���E���������葵���Ă���摜�łȂ��ƃ_���[�W���󂯂��ۂɃY���Ă����Ă��܂�
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
	CGauge::SetSize(DirectX::XMFLOAT2(m_fSp, -30.0f));
	CGauge::SetTexture(m_pBar);
	CGauge::Draw();
}

void CPlayerSp::Update()
{
	// �񕜊֘A�i�s���S�j
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


	// ���G���Ԋ֘A
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

