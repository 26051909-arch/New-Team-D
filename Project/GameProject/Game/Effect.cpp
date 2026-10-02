#include"Effect.h"
#include"StickyWeb.h"


Effect::Effect(const CVector2D& pos) : Base(eType_Effect)
{
	m_img = COPY_RESOURCE("Effect", CImage);
	m_pos = pos;

	m_img.SetSize(124, 124);
	m_img.ChangeAnimation(0, false);

}

void Effect::Update()
{
	m_img.UpdateAnimation();

	if (m_img.CheckAnimationEnd())
	{

		SetKill();
	}
}


void Effect::Draw()
{
	m_img.SetPos(m_pos);
	m_img.Draw();
}

static TexAnim _effect_web[] = {
	{0,4},
	{1,4},
	{2,4},
	{3,4},
};

TexAnimData effectAnimData[] = {
	ANIMDATA(_effect_web),
};