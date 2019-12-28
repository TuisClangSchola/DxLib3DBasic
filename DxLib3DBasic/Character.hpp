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

	enum class DIRECTION { left, down, right, up };

	bool m_direction[4];
	bool m_preDirection[4];


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
���̂S�F��������~���Ă��Ȃ��B�P���ɂ߂�ǂ������Ȃ����B
*/

