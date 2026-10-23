#include"Enemy5.h"
#include "Player.h"
#include"Effect.h"
#include"Slash.h"
#include"Field.h"
#include "HP.h"


Enemy5::Enemy5(const CVector2D & pos, bool flip) : Base(eType_Enemy5)
{
    m_img = COPY_RESOURCE("Enemy5", CImage);


    m_pos = pos;
    /*m_rad = 40;
    m_img.SetSize(256, 256);
    m_img.SetCenter(128, 226);*/
    m_rad = 40;
    m_img.SetSize(280, 280);
    m_img.SetCenter(140, 200);




    m_hp = 110.0f;


    //反転フラグ
    m_flip = flip;
    //通常状態へ
    m_state = eState_Idle;
    //着地フラグ
    m_is_ground = true;
    m_is_attacked = false;
    //重力フラグ
    m_grav = true;


    m_death_timer = 0;

    m_attack_timer = 0;
    m_slash_count = 0;


    m_img.ChangeAnimation(eAnimIdle, true);
}


void Enemy5::ToDeath()
{
    if (m_state != eState_Death) {
        m_state = eState_Death;
        //m_grav = true;
        new Effect(m_pos);
        m_img.ChangeAnimation(eAnimDeath); // アニメーションを繭に切り替え
    }
    
}


void Enemy5::TakeDamage(int damage) {


    //HP減少　　下限0
    m_hp = max(m_hp - damage, 0);
    if (m_hp <= 0) {
        ToDeath();
    }
    else{
        m_state = eState_Damage;
        m_img.ChangeAnimation(eAnimIdle, false);
        float knockback_x = 12.0f;    // 後ろに吹き飛ぶ強さ
        float knockback_y = -8.0f;    // 上に少し跳ね上がる強さ（マイナスが上方向）


        if (m_flip == true) {
            // プレイヤーが左を向いていたなら、右へ吹き飛ばす
            m_vec.x = knockback_x;
        }
        else {
            // プレイヤーが右を向いていたなら、左へ吹き飛ばす
            m_vec.x = -knockback_x;
        }
        // 上方向に跳ね上がらせる
        m_vec.y = knockback_y;
        m_is_ground = false; // 空中に浮くため接地フラグをOFFにする
    }
}


void Enemy5::StateIdle()
{
    const float move_speed = 5;
    const float slash_range = 625.0f;

    Base* player = Base::FindObject(eType_Player);

    if (player != nullptr) {
        float dist_x = fabsf(player->m_pos.x - m_pos.x);
        float dist_y = fabsf(player->m_pos.y - m_pos.y);

        if (dist_x <= slash_range && dist_y <= 100.0f) {
            // プレイヤーの方向を向く
            m_flip = (player->m_pos.x < m_pos.x);

            // 直接攻撃状態へ
            m_attack_timer = 0;
            m_slash_count = 0;
            m_state = eState_Attack;

            return;
        }
    }

    // 通常移動
    if (m_flip == false) {
        m_pos.x += move_speed;
        if (m_pos.x > SCREEN_WIDTH + 380) {
            SetKill();
        }
    }
    else {
        m_pos.x -= move_speed;
        if (m_pos.x < -380) {
            SetKill();
        }
    }


}


void Enemy5::StateDamage() {
    m_vec.x *= 0.5f;
    if (m_is_ground) {
        m_vec.x = 0;
        m_state = eState_Idle;
        //m_img.ChangeAnimation(eAnimIdle, true);
    }
}


void Enemy5::StateAttack() {
    m_attack_timer++;

    // 15フレームごとにSlashを発射
    if (m_attack_timer >= 15) {
        m_attack_timer = 0;

        CVector2D slash_pos = m_pos;

        // Enemy5はデフォルトで右向き
        float houkou = m_flip ? 2.0f : 1.0f;

        Slash* slash = new Slash(slash_pos, houkou);
        slash->m_dir = m_flip ? -1 : 1;

        m_slash_count++;

        // 3発撃ち終わったらクールタイムへ
        if (m_slash_count >= 2) {
            m_attack_timer = 0;
            m_state = eState_Cooldown;

            // 待機アニメーションへ
            m_img.ChangeAnimation(eAnimIdle, true);
        }
    }
}


void Enemy5::StateDeath()
{
    m_death_timer++; // 毎フレーム1ずつ増やす


    //8秒経過したら消滅
    if (m_death_timer >= 480) {
        SetKill();
    }
}



void Enemy5::StateCooldown()
{
    m_attack_timer++;

    // 120フレーム = 約2秒
    if (m_attack_timer >= 120) {
        m_attack_timer = 0;
        m_state = eState_Idle;

        m_img.ChangeAnimation(eAnimIdle, true);
    }
}


void Enemy5::Update()
{
    m_pos_old = m_pos;




    switch (m_state) {
        //通常状態
    case eState_Idle:
        StateIdle();
        break;


    case eState_Attack:
        StateAttack();
        break;




    case eState_Damage:
        StateDamage();
        break;


        //ダウン状態
    case eState_Death:
        StateDeath();
        break;


    case eState_Cooldown:
        StateCooldown();
        break;


    }


    
if (m_is_ground && m_vec.y > GRAVITY * 4)
    m_is_ground = false;
    
//重力による落下処理
m_vec.y += GRAVITY;
m_pos += m_vec;
    


    //アニメーションの更新
    m_img.UpdateAnimation();
}




void Enemy5::Draw()
{
    m_img.SetPos(m_pos);


    m_img.SetFlipH(m_flip);
    m_img.Draw();


}


void Enemy5::Collision(Base* b)
{
    switch (b->m_type) {
    case eType_Field:
        //Feild型へキャスト、型変換できたら
        if (Field* f = dynamic_cast <Field*>(b)) {
            //地面より下にいったら
            if (m_pos.y > f->GetGroundY()) {
                //地面の高さに戻す
                m_pos.y = f->GetGroundY();
                //落下速度リセット
                m_vec.y = 0;
                //接地フラグON
                m_is_ground = true;
            }
        }
        break;
    }
}




static TexAnim _idle[] = {
    {0,3},
    {1,3},
    {2,3},
    {3,3},
};


static TexAnim _attack[] = {
    {4,4},
    {5,4},
    {6,4},
    {7,4},
};


static TexAnim _death[] = {
    {8,3},


};




TexAnimData Enemy5::_anim_data[] = {
    ANIMDATA(_idle),
    ANIMDATA(_attack),
    ANIMDATA(_death),
};