#pragma once
#include"Base/Base.h"

class Enemy1 : public Base
{
private:

	//アニメーションの種類
	enum {
		eAnimIdle = 0,
		eAnimDeath,
	};

	//状態
	enum {
		eState_Idle,
		eState_Death,

	};

	//各状態での挙動
	void StateIdle();
	//void StateDeath();


	//状態変数
	int m_state;
	//反転フラグ
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
	//重力フラグ
	int m_grav;
	CImage m_img;

public:
	Enemy1(const CVector2D& pos, bool flip);
	void ToDeath();
	void Update();
	void Draw();
	void Collision(Base* b);

	static TexAnimData _anim_data[];

};
