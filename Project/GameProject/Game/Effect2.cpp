#include"Effect2.h"


Effect2::Effect2(const CVector2D& pos) : Base(eType_Effect2)
{
	m_img = COPY_RESOURCE("Effect2", CImage);
	m_pos = pos;
}

void Effect2::Update()
{

}


void Effect2::Draw()
{

}



static TexAnim _effect_impact[] = {
	{18,3},
	{19,3},
	{20,3},
	{21,3},
	{22,3},
};


TexAnimData Effect2::_anim_data[] = {
	ANIMDATA(_effect_impact),
};