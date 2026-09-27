#pragma once
#include"../Base/Base.h"

class SpiderBullet : public Base
{
public:
	CImage m_img;
	int m_dir = 1;	//1=âEÅA -1=ç∂

public:
	SpiderBullet(const CVector2D& pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};
