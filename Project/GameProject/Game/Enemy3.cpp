#include"Enemy3.h"
#include"Enemy2.h"
#include"Player.h"
#include"Field.h"
#include"Effect.h"

Enemy3::Enemy3(const CVector2D& pos, bool flip) : Base(eType_Enemy3)
{
	m_img = COPY_RESOURCE("Enemy3", CImage);

	m_pos = pos;
	m_rad = 20;
	m_img.SetSize(120, 120);
	m_img.SetCenter(60, 90);


	m_hp = 40.0f;
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
	m_max_turn_count = 3;
	// 方向転換回数を初期化
	m_turn_count = 0;

	m_death_timer = 0;

	m_img.ChangeAnimation(eAnimIdle);
}

void Enemy3::ToDeath()
{
	if (m_state != eState_Death) {
		m_state = eState_Death;
		new Effect(m_pos);
		m_img.ChangeAnimation(eAnimDeath); // アニメーションを繭に切り替え
	}
}


void Enemy3::StateIdle()
{
	//移動量
	float move_speed = 7;

	Base* player = Base::FindObject(eType_Player);

	// 方向転換できる回数が残っている場合だけ判定
	if (player != nullptr && m_turn_count <= m_max_turn_count)
	{
		// プレイヤーが敵より右側にいる場合
		if (player->m_pos.x > m_pos.x) {

			// 左向きから右向きに変わる場合だけカウント
			if (m_flip == false)
			{
				m_flip = true;

				// 突進速度に変更
				move_speed = 10.0f;

				m_pos.x += move_speed;
				m_turn_count++;

			}
		}

		// プレイヤーが敵より左側にいる場合
		else if (player->m_pos.x < m_pos.x) {

			// 右向きから左向きに変わる場合だけカウント
			if (m_flip == true) 
			{
				m_flip = false;

				// 突進速度に変更
				move_speed = 10.0f;

				m_pos.x += -move_speed;
				m_turn_count++;
			}
		}
	}

	//移動量
	//const float move_speed = 4;
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


void Enemy3::StateDeath()
{
	m_death_timer++; // 毎フレーム1ずつ増やす

	//6秒経過したら消滅
	if (m_death_timer >= 360) {
		SetKill();
	}
}


void Enemy3::StateDamage()
{
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
		m_img.ChangeAnimation(eAnimIdle, true);
	}
}


void Enemy3::Update()
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

void Enemy3::Draw()
{
	m_img.SetPos(m_pos);

	m_img.SetFlipH(m_flip);
	m_img.Draw();

}

void Enemy3::Collision(Base* b)
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


	case eType_Enemy1:
		if (Base::CollisionCircle(this, b)) {
			b->SetKill();
		
		}
		break;


	case eType_Enemy2:
		if (Base::CollisionCircle(this, b))
		{
			if (Enemy2* enemy2 = dynamic_cast<Enemy2*>(b)) {
				//敵2の状態が「死亡状態（繭）」のときだけ中を実行する
				if (enemy2->m_state == eState_Death) {
					enemy2->SetKill();
				}

			}


		}
		break;


	case eType_Enemy4:
		if (Base::CollisionCircle(this, b)) {
			b->SetKill();

		}
		break;

	}
}

void Enemy3::TakeDamage(int damage)
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
	{0,4},
	{1,4},
	{2,4},
	{3,4},
};


static TexAnim _damage[] = {
	{5,2},
	{6,2},
	{7,2},
	{8,2},
	{9,2},
};

static TexAnim _death[] = {
	{10,3},

};


TexAnimData Enemy3::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_damage),
	ANIMDATA(_death),
};