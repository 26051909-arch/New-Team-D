#pragma once
#include"Base/Base.h"

class Enemy6 : public Base {
private:
	//アニメーションの種類
	enum {
		eAnimIdle = 0,
		eAnimRun,
		eAnimJumpUp,
		eAnimJumpDown,
		eAnimTurisagari,
		eAnimShootWeb,
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
	//反転フラグ
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
	//行動中フラグ
	bool m_is_action;

	//体力
	float m_hp;

	int m_shot_timer;

	CImage m_img;





public:
	Enemy6(const CVector2D& pos, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	void ToDeath();
	//ダメージ受ける
	void TakeDamage(int damage);

	static TexAnimData _anim_data[];
	float GetHP() {
		return m_hp;
	}

};
