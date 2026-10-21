#pragma once 
#include "Base/Base.h"

class Enemy5 : public Base
{
public:
	enum {
		eAnimIdle = 0,
		eAnimAttack,
		eAnimDeath,
	};

	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Death, // 死亡状態
	};

	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDeath();

	float m_hp;
	int m_death_timer;
	bool m_flip;
	bool m_is_ground;
	CImage m_img;

public:
	Enemy5(const CVector2D& pos, bool flip);
	void ToDeath();
	void TakeDamage(int damage);
	void Update() override;
	void Draw() override;
	void Collision(Base* b) override;

	static TexAnimData _anim_data[];

	//状態変数
	int m_state;
};