#include "Camera.hpp"



/// ------------------------------------------------------------------------------------
void Camera::RLrotate(const float speed, float& axisOne, float& axisTwo)
{
	const float tempX = axisOne;
	const float tempY = axisTwo;
	axisOne = tempX * cosf(speed) + tempY * sinf(speed);
	axisTwo = -tempX * sinf(speed) + tempY * cosf(speed);
}



/// ------------------------------------------------------------------------------------
Camera::Camera(const VECTOR charaarea)
{
	// ���ߖ@�J�����̏�����
	m_perspesctiveViewArea = VGet(0, 150, 0);
	m_cameraPerspectiveArea = VGet(0, 530, 700);


	// �v���C���[�̍��W������
	m_charaArea = VAdd(charaarea, VGet(0.0f, 80.0f, 0.0f));


	// ��{��񏉊���
	m_speed = DX_PI_F / 90;
	m_angle = 0.0f;
	m_mouseAreaX = BasicParam::winWidth / 2;
	m_mouseAreaY = BasicParam::winHeight / 2;


	// ���ߖ@�J������������
	SetCameraNearFar(100.0f, 9500.0f);	// �J�����̕`��͈͂��w��
	SetCameraPositionAndTarget_UpVecY(VAdd(m_cameraPerspectiveArea, m_charaArea), VAdd(m_perspesctiveViewArea, m_charaArea));
}



/// ------------------------------------------------------------------------------------
Camera::~Camera()
{
}



/// ------------------------------------------------------------------------------------
void Camera::Process(const VECTOR charaarea)
{
	m_charaArea = VAdd(charaarea, VGet(0.0f, 40.0f, 0.0f));		// �L�����̈ʒu���X�V

	GetMousePoint(&m_mouseAreaX, &m_mouseAreaY);

	// ���ɉ�]��
	if (m_mouseAreaX < BasicParam::winWidth / 2 - 10)
	{
		// ���ߖ@�J�����̉�]����
		RLrotate(m_speed, m_cameraPerspectiveArea.x, m_cameraPerspectiveArea.z);


		// �J�����̕���
		if (m_angle > DX_TWO_PI_F)
		{
			m_angle = 0;
		}
		m_angle += m_speed;
		SetMousePoint(BasicParam::winWidth / 2, BasicParam::winHeight / 2);
	}
	// �E�ɉ�]��
	if (m_mouseAreaX > BasicParam::winWidth / 2 + 10)
	{
		// ���ߖ@�J�����̉�]����
		RLrotate(-m_speed, m_cameraPerspectiveArea.x, m_cameraPerspectiveArea.z);


		// �J�����̕���
		if (m_angle < -DX_TWO_PI_F)
		{
			m_angle = 0;
		}
		m_angle -= m_speed;
		SetMousePoint(BasicParam::winWidth / 2, BasicParam::winHeight / 2);
	}

	SetCameraPositionAndTarget_UpVecY(VAdd(m_cameraPerspectiveArea, m_charaArea), VAdd(m_perspesctiveViewArea, m_charaArea));
}
