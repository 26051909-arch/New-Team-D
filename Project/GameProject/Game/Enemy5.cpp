#include "Enemy5.h" 
#include "Player.h"
#include "Field.h"

Enemy5::Enemy5(const CVector2D& pos, bool flip) : Base(eType_Enemy5)
{
	m_img = COPY_RESOURCE("Enemy5", CImage);

	m_pos = pos; 
	m_rad = 64;

	m_img.SetSize(256, 256); 
	m_img.SetCenter(128, 128);

	m_hp = 50.0f;
	m_flip = flip;
	m_state = eState_Idle; 
	m_is_ground = true;
	m_death_timer = 0;

	m_img.ChangeAnimation(eAnimIdle, true);
}

void Enemy5::ToDeath()
{
	if (m_state != eState_Death) {
		m_state = eState_Death;
		m_img.ChangeAnimation(eAnimDeath, false);

		m_img.SetSize(128, 128);
		m_img.SetCenter(64, 64);
	}
}

void Enemy5::TakeDamage(int damage)
{
	m_hp -= (float)damage; 
	if (m_hp <= 0.0f) {
		ToDeath();
	}
}

void Enemy5::StateIdle()
{
	const float move_speed = 3.0f;
	const float attack_range = 140.0f;

	Base* player = Base::FindObject(eType_Player);
	if (player != nullptr) {
		float dist_x = fabsf(player->m_pos.x - m_pos.x);
		float dist_y = fabsf(player->m_pos.y - m_pos.y);

		if (dist_x <= attack_range && dist_y <= 100.0f) {
			m_state = eState_Attack;
			m_img.ChangeAnimation(eAnimAttack, false);
			return;
		}
	}

	if (m_flip == true) {
		m_pos.x -= move_speed;
		if (m_pos.x < -170)SetKill();
	}
	else {
		m_pos.x += move_speed;
		if (m_pos.x > SCREEN_WIDTH + 170) SetKill();
	}
}

void Enemy5::StateAttack() {
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
		m_img.ChangeAnimation(eAnimIdle, true);
	}
}

void Enemy5::StateDeath() {
	m_death_timer++;
	if (m_death_timer >= 480) {
		SetKill();
	}
}

void Enemy5::Update() {
	m_pos_old = m_pos;

	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Attack:
		StateAttack();
		break;
	case eState_Death:
		StateDeath();
		break;
	}

	m_vec.y += GRAVITY;
	m_pos += m_vec;
	m_img.UpdateAnimation();
}

void Enemy5::Draw() { 
	m_img.SetPos(m_pos); 
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}

void Enemy5::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		if (Field* f = dynamic_cast<Field*>(b)) {
			if (m_state == eState_Death) {
				if (m_pos.y + 64 > f->GetGroundY()) {
					m_pos.y = f->GetGroundY() - 64;
					m_vec.y = 0; m_is_ground = true;
				}
			}
			else {
				if (m_pos.y + 65 > f->GetGroundY()) {
					m_pos.y = f->GetGroundY() - 65;
					m_vec.y = 0;
					m_is_ground = true;
				}
			}
		} break;

	case eType_Player_Attack:
	case eType_Bullet:
		if (m_state != eState_Death) {
			if (Base::CollisionCircle(this, b)) {
				TakeDamage(10);
				b->SetKill();
			}
		}
		break;
	}
}

static TexAnim _idle[] = {
	{0, 4}, 
	{1, 4}, 
	{2, 4}, 
	{3, 4}, 
};

static TexAnim _attack[] = { 
	{4, 4},
	{5, 4},
	{6, 4},
	{7, 4}, 
};

static TexAnim _death[] = { 
	{8, 4}, 
};

TexAnimData Enemy5::_anim_data[] = { 
	ANIMDATA(_idle), // 0: ï‡Ç´ 
	ANIMDATA(_attack), // 1: çUåÇ
	ANIMDATA(_death), // 2: éÄñS 
};