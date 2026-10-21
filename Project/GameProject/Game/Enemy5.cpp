#include "Enemy5.h" 
#include "Player.h"
#include"Effect.h"
#include"Field.h"
#include "HP.h"

Enemy5::Enemy5(const CVector2D& pos, bool flip) : Base(eType_Enemy5)
{
	m_img = COPY_RESOURCE("Enemy5", CImage);

	m_pos = pos; 
	/*m_rad = 40;

	m_img.SetSize(256, 256); 
	m_img.SetCenter(128, 226);*/
	m_rad = 40;
	m_img.SetSize(280, 280);
	m_img.SetCenter(140, 200);


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
		//m_grav = true;
		new Effect(m_pos);
		m_img.ChangeAnimation(eAnimDeath); // アニメーションを繭に切り替え
	}
	
}

void Enemy5::TakeDamage(int damage)
{
	//HP減少　　下限0
	m_hp = max(m_hp - damage, 0);
	if (m_hp <= 0) {
		ToDeath();
	}
	else {
		m_state = eState_Damage;
		m_img.ChangeAnimation(eAnimIdle, false);
		const float knockback_x = 14.0f;	// 後ろに吹き飛ぶ強さ
		const float knockback_y = -8.0f;	// 上に少し跳ね上がる強さ（マイナスが上方向）

		if (m_flip == true) {
			// プレイヤーが左を向いていたなら、右へ吹き飛ばす
			m_vec.x = knockback_x;
		}
		else {
			// プレイヤーが右を向いていたなら、左へ吹き飛ばす
			m_vec.x = -knockback_x;
		}
		// 上方向に跳ね上がらせる
		m_vec.y = knockback_y;
		m_is_ground = false; // 空中に浮くため接地フラグをOFFにする
	}
}

void Enemy5::StateIdle()
{

	//移動量
	const float move_speed = 3;
	const float attack_range = 500.0f; // 攻撃を開始する距離(ピクセル)
	//移動フラグ
	bool move_flag = true;


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

	if (m_flip == false) {
		m_pos.x += move_speed;
		if (m_pos.x > SCREEN_WIDTH + 250) {
			SetKill();
		}
	}
	else {
		m_pos.x -= move_speed;
		if (m_pos.x < -250) {
			SetKill();
		}
	}
}

void Enemy5::StateDamage() {
	m_vec.x *= 0.5f;
	if (m_is_ground) {
		m_vec.x = 0;
		m_state = eState_Idle;
		//m_img.ChangeAnimation(eAnimIdle, true);
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


	case eState_Damage:
		StateDamage();
		break;

	case eState_Death:
		StateDeath();
		break;
	}

	
if (m_is_ground && m_vec.y > GRAVITY * 4)
	m_is_ground = false;
	
//重力による落下処理
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
			//地面より下にいったら
			if (m_pos.y > f->GetGroundY()) {
				//地面の高さに戻す
				m_pos.y = f->GetGroundY();
				//落下速度リセット
				m_vec.y = 0;
				//接地フラグON
			}
		} break;
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
	ANIMDATA(_idle), // 0: 歩き 
	ANIMDATA(_attack), // 1: 攻撃
	ANIMDATA(_death), // 2: 死亡 
};