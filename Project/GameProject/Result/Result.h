#pragma once 
#include "Base/Base.h" 
class Result : 
public Base { 
private: 
	CImage m_img; 
	CFont* m_font; 
	int	   m_day; // š ‚±‚±‚Å m\_day ‚ğéŒ¾‚µ‚Ä‚¢‚é‚©Šm”FI
	int m_eat_count;
	int	   m_timer;

public: 
	Result(int day, int eat_count); 
	void Update() override; 
	void Draw() override; 
};