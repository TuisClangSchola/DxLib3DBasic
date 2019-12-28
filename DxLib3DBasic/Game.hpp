#pragma once
#include "Basic.hpp"
#include "Character.hpp"
#include "Camera.hpp"
#include "Panel.hpp"



/*
ゲームじゃないけどキャラクターとかを管理するクラス
*/
class Game
{
private:
	Camera* mp_camera;
	Character* mp_character;
	Panel* mp_panel;

	std::vector<ELOADFILE> m_fileType;

	std::vector<int> m_fileData;


public:
	Game(const std::vector<int>& t_fileData);
	~Game();


	void Update();
};


/*
ちょっとプログラムに意地悪をしました。正確に言えば俺が作ったときのやつから色々削った(*''ω''*)。理由：だんだんめんどくさくなってきた
それを考慮してアドバイス。
その１：実際に3Dのゲームであればスカイボックスがいる。じゃないと遠くの描画がおかしくなる。
*/