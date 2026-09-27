#pragma once
#include"Base/Base.h"

class Player : public Base {
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
		eStateDamage,
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
	CImage m_img;

	



public:
	Player(const CVector2D& pos, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);

	static TexAnimData _anim_data[];

};
