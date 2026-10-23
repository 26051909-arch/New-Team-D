#include"Slash.h"
#include"Player.h"
#include"Enemy2.h"
#include"Enemy3.h"
#include"Enemy6.h"


Slash::Slash(const CVector2D& pos, float houkou) : Base(eType_Slash)
{
	m_img = COPY_RESOURCE("Slash", CImage);

	m_pos = pos;

	m_houkou = houkou;

	//îºåa
	m_rad = 80;

	m_img.SetSize(160, 160);
	m_img.SetCenter(80, 80);

	m_img.ChangeAnimation(eAnimSlash, true);
}


void Slash::Update()
{
	const int move_speed = 7;

	if (m_houkou == 2) {
		m_pos.x += move_speed * m_dir;
	}
	else {
		m_pos.x += move_speed;
	}


	if (m_pos.x < -200 || m_pos.x > SCREEN_WIDTH + 200) {
		SetKill();
	}

	m_img.UpdateAnimation();

}

void Slash::Draw()
{
	if (m_houkou == 2) {
		m_img.SetPos(m_pos.x + 60, m_pos.y - 50);
	}
	else {
		m_img.SetPos(m_pos.x - 60, m_pos.y - 50);
	}


	// âEå¸Ç´Ç»ÇÁîΩì]ÅAç∂å¸Ç´Ç»ÇÁÇªÇÃÇ‹Ç‹
	if (m_dir == -1) {
		m_img.SetFlipH(true);
	}
	else {
		m_img.SetFlipH(false);
	}

	m_img.Draw();

}

void Slash::Collision(Base* b)
{
	switch (b->GetType()) {

	case eType_Enemy2:
		if (Base::CollisionCircle(this, b))
		{
			Enemy2* enemy = (Enemy2*)b;
			//enemy->TakeDamage(10.0f);

			SetKill();

		}
		break;

	case eType_Enemy3:
		if (Base::CollisionCircle(this, b))
		{
			Enemy3* enemy = (Enemy3*)b;
			//enemy->TakeDamage(20.0f);

			SetKill();

		}
		break;

	case eType_Enemy6:
		if (Base::CollisionCircle(this, b))
		{
			Enemy6* enemy = (Enemy6*)b;
			enemy->TakeDamage(25.0f);


			// íeé©êgÇÕè¡ñ≈Ç≥ÇπÇÈ
			SetKill();



		}
		break;

	}

}


static TexAnim _slash[] = {
	{0,3},
	{1,3},
};


TexAnimData Slash::_anim_data[] = {
	ANIMDATA(_slash),
};