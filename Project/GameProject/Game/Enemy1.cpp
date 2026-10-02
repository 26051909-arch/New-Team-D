#include"Enemy1.h"


Enemy1::Enemy1(const CVector2D& pos) : Base(eType_Enemy1)
{
	m_img = COPY_RESOURCE("Enemy1", CImage);

	m_pos = pos;
	m_rad = 60;
	m_img.SetSize(120, 120);
	m_img.SetCenter(60, 60);


	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = false;

	m_img.ChangeAnimation(eAnimIdle);

}


void Enemy1::StateIdle()
{
	//移動量
	const float move_speed = 5;
	//移動フラグ
	bool move_flag = true;


	m_pos.x += move_speed;

	if (m_pos.x > SCREEN_WIDTH + 180) {
		SetKill();

	}

}


void Enemy1::StateDeath()
{
	/*m_img.ChangeAnimation(eAnimDeath, false);
	if (m_img.CheckAnimationEnd()) {
		SetKill();
	}*/
}

void Enemy1::Update()
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

	//アニメーションの更新
	m_img.UpdateAnimation();
}

void Enemy1::Draw()
{
	m_img.SetPos(m_pos);

	m_img.Draw();

}

static TexAnim _idle[] = {
	{0,4},
	{1,4},
	{2,4},
	{3,4},
};


static TexAnim _death[] = {
	{4,3},
	{5,3},
	{6,3},
	{7,3},
};


TexAnimData Enemy1::_anim_data[] = {
	ANIMDATA(_idle),
	ANIMDATA(_death),
};