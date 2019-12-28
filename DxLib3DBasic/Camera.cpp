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
	perspesctiveViewArea = VGet(0, 150, 0);
	cameraPerspectiveArea = VGet(0, 530, 700);


	// �v���C���[�̍��W������
	charaArea = VAdd(charaarea, VGet(0.0f, 80.0f, 0.0f));


	// ��{��񏉊���
	speed = DX_PI_F / 90;
	angle = 0.0f;
	zRota = VGet(0, 530, 700);


	// ���ߖ@�J������������
	SetCameraNearFar(100.0f, 9500.0f);	// �J�����̕`��͈͂��w��
	SetCameraPositionAndTarget_UpVecY(VAdd(cameraPerspectiveArea, charaArea), VAdd(perspesctiveViewArea, charaArea));
}



/// ------------------------------------------------------------------------------------
Camera::~Camera()
{
}



/// ------------------------------------------------------------------------------------
void Camera::Process(const VECTOR charaarea)
{
	charaArea = VAdd(charaarea, VGet(0.0f, 80.0f, 0.0f));		// �L�����̈ʒu���X�V


	// ���ɉ�]��
	if (!CheckHitKey(KEY_INPUT_LEFT))
	{
		// ���ߖ@�J�����̉�]����
		RLrotate(speed, cameraPerspectiveArea.x, cameraPerspectiveArea.z);


		// �J�����̕���
		if (angle > DX_TWO_PI_F)
		{
			angle = 0;
		}
		angle += speed;
	}
	// �E�ɉ�]��
	if (!CheckHitKey(KEY_INPUT_RIGHT))
	{
		// ���ߖ@�J�����̉�]����
		RLrotate(-speed, cameraPerspectiveArea.x, cameraPerspectiveArea.z);


		// �J�����̕���
		if (angle < -DX_TWO_PI_F)
		{
			angle = 0;
		}
		angle -= speed;
	}

	SetCameraPositionAndTarget_UpVecY(VAdd(cameraPerspectiveArea, charaArea), VAdd(perspesctiveViewArea, charaArea));
}
