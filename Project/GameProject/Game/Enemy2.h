#pragma once
#include"Base/Base.h"


class Enemy2 : public Base
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


	//状態変数
	int m_state;
	//死亡状態でのタイマー
	int m_death_timer;
	//反転フラグ
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
	//体力
	float m_hp;
	CImage m_img;

public:
	Enemy2(const CVector2D& pos, bool flip);
	void ToDeath();
	void Update();
	void Draw();
	void Collision(Base* b);
	//ダメージ受ける
	void TakeDamage(int damage);

	static TexAnimData _anim_data[];

};
