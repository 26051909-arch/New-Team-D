#include"Player.h"
#include"SpiderBullet.h"
#include"Field.h"
#include"Tree.h"



Player::Player(const CVector2D& pos, bool flip) : Base(eType_Player) 
{
	m_img = COPY_RESOURCE("Player", CImage);
	//座標設定
	m_pos_old = m_pos = pos;
	//サイズ設定
	m_img.SetSize(160, 160);
	//中心位置設定
	m_img.SetCenter(80, 155);


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
	const float move_speed = 8;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 14;

	//右移動
	if (HOLD(CInput::eRight)) {
		//移動量を設定
		m_pos.x += move_speed;
		//反転フラグ
		m_flip = true;
		move_flag = true;
	}

	//左移動
	if (HOLD(CInput::eLeft)) {
		//移動量を設定
		m_pos.x += -move_speed;
		//反転フラグ
		m_flip = false;
		move_flag = true;
	}


	//弾の発射
	if (PUSH(CInput::eMouseL)) {
		if (m_flip == false) {
			//左へ
			CVector2D bulletPos;

			bulletPos.x = m_pos.x - 30;	//プレイヤーの左端
			bulletPos.y = m_pos.y - 20;		//プレイヤーの胸辺り

			SpiderBullet* b = new SpiderBullet(bulletPos);
			b->m_dir = -1;
		}
		else {
			//右へ
			CVector2D bulletPos;

			bulletPos.x = m_pos.x + 30;	//プレイヤーの右端
			bulletPos.y = m_pos.y - 20;		//プレイヤーの胸辺り

			SpiderBullet* b = new SpiderBullet(bulletPos);
			b->m_dir = 1;
		}
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
				m_img.ChangeAnimation(eAnimRun, true);
				
		}
		else {
				//待機アニメーション
				m_img.ChangeAnimation(eAnimIdle, true);
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

	m_img.SetFlipH(m_flip);

	m_img.Draw();


}




void Player::Collision(Base* b) 
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

	case eType_Tree:
		if (Tree* t = dynamic_cast<Tree*>(b)) {
			// 枝の範囲内にいるか
			bool inXRange = (m_pos.x > t->m_pos.x - 480 && m_pos.x < t->m_pos.x + 480);
			bool aboveBranch = (m_pos_old.y <= t->GetGroundY()); // 前フレームで枝より上にいたか
			bool falling = (m_vec.y > 0); // 下方向に移動しているか

			// 枝の上から落ちてきた場合のみ乗る
			if (inXRange && falling && aboveBranch && m_pos.y > t->GetGroundY()) {
				m_pos.y = t->GetGroundY();
				m_vec.y = 0;
				m_is_ground = true;
			}
		}
		break;
	}
}

static TexAnim _idle[] = {
	{0,4},
	{1,4},
	{2,4},
	{3,4},
	{4,4},
};

static TexAnim _run[] = {
	{10,4},
	{11,4},
	{12,4},
	{13,4},
	{14,4},
	//{15,4},
};

static TexAnim _jumpUp[] = {
	{18,2},
	{19,2},
	{20,2},
	{21,2},
	{22,2},
	//{23,2},
};

static TexAnim _jumpDown[] = {
	{23,2},
	{24,2},
	{25,2},
	{26,2},
	//{27,2},
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