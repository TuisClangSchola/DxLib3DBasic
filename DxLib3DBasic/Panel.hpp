#pragma once
#include "Basic.hpp"



/*
�����蔻���m�炵�߂邽�߂̃p�l��
*/
class Panel
{
private:
	int m_model;


public:
	Panel(const int& t_model);
	~Panel();


	void Draw();
};


/*
������ƃv���O�����ɈӒn�������܂����B���m�Ɍ����Ή���������Ƃ��̂����F�X�����(*''��''*)
������l�����ăA�h�o�C�X�B
���̂P�F�X�N���[���O�ɏo����`��������Ȃ��悤�ɂ��Ă��Ȃ��BCheckCameraViewClip_Box�Ƃ�������B
���̂Q�F���f���p�ӂ���̂߂�ǂ�����������V�����o��̖ځB
*/
