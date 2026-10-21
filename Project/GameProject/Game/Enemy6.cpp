#include"Enemy6.h"
#include"BigBullet.h"
#include"Effect2.h"
#include"Field.h"


Enemy6::Enemy6(const CVector2D& pos, bool flip) : Base(eType_Enemy6)
{
	m_img = COPY_RESOURCE("Enemy6", CImage);

	m_pos = pos;
	m_rad = 240;
	m_img.SetSize(960, 960);
	m_img.SetCenter(480, 930);


	m_hp = 300.0f;
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;

	m_shot_timer = 0;
	m_is_action = false;

	//m_max_turn_count = 3;
	// 方向転換回数を初期化
	//m_turn_count = 0;

	m_img.ChangeAnimation(eAnimIdle);
}


void Enemy6::StateIdle()
{
	//移動量
	const float move_speed = 5.0f;

	//プレイヤーとの停止する距離
	const float stop_distance = 1100.0f;

	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 24;

	Base* player = Base::FindObject(eType_Player);

	//プレイヤーが存在しない場合
	  // プレイヤーが存在しない場合
	if (player == nullptr) {
		m_img.ChangeAnimation(eAnimIdle, true);
		return;
	}


	//プレイヤーとの横方向の距離を計算
	 // プレイヤーとの横方向の距離を計算
	float distance = abs(player->m_pos.x - m_pos.x);
	

	//移動処理
	
	  // 停止距離より離れている場合だけ移動
	if (distance > stop_distance) {

		// プレイヤーが敵より右側にいる場合
		if (player->m_pos.x > m_pos.x) {

			m_flip = true;
			m_pos.x += move_speed;
			move_flag = true;

		}// プレイヤーが敵より左側にいる場合
		else if (player->m_pos.x < m_pos.x) {

			m_flip = false;
			m_pos.x += -move_speed;
			move_flag = true;

		}

	}
	else {
		// 停止距離以内ならプレイヤーの方を向く
		if (player->m_pos.x > m_pos.x) {
			m_flip = true;
		}
		else if (player->m_pos.x < m_pos.x) {
			m_flip = false;
		}
	}
	

	//地面にいるなら
	
		if (move_flag) {
			//走るアニメーション
			m_img.ChangeAnimation(eAnimRun, true);

			m_shot_timer = 0;

		}
		else {
			//待機アニメーション
			m_img.ChangeAnimation(eAnimIdle, true);

			//行動中でなければタイマーを進める
			if (!m_is_action) {
				m_shot_timer++;
			}


			//4秒経過したら行動
			if (m_shot_timer >= 240 && !m_is_action) {

				//タイマーリセット
				m_shot_timer = 0;

				//0か1かランダムに選ぶ
				int action = rand() % 2;

				if (action == 0) {
					//その場で上にジャンプ
					m_vec.y = -24.0f;
					m_is_ground = false;

					// ジャンプアニメーション
					m_img.ChangeAnimation(eAnimJumpUp, false);

					m_is_action = true;
				}
				else {


					if (m_flip == false) {
						//左へ
						CVector2D bulletPos;

						bulletPos.x = m_pos.x - 370;	//プレイヤーの左端
						bulletPos.y = m_pos.y - 100;		//プレイヤーの胸辺り

						BigBullet* b = new BigBullet(bulletPos, 2);
						b->m_dir = -1;
					}
					else {
						//右へ
						CVector2D bulletPos;

						bulletPos.x = m_pos.x + 370;	//プレイヤーの右端
						bulletPos.y = m_pos.y - 100;		//プレイヤーの胸辺り

						BigBullet* b = new BigBullet(bulletPos, 3);
						b->m_dir = 1;
					}

					//行動中フラグ
					//m_is_action = true;
				}
				m_is_action = false;
			}


		}


}

void Enemy6::StateDamage()
{
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
		m_img.ChangeAnimation(eAnimIdle, true);
	}
}

void Enemy6::StateDeath()
{
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}
}

void Enemy6::Update()
{

	m_pos_old = m_pos;


	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;

		//ダメージ状態
	case eState_Damage:
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

void Enemy6::Draw()
{
	m_img.SetPos(m_pos);

	m_img.SetFlipH(m_flip);
	m_img.Draw();
}

void Enemy6::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Field:
		//Feild型へキャスト、型変換できたら
		if (Field* f = dynamic_cast <Field*>(b)) {
			//地面より下にいったら
			if (m_pos.y > f->GetGroundY()) {

				// 着地した瞬間だけ衝撃波を生成
				if (!m_is_ground && m_vec.y > 0) {

					new Effect2(m_pos, m_flip);
				}

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


void Enemy6::ToDeath()
{
	if (m_state != eState_Death) {
		m_state = eState_Death;
		//new Effect(m_pos);
		m_img.ChangeAnimation(eAnimDeath, false);
	}


}

void Enemy6::TakeDamage(int damage) 
{
	//HP減少　　下限0
	m_hp = max(m_hp - damage, 0);
	if (m_hp <= 0) {
		ToDeath();
	}
	else {
		m_state = eState_Damage;
		m_img.ChangeAnimation(eAnimDamage, false);
	}
}


static TexAnim _idle[] = {
	{0,6},
	{1,6},
	{2,6},
	{3,6},
	{4,6},
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
	{36,6},
	{37,6},
	{38,6},
	{39,6},
};

static TexAnim _damage[] = {
	{45,3},
	{46,3},
	{47,3},
};

static TexAnim _death[] = {
	{54,4},
	{55,4},
	{56,4},
	{57,4},
	{58,4},
	{59,4},
	{60,4},
	{61,4},
	{62,4},
};


TexAnimData Enemy6::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_run),
	ANIMDATA(_jumpUp),
	ANIMDATA(_jumpDown),
	ANIMDATA(_turisagari),
	ANIMDATA(_shootweb),
	ANIMDATA(_damage),
	ANIMDATA(_death),
};