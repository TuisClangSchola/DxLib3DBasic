#pragma once
#include "Basic.hpp"
#include "Character.hpp"
#include "Camera.hpp"


/*
ゲームじゃないけどキャラクターとかを管理するクラス
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

