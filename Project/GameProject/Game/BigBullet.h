#pragma once
#include"Base/Base.h"


class BigBullet : public Base
{
public:
	CImage m_img;
	int m_dir = 1;	//1=右、 -1=左
	//体力
	float m_hp;
	float m_houkou;

public:
	BigBullet(const CVector2D& pos, float houkou);
	void Update();
	void Draw();
	void Collision(Base* b);
	//ダメージ受ける
	void TakeDamage(int damage);
};
