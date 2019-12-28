#pragma once
#include "Basic.hpp"



/*
����͓V�����o�Ɋ撣���Ă��炢�܂����B
*/
class Character
{
private:
	int m_model;

	VECTOR m_area;

	float m_walkSpeed;

	bool m_moveFlag;

	float m_animSpeed;

	int m_attachMotion;

	int m_attachNum;

	float m_totalTime;

	float m_nowPlayTime;

	float m_motionBlendTime;

	int m_preAttach;

	float m_preMotionPlayTime;

	enum class MOTION { dash, idle };

	void Player_PlayAnim(int attach);

	void Player_AnimProcess();

	void MoveProcess(const float t_angle);


public:
	Character(const int& t_model);
	~Character();


	void Draw();
	void Process(const float t_angle);

	const VECTOR GetArea() const { return m_area; }
};


/*
������ƃv���O�����ɈӒn�������܂����B���m�Ɍ����Ή���������Ƃ��̂����F�X�����(*''��''*)
������l�����ăA�h�o�C�X�B
���̂P�F�L�[�{�[�h�݂̂̐��䂵�����Ă��Ȃ��B�R���g���[���[�ł��Ȃ�X�e�B�b�N�̌X���𐳊m�ɂ��K�v������B
���̂Q�F�΂ߕ����߂��ᑁ���B*sqrt(2)�Ƃ������΂悭�Ȃ�B
���̂R�F�O���������ĂȂ��BMV1SetRotationXYZ�Ɉ�H�v����邾���ŏo����B
���̂S�F�X�b�ƈړ�����B�������ړ�������������~������K�v������B
*/

