#include"Enemy5.h"
#include"Field.h"

Enemy5::Enemy5(const CVector2D& pos, bool flip) : Base(eType_Enemy5)
{
	m_img = COPY_RESOURCE("Enemy5", CImage);

	m_pos = pos;
	m_rad = 64;
	m_img.SetSize(256, 256);
	m_img.SetCenter(128, 128);

	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
	//重力フラグ
	m_grav = true;

	m_death_timer = 0;

	m_img.ChangeAnimation(eAnimIdle);
}

void Enemy5::ToDeath()
{
	if (m_state != eState_Death) {
		m_state = eState_Death;
		m_grav = true;
		m_img.ChangeAnimation(eAnimDeath); // アニメーションを繭に切り替え
	}
}


void Enemy5::StateIdle()
{
	//移動量
	const float move_speed = 3;
	//移動フラグ
	bool move_flag = true;


	if (m_flip == true) {
		m_pos.x -= move_speed;
		if (m_pos.x > SCREEN_WIDTH + 170) {
			SetKill();

		}
	}
	else {
		m_pos.x -= move_speed;
		if (m_pos.x < -170) {
			SetKill();
		}
	}

}

void Enemy5::StateDeath()
{
	m_death_timer++; // 毎フレーム1ずつ増やす

	//8秒経過したら消滅
	if (m_death_timer >= 480) {
		SetKill();
	}
}

void Enemy5::Update()
{
	m_pos_old = m_pos;


	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;

		//ダウン状態
	case eState_Death:
		StateDeath();
		break;

	}

	if (m_grav == true)
	{
		if (m_is_ground && m_vec.y > GRAVITY * 4)
			m_is_ground = false;
	}

	if (m_grav == true)
	{
		//重力による落下処理
		m_vec.y += GRAVITY;
		m_pos += m_vec;
	}

	//アニメーションの更新
	m_img.UpdateAnimation();
}


void Enemy5::Draw()
{
	m_img.SetPos(m_pos);

	m_img.SetFlipH(m_flip);
	m_img.Draw();

}

void Enemy5::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		//Feild型へキャスト、型変換できたら
		if (Field* f = dynamic_cast <Field*>(b)) {
			//地面より下にいったら
			if (m_pos.y +64 > f->GetGroundY()) {
				//地面の高さに戻す
				m_pos.y = f->GetGroundY() - 64;
				//落下速度リセット
				m_vec.y = 0;
				//接地フラグON
				m_is_ground = true;
			}
		}
		break;

	}
}


static TexAnim _idle[] = {
	{0,3},
	{1,3},
	{2,3},
	{3,3},
};


static TexAnim _death[] = {
	{8,3},

};


TexAnimData Enemy5::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_death),
};