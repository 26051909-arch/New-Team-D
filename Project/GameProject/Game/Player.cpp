#include"Player.h"

Player::Player(const CVector2D& pos, bool flip) : Base(eType_Player) 
{
	m_img = COPY_RESOURCE("Player", CImage);
	//座標設定
	m_pos_old = m_pos = pos;
	//サイズ設定
	m_img.SetSize(96, 96);
	//中心位置設定
	m_img.SetCenter(48, 93);


	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
	m_img.ChangeAnimation(eAnimIdle);
}


void Player::StateIdle()
{
	//移動量
	const float move_speed = 6;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 16;

	//右移動
	if (HOLD(CInput::eRight)) {
		//移動量を設定
		m_pos.x += move_speed;
		//反転フラグ
		m_flip = false;
		move_flag = true;
	}

	//左移動
	if (HOLD(CInput::eLeft)) {
		//移動量を設定
		m_pos.x += -move_speed;
		//反転フラグ
		m_flip = true;
		move_flag = true;
	}


	//ジャンプ
	if (m_is_ground && PUSH(CInput::eButton5)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
	}

	//ジャンプ中なら
	if (!m_is_ground) {
		if (m_vec.y < 0) {
			//上昇アニメ―ション
			m_img.ChangeAnimation(eAnimJumpUp, false);
		}
		else {
			//下降アニメーション
			m_img.ChangeAnimation(eAnimJumpDown, false);
		}
	}

	//地面にいるなら
	else
	{
		if (move_flag) {
			//走るアニメーション
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			//待機アニメーション
			m_img.ChangeAnimation(eAnimIdle);
		}
	}


}

void Player::StateDamage()
{

}

void Player::StateDeath()
{
	m_img.ChangeAnimation(eAnimDeath, false);
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}



void Player:: Update()
{
	m_pos_old = m_pos;


	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;

		//ダメージ状態
	case eStateDamage:
		StateDamage();
		break;

		//ダウン状態
	case eState_Death:
		StateDeath();
		break;
	}

	//落ちていたら落下中状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;


	//重力による落下処理
	m_vec.y += GRAVITY;
	m_pos += m_vec;


	//アニメーションの更新
	m_img.UpdateAnimation();
}



void Player::Draw()
{
	m_img.SetPos(m_pos);

	m_img.Draw();

	m_img.SetFlipH(m_flip);

}




void Player::Collision(Base* b) 
{

}

static TexAnim _idle[] = {
	{0,2},
	{1,2},
	{2,2},
	{3,2},
	{4,2},
};

static TexAnim _run[] = {
	{5,4},
	{6,4},
	{7,4},
	{8,4},
	{9,4},
	{10,4},
};

static TexAnim _jumpUp[] = {
	{11,4},
	{12,4},
	{13,4},
	{14,4},
	{15,4},
};

static TexAnim _jumpDown[] = {
	{16,4},
	{17,4},
	{18,4},
	{19,4},
};

static TexAnim _turisagari[] = {
	{20,4},
};

static TexAnim _shootweb[] = {
	{21,4},
	{22,4},
	{23,4},
	{24,4},
};

static TexAnim _damage[] = {
	{25,4},
	{26,4},
	{27,4},
};

static TexAnim _death[] = {
	{28,4},
	{29,4},
	{30,4},
	{31,4},
	{32,4},
	{33,4},
	{34,4},
	{35,4},
	{36,4},
};


TexAnimData Player::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
	ANIMDATA(_jumpUp),
	ANIMDATA(_jumpDown),
	ANIMDATA(_turisagari),
	ANIMDATA(_shootweb),
	ANIMDATA(_damage),
	ANIMDATA(_death),
};