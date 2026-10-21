#pragma once
#include"Base/Base.h"


class Effect2 : public Base
{
private:

	//アニメーションの種類
	enum {
		eAnimShock,
	};

	//反転フラグ
	//bool m_flip;
	int m_dir = 1;	//1=右、 -1=左
	//衝撃波の消滅までのタイマー
	int m_timer = 0;

	CImage m_img;
	CImage m_img2;

public:


	CVector2D m_pos_left;
	CVector2D m_pos_right;

	Effect2(const CVector2D& pos, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	bool HitTest(const CVector2D& pos, float rad) const;

	static TexAnimData _anim_data[];

};