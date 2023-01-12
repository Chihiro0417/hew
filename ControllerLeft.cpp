////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		ControllerLeft.cpp
//		
//		�X�V����	�X�V�����l	�X�V���e
//		----------------------------------
//		2022/12/13	�X�{		ControllerLeft.h/cpp�쐬
//		2022/12/14�@�X�{		�R�����g�̒ǉ�
//		
//		
//		
//		���e
//		�E�v���C���[��HP�o�[�֘A�̃v���O�����ł�
//
//
//		���ӓ_
//		�E����cpp�̊֐���GameUI.cpp�Ŋ�{�I�ɌĂт����Ă�������
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ControllerLeft.h"
#include "Gauge.h"
#include "Input.h"
#include "DirectXTex/Texture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ControllerLeft.cpp:�R���X�g���N�^
//
//	�N���X���FCControllerLeft
//
//	�ϐ���			�^��						�T�v
//	m_fControllerLeftPos	Float3						HP�o�[�̈ʒu
//	m_fHp			float						HP�o�[�̒���
//	m_fDamage		float						�_���[�W�ʁi����ɂ����HP�o�[�̌�������ς��j
//	m_nHeal			int							�񕜂���܂ł̃t���[���̃J�E���g
//	m_nFrame		float						�t���[���̃J�E���g
//	m_bInv			bool						���G���Ԃ̏����p
//	m_bInvTime		int							���G����
//	m_pBar			ID3D11ShaderResourceView	HP�o�[�̃e�N�X�`��
//	��HP�o�[�ɓ\��e�N�X�`���͏㉺���E���������葵���Ă���摜�łȂ��ƃ_���[�W���󂯂��ۂɃY���Ă����Ă��܂�
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

	case 2:		// �|�[�Y����
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