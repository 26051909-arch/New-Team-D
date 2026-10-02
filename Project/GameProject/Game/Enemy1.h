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
	void StateDeath();


	//状態変数
	int m_state;
	//着地フラグ
	bool m_is_ground;
	CImage m_img;

public:
	Enemy1(const CVector2D& pos);
	void Update();
	void Draw();
	//void CollisionCircle(Base* b);

	static TexAnimData _anim_data[];

};
