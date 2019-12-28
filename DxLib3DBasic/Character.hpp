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

	VECTOR preArea;

	float m_modelHeight;

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
	Character(const int& t_model, const int& t_panelModel);
	~Character();


	void Draw();
	void Process(const float t_angle);

	bool HitCircleReturn(VECTOR t_hitUnderArea, float t_width);

	const VECTOR GetArea() const { return m_area; }

	const float GetHeight() const { return MV1GetFramePosition(m_model, 7).y; }
};


/*
������ƃv���O�����ɈӒn�������܂���(*''��''*)�B���R�F���񂾂�߂�ǂ������Ȃ��Ă���
������l�����ăA�h�o�C�X�B
���̂P�F�L�[�{�[�h�݂̂̐��䂵�����Ă��Ȃ��B�R���g���[���[�ł��Ȃ�X�e�B�b�N�̌X���𐳊m�ɂ��K�v������B���Ȃ݂ɂ��̏ꍇ�f�b�h���b�N�ɂ��Ă��l�����Ȃ��Ɛ������ƂɂȂ�B
���̂Q�F�΂ߕ����߂��ᑁ���B*sqrt(2)�Ƃ������΂悭�Ȃ�B
���̂R�F�O���������ĂȂ��BMV1SetRotationXYZ�Ɉ�H�v����邾���ŏo����B
���̂S�F�X�b�ƈړ�����B�������ړ�������������~������K�v������B
���̂T�F0,0,0�̂Ƃ���Ƀ��X�|�[�������Ă�B���ۂ�3D���Ȃ�n�ʂ�肿�傢��Ƀ��X�|�[��������悤�ɂ��Ȃ��Ɗm���ŋ���ɒ��ށB
���̂T�F�X�e�[�W�Ƃ�OBB�ȊO�̂����蔻��̏����͂����ĂȂ��B�Q�l�Ƃ��Ă��ꂪ�ǂ��Bhttps://dxlib.xsrv.jp/program/dxprogram_3DAction.html ���́� void Player_Move( VECTOR MoveVector )
���̂U�F�����Ƃ����邳�Ƃ������M���ĂȂ�����߂�����Â��B�y����Ȃ�}�e���A���֌W�̊֐��g���Ė�����薾�邭������B
���̂V�F�e�������B�����̉e�Ȃ�Ahttps://dxlib.xsrv.jp/program/dxprogram_3DAction.html ���́�void Player_ShadowRender( void )���Q�l�ɂ���΂����B�y���ĉe����肽�����SetUseShadowMap���g���΂����B���m�ɂ�肽���Ȃ�V�F�[�_�B�Ȃ�ɂ��Ă��e��t���郂�f���i�X�e�[�W���f���j�Ƃ��Ȃ��Əo���Ȃ��i���ɂ����j�B
*/

