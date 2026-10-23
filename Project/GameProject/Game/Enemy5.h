#pragma once
#include"Base/Base.h"




class Enemy5 : public Base
{
public:


    //アニメーションの種類
    enum {
        eAnimIdle = 0,
        eAnimAttack, // 攻撃 (コマ 5〜8)
        eAnimDeath,
    };


    //状態
    enum {
        eState_Idle,
        eState_Attack, // 攻撃状態
        eState_Damage,
        eState_Death,
        eState_Cooldown
    };


    //各状態での挙動
    void StateIdle();
    void StateAttack();
    void StateDamage();
    void StateDeath();
    void StateCooldown();


    
    float m_hp;
    //死亡状態でのタイマー
    int m_death_timer;
    //反転フラグ
    bool m_flip;
    //着地フラグ
    bool m_is_ground;

    int m_attack_timer; // 溜め・発射間隔・クールタイム用
    int m_slash_count;  // 発射したSlashの数


    bool m_is_attacked;
    //重力フラグ
    int m_grav;
    CImage m_img;


public:
    Enemy5(const CVector2D& pos, bool flip);
    void ToDeath();
    void TakeDamage(int damage);
    void Update();
    void Draw();
    void Collision(Base* b);


    static TexAnimData _anim_data[];


    //状態変数
    int m_state;
};