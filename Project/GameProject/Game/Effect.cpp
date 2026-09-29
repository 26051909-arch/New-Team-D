#include"Effect.h"
#include"StickyWeb.h"


Effect::Effect() : Base(eType_Effect)
{
	m_img = COPY_RESOURCE("Effect", CImage);
	//m_pos = pos;

	m_img.SetSize(256, 256);
	m_img.ChangeAnimation(0, false);

}

void Effect::Update()
{
	m_img.UpdateAnimation();

	if (m_img.CheckAnimationEnd())
	{
		// エフェクトが終わったら新しいオブジェクトを生成
		new StickyWeb();

		SetKill();
	}
}


void Effect::Draw()
{
	//m_img.SetPos();
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