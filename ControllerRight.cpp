////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		ControllerRight.cpp
//		
//		�X�V����	�X�V�����l	�X�V���e
//		----------------------------------
//		2022/12/13	�X�{		ControllerRight.h/cpp�쐬
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

#include "ControllerRight.h"
#include "Gauge.h"
#include "Input.h"
#include "DirectXTex/Texture.h"

bool g_bStop;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	ControllerRight.cpp:�R���X�g���N�^
//
//	�N���X���FCControllerRight
//
//	�ϐ���			�^��						�T�v
//	m_fControllerRightPos	Float3						HP�o�[�̈ʒu
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
CControllerRight::CControllerRight()
{
	m_fControllerRightPos = DirectX::XMFLOAT3(180.0f, 1100.0f, 0.0f);
	m_nHeal = 0;
	m_nFrame = 0;
	m_bInv = false;
	m_bPressKey = false;
	m_nInvTime = 120;
	m_nUsePause = 1;
	m_pPosX = 0;
	g_bStop = false;
	m_bCreateMenu = false;
	LoadTextureFromFile("Assets/Frame_Right.png", &m_pBar);
}

CControllerRight::~CControllerRight()
{
	m_pBar->Release();
}

void CControllerRight::Draw()
{
	DirectX::XMFLOAT4X4 mat[3];;
	DirectX::XMMATRIX T =
		DirectX::XMMatrixTranslation(m_fControllerRightPos.x, m_fControllerRightPos.y, m_fControllerRightPos.z);
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

	if (m_bCreateMenu)
	{
		m_pMenu->Draw();
		m_pPAUSE->Draw();
		m_pGRID->Draw();
		m_pRESUME->Draw();
		m_pOPTION->Draw();
		m_pEXITGAME->Draw();
		m_pCursor->Draw();

	}
}

void CControllerRight::Update()
{
	if (IsKeyPress(VK_ESCAPE))
	{
		m_bPressKey = true;
	}

	switch (m_nUsePause)
	{
	case 1:		// �W�J
		if (m_bPressKey)
		{
			if (m_fControllerRightPos.y < 375.0f)
			{
				if (m_fControllerRightPos.x > 1100.0f)
				{
					m_bPressKey = false;
					m_bCreateMenu = true;
					m_pMenu = new CCreateUI("Assets/MainDisplay.png",
						DirectX::XMFLOAT2(1000, -650.0f),DirectX::XMFLOAT3(155.0f, 350.0f, 0.0f));
					m_pPAUSE = new CCreateUI("Assets/PAUSE.png",
						DirectX::XMFLOAT2(300, -100.0f), DirectX::XMFLOAT3(500.0f, 100.0f, 0.0f));
					m_pGRID = new CCreateUI("Assets/Grid.png",
						DirectX::XMFLOAT2(950, -5.0f), DirectX::XMFLOAT3(180.0f, 150.0f, 0.0f));
					m_pRESUME = new CCreateUI("Assets/Resume.png",
						DirectX::XMFLOAT2(300, -70.0f), DirectX::XMFLOAT3(500.0f, 250.0f, 0.0f));
					m_pOPTION = new CCreateUI("Assets/Option.png",
						DirectX::XMFLOAT2(300, -70.0f), DirectX::XMFLOAT3(500.0f, 400.0f, 0.0f));
					m_pEXITGAME = new CCreateUI("Assets/ExitGame.png",
						DirectX::XMFLOAT2(500, -70.0f), DirectX::XMFLOAT3(400.0f, 550.0f, 0.0f));
					m_pCursor = new CCursor();
					m_nUsePause = 2;
				}
				else
				{
					m_fControllerRightPos.x += 100.0f;
				}
			}
			else
			{
				m_fControllerRightPos.y -= 30.0f;
			}
			Draw();
		}
		g_bStop = false;

		break;

	case 2:		// ���[�ƃ��j���[�\��
		if (m_bCreateMenu)
		{
			m_pMenu->Update();
			m_pCursor->Update();

		}

		if (m_bPressKey)
		{
			if (m_bCreateMenu)
			{
				delete m_pMenu;
				m_bCreateMenu = false;
			}
			if (m_fControllerRightPos.x < 200.0f)
			{
				if (m_fControllerRightPos.y > 1200.0f)
				{
					m_bPressKey = false; 				
					m_nUsePause = 1;
				}
				else
				{
					m_fControllerRightPos.y += 30.0f;
				}
				g_bStop = true;
			}
			else
			{
				m_fControllerRightPos.x -= 100.0f;
			}
			Draw();
		}
		break;
	}
}

DirectX::XMFLOAT3 CControllerRight::GetPos()
{
	return m_fControllerRightPos;
}

bool CControllerRight::GetStop()
{
	return g_bStop;
}

