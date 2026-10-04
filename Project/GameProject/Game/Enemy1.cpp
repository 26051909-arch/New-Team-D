#include"Enemy1.h"
#include"Field.h"


Enemy1::Enemy1(const CVector2D& pos, bool flip) : Base(eType_Enemy1)
{
	m_img = COPY_RESOURCE("Enemy1", CImage);

	m_pos = pos;
	m_rad = 60;
	m_img.SetSize(120, 120);
	m_img.SetCenter(60, 60);

	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
	//重力フラグ
	m_grav = false;

	m_img.ChangeAnimation(eAnimIdle);

}


void Enemy1::ToDeath()
{
	if (m_state != eState_Death) {
		m_state = eState_Death;
		m_grav = true;
		m_img.ChangeAnimation(eAnimDeath); // アニメーションを繭に切り替え
	}
}

void Enemy1::StateIdle()
{
	//移動量
	const float move_speed = 5;
	//移動フラグ
	bool move_flag = true;


	if (m_flip == true) {
		m_pos.x += move_speed;
		if (m_pos.x > SCREEN_WIDTH + 180) {
			SetKill();

		}
	}
	else {
		m_pos.x -= move_speed;
		if (m_pos.x < -125) {
			SetKill();
		}
	}

}


/*void Enemy1::StateDeath()
{
	m_img.ChangeAnimation(eAnimDeath, false);
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}*/

void Enemy1::Update()
{
	m_pos_old = m_pos;


	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;

		//ダウン状態
	/*case eState_Death:
		StateDeath();
		break;*/

	}

	if (m_grav == true)
	{
		if(m_is_ground && m_vec.y > GRAVITY * 4)
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

void Enemy1::Draw()
{
	m_img.SetPos(m_pos);

	m_img.SetFlipH(m_flip);
	m_img.Draw();

}


void Enemy1::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		//Feild型へキャスト、型変換できたら
		if (Field* f = dynamic_cast <Field*>(b)) {
			//地面より下にいったら
			if (m_pos.y > f->GetGroundY()) {
				//地面の高さに戻す
				m_pos.y = f->GetGroundY();
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
	{0,2},
	{1,2},
	{2,2},
	{3,2},
};


static TexAnim _death[] = {
	{7,3},
	
};


TexAnimData Enemy1::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_death),
};