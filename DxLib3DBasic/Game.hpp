#pragma once
#include "Basic.hpp"
#include "Character.hpp"
#include "Camera.hpp"


/*
�Q�[������Ȃ����ǃL�����N�^�[�Ƃ����Ǘ�����N���X
*/
class Game
{
private:
	Camera* mp_camera;
	Character* mp_character;

	std::vector<ELOADFILE> m_fileType;

	std::vector<int> m_fileData;


public:
	Game(const std::vector<int>& t_fileData);
	~Game();


	void Update();
};

