#include "Game.hpp"



/// ------------------------------------------------------------------------------------
Game::Game(const std::vector<int>& t_fileData)
{
	mp_character = new Character(t_fileData.at(0));

	mp_camera = new Camera(mp_character->GetArea());
}



/// ------------------------------------------------------------------------------------
Game::~Game()
{
	POINTER_RELEASE(mp_camera);
}



/// ------------------------------------------------------------------------------------
void Game::Update()
{
	VECTOR Pos1;
	VECTOR Pos2;
	float LINE_AREA_SIZE = 10000.0f;
	int LINE_NUM = 50;

	SetUseZBufferFlag(TRUE);

	Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
	Pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
	for (int i = 0; i <= LINE_NUM; i++)
	{
		DrawLine3D(Pos1, Pos2, GetColor(0, 0, 0));
		Pos1.x += LINE_AREA_SIZE / LINE_NUM;
		Pos2.x += LINE_AREA_SIZE / LINE_NUM;
	}

	Pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
	Pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
	for (int i = 0; i < LINE_NUM; i++)
	{
		DrawLine3D(Pos1, Pos2, GetColor(0, 0, 0));
		Pos1.z += LINE_AREA_SIZE / LINE_NUM;
		Pos2.z += LINE_AREA_SIZE / LINE_NUM;
	}

	SetUseZBufferFlag(FALSE);

	mp_character->Draw();


	mp_camera->Process(mp_character->GetArea());
	mp_character->Process(mp_camera->GetAngle());
}
