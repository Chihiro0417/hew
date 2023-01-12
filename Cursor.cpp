////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		Cursor.cpp
//		
//		�X�V����	�X�V�����l	�X�V���e
//		----------------------------------
//		2022/12/13	�X�{		Cursor.h/cpp�쐬
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

#include "Cursor.h"
#include "Gauge.h"
#include "Input.h"
#include "DirectXTex/Texture.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Cursor.cpp:�R���X�g���N�^
//
//	�N���X���FCCursor
//
//	�ϐ���			�^��						�T�v
//	m_fCursorPos	Float3						HP�o�[�̈ʒu
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