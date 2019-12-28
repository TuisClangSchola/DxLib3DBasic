#pragma once
#include "Basic.hpp"



/*
�ʏ�̃J�����̃N���X
*/
class Camera
{
private:
	// �J�����̈ʒu
	VECTOR cameraPerspectiveArea;		// ���ߖ@�J����

	// �����������
	VECTOR perspesctiveViewArea;		// ���ߖ@�J����

	// �L�����ʒu
	VECTOR charaArea;

	// �L�����N�^�[�̃A���O��
	float angle;

	// ��]�X�s�[�h
	float speed;

	// ��]���s���֐�
	void RLrotate(const float speed, float& axisOne, float& axisTwo);

	// �}�E�X�̈ʒu
	int m_mouseAreaX, m_mouseAreaY;


public:
	// �L�����̈ʒu�������Ɏ�����R���X�g���N�^
	Camera(const VECTOR charaarea);

	// �f�X�g���N�^
	~Camera();


	// �L�����̈ʒu�������Ɏ�����v���Z�X
	void Process(const VECTOR charaarea);

	// �L�����N�^�[�̃A���O��
	const float GetAngle() const { return angle; }

	// �J�����̍��W
	const VECTOR GetArea() const { return cameraPerspectiveArea; }
};