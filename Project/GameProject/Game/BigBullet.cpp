#include"BigBullet.h"
#include"Enemy1.h"
#include"Enemy2.h"
#include"Enemy3.h"
#include"Effect.h"


BigBullet::BigBullet(const CVector2D& pos, float houkou) : Base(eType_BigBullet)
{
	m_img = COPY_RESOURCE("BigBullet", CImage);

	m_pos = pos;
	m_houkou = houkou;

	//半径
	m_rad = 200;

	m_img.SetSize(400, 400);
	m_img.SetCenter(200, 200);

	m_hp = 50.0f;
}



void BigBullet::Update()
{
	const int move_speed = 5;

	if (m_houkou == 2) {
		m_pos.x += move_speed * m_dir;
	}
	else {
		m_pos.x += move_speed;
	}


	if (m_pos.x < -300 || m_pos.x > SCREEN_WIDTH + 300) {
		SetKill();
	}

}


void BigBullet::Draw()
{
	m_img.SetPos(m_pos);

	// 右向きなら反転、左向きならそのまま
	if (m_dir == 1) {
		m_img.SetFlipH(true);
	}
	else {
		m_img.SetFlipH(false);
	}

	m_img.Draw();
}


void BigBullet::Collision(Base* b)
{
	switch (b->GetType()) {

	case eType_Enemy1:
		if (Base::CollisionCircle(this, b))
		{
			Enemy1* enemy = (Enemy1*)b;
			enemy->ToDeath();

			// 必要であればエフェクトを出す
			//new Effect(m_pos);

		}
		break;


	case eType_Enemy2:
		if (Base::CollisionCircle(this, b))
		{
			Enemy2* enemy = (Enemy2*)b;
			enemy->ToDeath();

		}
		break;

	case eType_Enemy3:
		if (Base::CollisionCircle(this, b))
		{
			Enemy3* enemy = (Enemy3*)b;
			enemy->ToDeath();

		}
		break;


	case eType_Enemy4:
		if (Base::CollisionCircle(this, b))
		{
			Enemy1* enemy = (Enemy1*)b;
			enemy->ToDeath();

			// 必要であればエフェクトを出す
			//new Effect(m_pos);

		}
		break;
	}

}

void BigBullet::TakeDamage(int damage)
{
	//HP減少　　下限0
	m_hp = max(m_hp - damage, 0);
	if (m_hp <= 0) {
		SetKill();
	}
}