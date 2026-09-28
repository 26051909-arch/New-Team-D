#include"SpiderBullet.h"
#include"Player.h"
#include"Tree.h"
#include"Effect.h"

SpiderBullet::SpiderBullet(const CVector2D& pos) : Base(eType_Bullet)
{
	m_img = COPY_RESOURCE("SpiderBullet", CImage);

	m_pos = pos;

	//”¼Œa
	m_rad = 48;

	m_img.SetSize(96, 96);
	m_img.SetCenter(48, 48);
}

void SpiderBullet::Update()
{
	const int move_speed = 14;

	m_pos.x += move_speed * m_dir;

	if (m_pos.x < -100 || m_pos.x > SCREEN_WIDTH + 100) {
		SetKill();
	}

}

void SpiderBullet::Draw()
{
	m_img.SetPos(m_pos);
	m_img.Draw();
}


void SpiderBullet::Collision(Base* b)
{
	switch (b->GetType()) {
	case eType_Tree:
		if (Base::CollisionCircle(this, b))
		{
			new Effect(CVector2D(60, 650));

			SetKill();
		}
		break;
	}
}