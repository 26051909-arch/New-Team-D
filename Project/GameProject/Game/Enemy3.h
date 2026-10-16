#pragma once
#include"Base/Base.h"


class Enemy3 : public Base
{
private:

	//アニメーションの種類
	enum {
		eAnimIdle = 0,
		eAnimDamage,
		eAnimDeath,
	};

	//状態
	enum {
		eState_Idle,
		eState_Damage,
		eState_Death,

	};

	//各状態での挙動
	void StateIdle();
	void StateDamage();
	void StateDeath();



	//死亡状態でのタイマー
	int m_death_timer;
	//反転フラグ
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
	//体力
	float m_hp;
	// 方向転換した回数
	int m_turn_count = 0;

	// 方向転換できる最大回数
	const int m_max_turn_count = 3;
	CImage m_img;

public:
	Enemy3(const CVector2D& pos, bool flip);
	void ToDeath();
	void Update();
	void Draw();
	void Collision(Base* b);
	//ダメージ受ける
	void TakeDamage(int damage);

	static TexAnimData _anim_data[];

	//状態変数
	int m_state;

};
