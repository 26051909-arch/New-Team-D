#include"SpiderBullet.h"
#include"Player.h"
#include"Enemy1.h"
#include"Enemy2.h"
#include"Enemy3.h"
#include"Enemy4.h"
#include"Effect.h"

SpiderBullet::SpiderBullet(const CVector2D& pos, float houkou) : Base(eType_Bullet)
{
	m_img = COPY_RESOURCE("SpiderBullet", CImage);

	m_pos = pos;

	m_houkou = houkou;

	//半径
	m_rad = 48;

	m_img.SetSize(96, 96);
	m_img.SetCenter(48, 48);
}

void SpiderBullet::Update()
{
	const int move_speed = 14;

	if (m_houkou == 2) {
		m_pos.x += move_speed * m_dir;
	}
	else {
		m_pos.y += -move_speed;
	}


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
	/*case eType_Tree2:
		if (Base::CollisionRect(this, b))
		{
			new Effect(m_pos);

			SetKill();
		}
		break;*/


	case eType_Enemy1:
		if (Base::CollisionCircle(this, b))
		{
			Enemy1* enemy = (Enemy1*)b;
			enemy->ToDeath();

			// 弾自身は消滅させる
			SetKill();

			// 必要であればエフェクトを出す
			new Effect(m_pos);

			

		}
		break;


	case eType_Enemy2:
		if (Base::CollisionCircle(this, b))
		{
			Enemy2* enemy = (Enemy2*)b;
			enemy->TakeDamage(10.0f);


			// 弾自身は消滅させる
			SetKill();



		}
		break;

	case eType_Enemy3:
		if (Base::CollisionCircle(this, b))
		{
			Enemy3* enemy = (Enemy3*)b;
			enemy->TakeDamage(10.0f);


			// 弾自身は消滅させる
			SetKill();



		}
		break;


	case eType_Enemy4:
		if (Base::CollisionCircle(this, b))
		{
			Enemy1* enemy = (Enemy1*)b;
			enemy->ToDeath();

			// 弾自身は消滅させる
			SetKill();

			// 必要であればエフェクトを出す
			new Effect(m_pos);



		}
		break;
	}

}