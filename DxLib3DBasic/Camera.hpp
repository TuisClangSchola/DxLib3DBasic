#pragma once
#include "Basic.hpp"



/*
�ʏ�̃J�����̃N���X
*/
class Camera
{
private:
	// �J�����̈ʒu
	VECTOR m_cameraPerspectiveArea;		// ���ߖ@�J����

	// �����������
	VECTOR m_perspesctiveViewArea;		// ���ߖ@�J����

	// �L�����ʒu
	VECTOR m_charaArea;

	// �L�����N�^�[�̃A���O��
	float m_angle;

	// ��]�X�s�[�h
	float m_speed;

	// ��]���s���֐�
	void RLrotate(const float t_speed, float& t_axisOne, float& t_axisTwo);

	// �}�E�X�̈ʒu
	int m_mouseAreaX, m_mouseAreaY;


public:
	// �L�����̈ʒu�������Ɏ�����R���X�g���N�^
	Camera(const VECTOR t_charaarea);

	// �f�X�g���N�^
	~Camera();


	// �L�����̈ʒu�������Ɏ�����v���Z�X
	void Process(const VECTOR t_charaarea);

	// �L�����N�^�[�̃A���O��
	const float GetAngle() const { return m_angle; }

	// �J�����̍��W
	const VECTOR GetArea() const { return m_cameraPerspectiveArea; }
};


/*
������ƃv���O�����ɈӒn�������܂���(*''��''*)�B���R�F���񂾂�߂�ǂ������Ȃ��Ă���
������l�����ăA�h�o�C�X�B
���̂P�F3D������z�u����̂ł���΃J�����Ɠ��������Ń��X�i�[�p�̂��̂�����B����Ȃ�Set3DSoundListenerPosAndFrontPos_UpVecY
*/