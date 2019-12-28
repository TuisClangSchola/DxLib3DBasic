#include "Panel.hpp"



/// ------------------------------------------------------------------------------------
Panel::Panel(const int& t_model)
{
	m_model = 0;
	m_model = MV1DuplicateModel(t_model);

	MV1SetPosition(m_model, VGet(1000.0f, 30.0f, 0.0f));
}



/// ------------------------------------------------------------------------------------
Panel::~Panel()
{
	MODEL_RELEASE(m_model);
}



/// ------------------------------------------------------------------------------------
void Panel::Draw()
{
	MV1DrawModel(m_model);

	DrawCapsule3D(VGet(1000.0f, 30.0f, 0.0f), VAdd(VGet(1000.0f, 30.0f, 0.0f), VGet(0.0f, MV1GetFramePosition(m_model, 7).y, 0.0f))
		, 50.0f, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), false);
}
