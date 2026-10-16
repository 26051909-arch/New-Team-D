#include"Enemy2.h"
#include"Enemy3.h"
#include"Effect.h"
#include"Field.h"

Enemy2::Enemy2(const CVector2D& pos, bool flip) : Base(eType_Enemy2)
{
	m_img = COPY_RESOURCE("Enemy2", CImage);

	m_pos = pos;
	m_rad = 20;
	m_img.SetSize(120, 120);
	m_img.SetCenter(60, 90);

	m_hp = 20.0f;
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;

	m_death_timer = 0;

	m_img.ChangeAnimation(eAnimIdle);
}

void Enemy2::ToDeath()
{
	if (m_state != eState_Death) {
		m_state = eState_Death;
		new Effect(m_pos);
		m_img.ChangeAnimation(eAnimDeath); // アニメーションを繭に切り替え
	}
}

void Enemy2::StateIdle()
{
	//移動量
	const float move_speed = 4;
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

void Enemy2::StateDamage()
{
	//空気抵抗や地面との摩擦のイメージで、徐々に横移動の速度を落とす
	m_vec.x *= 0.5f;

	if (m_img.CheckAnimationEnd()) {
		m_vec.x = 0; //通常状態に戻る時に横の移動速度を完全にリセット
		m_state = eState_Idle;
		m_img.ChangeAnimation(eAnimIdle, true);
	}
}

void Enemy2::StateDeath()
{
	m_death_timer++; // 毎フレーム1ずつ増やす

	//12秒経過したら消滅
	if (m_death_timer >= 720) {
		SetKill();
	}
}

void Enemy2::Update()
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

void Enemy2::Draw()
{
	m_img.SetPos(m_pos);

	m_img.SetFlipH(m_flip);
	m_img.Draw();

}

void Enemy2::Collision(Base* b)
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


	case eType_Enemy3:
		if (Base::CollisionCircle(this, b)) {
			if (Enemy3* enemy3 = dynamic_cast<Enemy3*>(b)) {
				
				if (enemy3->m_state != eState_Death) {

					//コガネムシが通常状態の際は蟻がダメージを食らう
					m_hp -= 12.0f;
					m_state = eState_Damage;
					m_img.ChangeAnimation(eAnimDamage, false);

					// ノックバック処理
					float knockback_x = 12.0f;  // 後ろに吹き飛ぶ強さ
					float knockback_y = -13.0f; // 上に少し跳ね上がる強さ（マイナスが上方向）

					if (m_flip == true) {
						// 蟻が右を向いていたなら、左（マイナス方向）へ吹き飛ばす
						m_vec.x = -knockback_x;
					}
					else {
						// 蟻が左を向いていたなら、右（プラス方向）へ吹き飛ばす
						m_vec.x = knockback_x;
					}
					// 上方向に跳ね上がらせる
					m_vec.y = knockback_y;
					m_is_ground = false; // 空中に浮くため接地フラグをOFFにする
				}
			}
		}
		break;

	}

}

void Enemy2::TakeDamage(int damage)
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
	{4,2},
	{5,2},
	{6,2},
	{7,2},
};

static TexAnim _death[] = {
	{8,3},

};


TexAnimData Enemy2::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_damage),
	ANIMDATA(_death),
};