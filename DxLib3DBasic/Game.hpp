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

	std::vector<ELOADFILE> m_fileType;

	std::vector<int> m_fileData;


public:
	Game(std::vector<ELOADFILE>& t_fileType, std::vector<int>& t_fileData);
	~Game();


	void Update();
};

