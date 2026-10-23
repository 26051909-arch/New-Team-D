#include"Player.h"
#include"Enemy1.h"
#include"Enemy2.h"
#include"Enemy3.h"
#include"Enemy4.h"
#include"Enemy5.h"
#include"Enemy6.h"
#include"SpiderBullet.h"
#include"BigBullet.h"
#include"Effect2.h"
#include"Slash.h"
#include"Field.h"
#include "Result/Result.h"








Player::Player(const CVector2D& pos, bool flip) : Base(eType_Player) 
{
    m_img = COPY_RESOURCE("Player", CImage);
    //座標設定
    m_pos_old = m_pos = pos;
    //サイズ設定
    m_img.SetSize(160, 160);
    //中心位置設定
    m_img.SetCenter(80, 155);


    //体力の初期化(最大500)
    m_hp = 200.0f;
    //反転フラグ
    m_flip = flip;
    //通常状態へ
    m_state = eState_Idle;
    //着地フラグ
    m_is_ground = true;

    //捕食数
    m_eat_count = 0;

    m_img.ChangeAnimation(eAnimIdle);
}




void Player::StateIdle()
{
    //移動量
    const float move_speed = 8;
    //移動フラグ
    bool move_flag = false;
    //ジャンプ力
    const float jump_pow = 12;


    //右移動
    if (HOLD(CInput::eRight)) {
        //移動量を設定
        m_pos.x += move_speed;
        //反転フラグ
        m_flip = true;
        move_flag = true;
    }


    //左移動
    if (HOLD(CInput::eLeft)) {
        //移動量を設定
        m_pos.x += -move_speed;
        //反転フラグ
        m_flip = false;
        move_flag = true;
    }




    //弾の発射(左右)
    if (PUSH(CInput::eMouseL)) {
        if (m_flip == false) {
            //左へ
            CVector2D bulletPos;


            bulletPos.x = m_pos.x - 30;    //プレイヤーの左端
            bulletPos.y = m_pos.y - 20;        //プレイヤーの胸辺り


            SpiderBullet* b = new SpiderBullet(bulletPos, 2);
            b->m_dir = -1;
        }
        else {
            //右へ
            CVector2D bulletPos;


            bulletPos.x = m_pos.x + 30;    //プレイヤーの右端
            bulletPos.y = m_pos.y - 20;        //プレイヤーの胸辺り


            SpiderBullet* b = new SpiderBullet(bulletPos, 2);
            b->m_dir = 1;
        }
    }


    //弾の発射(上)
    if (PUSH(CInput::eMouseR)) {
        CVector2D bulletPos;


        bulletPos.x = m_pos.x;    //プレイヤーの頭
        bulletPos.y = m_pos.y;// - 155 + 48;    //プレイヤーの頭


        SpiderBullet* b = new SpiderBullet(bulletPos, 3);
    }




    //ジャンプ
    if (m_is_ground && PUSH(CInput::eButton5)) {
        m_vec.y = -jump_pow;
        m_is_ground = false;
    }


    //ジャンプ中なら
    if (!m_is_ground) {
        if (m_vec.y < 0) {
            //上昇アニメ―ション
            m_img.ChangeAnimation(eAnimJumpUp, false);
        }
        else {
            //下降アニメーション
            m_img.ChangeAnimation(eAnimJumpDown, false);
        }
    }


    //地面にいるなら
    else
    {
        if (move_flag) {
                //走るアニメーション
                m_img.ChangeAnimation(eAnimRun, true);
                
        }
        else {
                //待機アニメーション
                m_img.ChangeAnimation(eAnimIdle, true);
        }
    }




}


void Player::StateDamage()
{
    //空気抵抗や地面との摩擦のイメージで、徐々に横移動の速度を落とす
    m_vec.x *= 0.5f;


    if (m_img.CheckAnimationEnd()) {
        m_vec.x = 0; //通常状態に戻る時に横の移動速度を完全にリセット
        m_state = eState_Idle;
        m_img.ChangeAnimation(eAnimIdle, true);
    }
}


void Player::StateDeath()
{
    m_img.ChangeAnimation(eAnimDeath, false);
    if (m_img.CheckAnimationEnd()) {
        SetKill();
    }
}






void Player:: Update()
{
    m_pos_old = m_pos;




    //一秒につき１０ずつ体力が下がる
    if (m_state != eState_Death) {
        m_hp -= (5.0f / 60.0f);


        if (m_hp <= 0.0f) {
            m_hp = 0.0f;
            m_state = eState_Death;
        }
    }




    switch (m_state) {
        //通常状態
    case eState_Idle:
        StateIdle();
        break;


        //ダメージ状態
    case eState_Damage:
        StateDamage();
        break;


        //ダウン状態
    case eState_Death:
        StateDeath();
        break;
    }


    //落ちていたら落下中状態へ移行
    if (m_is_ground && m_vec.y > GRAVITY * 4)
        m_is_ground = false;




    //重力による落下処理
    m_vec.y += GRAVITY;
    m_pos += m_vec;






    //アニメーションの更新
    m_img.UpdateAnimation();
}






void Player::Draw()
{
    m_img.SetPos(m_pos);


    m_img.SetFlipH(m_flip);


    m_img.Draw();




}








void Player::Collision(Base* b)
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




    case eType_Enemy1:
        if (Base::CollisionCircle(this, b)) {
            b->SetKill();
            //体力を15回復
            m_hp += 15.0f;

            m_eat_count++;

            //HPが最大値500を超えないように制限
            if (m_hp > 500.0f) {
                m_hp = 500.0f;
            }
        }
        break;




    case eType_Enemy2:
        if (Base::CollisionCircle(this, b)) {
            if (Enemy2* enemy2 = dynamic_cast<Enemy2*>(b)) {
                //敵2の状態が「死亡状態（繭）」のときだけ中を実行する
                if (enemy2->m_state == Enemy2::eState_Death) {
                    enemy2->SetKill();


                    // 体力を25回復
                    m_hp += 25.0f;

                    m_eat_count++;

                    // HPが最大値500を超えないように制限
                    if (m_hp > 500.0f) {
                        m_hp = 500.0f;
                    }
                }
                else {


                    //敵が通常状態の際はプレイヤーがダメージを食らう
                    m_hp -= 2.0f;
                    m_state = eState_Damage;
                    m_img.ChangeAnimation(eAnimDamage, false);


                    // ノックバック処理
                    float knockback_x = 13.0f;  // 後ろに吹き飛ぶ強さ
                    float knockback_y = -10.0f; // 上に少し跳ね上がる強さ（マイナスが上方向）


                    if (m_flip == true) {
                        // プレイヤーが右を向いていたなら、左（マイナス方向）へ吹き飛ばす
                        m_vec.x = -knockback_x;
                    }
                    else {
                        // プレイヤーが左を向いていたなら、右（プラス方向）へ吹き飛ばす
                        m_vec.x = knockback_x;
                    }
                    // 上方向に跳ね上がらせる
                    m_vec.y = knockback_y;
                    m_is_ground = false; // 空中に浮くため接地フラグをOFFにする
                }
            }
        }
        break;




    case eType_Enemy3:
        if (Base::CollisionCircle(this, b)) {
            if (Enemy3* enemy3 = dynamic_cast<Enemy3*>(b)) {
                //敵2の状態が「死亡状態（繭）」のときだけ中を実行する
                if (enemy3->m_state == Enemy3::eState_Death) {
                    enemy3->SetKill();


                    // 体力を35回復
                    m_hp += 35.0f;

                    m_eat_count++;


                    // HPが最大値500を超えないように制限
                    if (m_hp > 500.0f) {
                        m_hp = 500.0f;
                    }
                }
                else {


                    //敵が通常状態の際はプレイヤーがダメージを食らう
                    m_hp -= 6.0f;
                    m_state = eState_Damage;
                    m_img.ChangeAnimation(eAnimDamage, false);


                    // ノックバック処理
                    float knockback_x = 16.0f;  // 後ろに吹き飛ぶ強さ
                    float knockback_y = -13.0f; // 上に少し跳ね上がる強さ（マイナスが上方向）


                    if (m_flip == true) {
                        // プレイヤーが右を向いていたなら、左（マイナス方向）へ吹き飛ばす
                        m_vec.x = -knockback_x;
                    }
                    else {
                        // プレイヤーが左を向いていたなら、右（プラス方向）へ吹き飛ばす
                        m_vec.x = knockback_x;
                    }
                    // 上方向に跳ね上がらせる
                    m_vec.y = knockback_y;
                    m_is_ground = false; // 空中に浮くため接地フラグをOFFにする
                }
            }
        }
        break;




    case eType_Enemy4:
        if (Base::CollisionCircle(this, b)) {
            b->SetKill();
            //体力を45回復
            m_hp += 45.0f;

            m_eat_count++;


            //HPが最大値500を超えないように制限
            if (m_hp > 500.0f) {
                m_hp = 500.0f;
            }
        }
        break;




    case eType_Enemy5:
        if (Enemy5* enemy5 = dynamic_cast<Enemy5*>(b)) {
            if (Base::CollisionCircle(this, b)) {
                //敵5の状態が「死亡状態（繭）」のときだけ中を実行する
                if (enemy5->m_state == Enemy5::eState_Death) {
                    enemy5->SetKill();


                    // 体力を65回復
                    m_hp += 65.0f;

                    m_eat_count++;


                    // HPが最大値500を超えないように制限
                    if (m_hp > 500.0f) {
                        m_hp = 500.0f;
                    }
                }
                else if (enemy5->m_state == Enemy5::eState_Idle ||
                    enemy5->m_state == Enemy5::eState_Attack) {


                    //敵が通常状態の際はプレイヤーがダメージを食らう
                    m_hp -= 10.0f;
                    m_state = eState_Damage;
                    m_img.ChangeAnimation(eAnimDamage, false);


                    // ノックバック処理
                    float knockback_x = 18.0f;  // 後ろに吹き飛ぶ強さ
                    float knockback_y = -15.0f; // 上に少し跳ね上がる強さ（マイナスが上方向）


                    if (m_flip == true) {
                        // プレイヤーが右を向いていたなら、左（マイナス方向）へ吹き飛ばす
                        m_vec.x = -knockback_x;
                    }
                    else {
                        // プレイヤーが左を向いていたなら、右（プラス方向）へ吹き飛ばす
                        m_vec.x = knockback_x;
                    }
                    // 上方向に跳ね上がらせる
                    m_vec.y = knockback_y;
                    m_is_ground = false; // 空中に浮くため接地フラグをOFFにする
                }
            }
        }
        break;




    case eType_Enemy6:
        if (Base::CollisionCircle(this, b)) {
            
                    //敵が通常状態の際はプレイヤーがダメージを食らう
                    m_hp -= 6.0f;
                    m_state = eState_Damage;
                    m_img.ChangeAnimation(eAnimDamage, false);


                    // ノックバック処理
                    float knockback_x = 15.0f;  // 後ろに吹き飛ぶ強さ
                    float knockback_y = -13.0f; // 上に少し跳ね上がる強さ（マイナスが上方向）


                    if (m_flip == true) {
                        // プレイヤーが右を向いていたなら、左（マイナス方向）へ吹き飛ばす
                        m_vec.x = -knockback_x;
                    }
                    else {
                        // プレイヤーが左を向いていたなら、右（プラス方向）へ吹き飛ばす
                        m_vec.x = knockback_x;
                    }
                    // 上方向に跳ね上がらせる
                    m_vec.y = knockback_y;
                    m_is_ground = false; // 空中に浮くため接地フラグをOFFにする
            
        }
        break;






    case eType_Effect2:
        if (Effect2* effect = dynamic_cast<Effect2*>(b)) {
            if (effect->HitTest(m_pos, m_rad)) {


                // ダメージ
                m_hp -= 18.0f;


                if (m_hp < 0.0f) {
                    m_hp = 0.0f;
                }


                // ダメージアニメーション
                m_state = eState_Damage;
                m_img.ChangeAnimation(eAnimDamage, false);


                // ノックバック
                const float knockback_x = 14.0f;
                const float knockback_y = -13.0f;


                // 衝撃波がプレイヤーの左側なら右へ、
                // 右側なら左へ吹き飛ばす
                if (m_pos.x < effect->m_pos_left.x) {
                    m_vec.x = -knockback_x;
                }
                else if (m_pos.x > effect->m_pos_right.x) {
                    m_vec.x = knockback_x;
                }
                else {
                    // どちらか判断しにくい場合
                    m_vec.x = (m_pos.x < effect->m_pos.x)
                        ? -knockback_x : knockback_x;
                }


                m_vec.y = knockback_y;
                m_is_ground = false;
            }
        }
        break;

    
    case eType_Slash:
        if (Base::CollisionCircle(this, b)) {

            m_hp -= 9.0f;
            m_state = eState_Damage;
            m_img.ChangeAnimation(eAnimDamage, false);


            // ノックバック処理
            float knockback_x = 9.0f;  // 後ろに吹き飛ぶ強さ
            float knockback_y = -11.0f; // 上に少し跳ね上がる強さ（マイナスが上方向）


            if (m_flip == true) {
                // プレイヤーが右を向いていたなら、左（マイナス方向）へ吹き飛ばす
                m_vec.x = -knockback_x;
            }
            else {
                // プレイヤーが左を向いていたなら、右（プラス方向）へ吹き飛ばす
                m_vec.x = knockback_x;
            }
            // 上方向に跳ね上がらせる
            m_vec.y = knockback_y;
            m_is_ground = false; // 空中に浮くため接地フラグをOFFにする




        }
        break;


    case eType_BigBullet:
        if (Base::CollisionCircle(this, b)) {
            
            m_hp -= 13.0f;
            m_state = eState_Damage;
            m_img.ChangeAnimation(eAnimDamage, false);


            // ノックバック処理
            float knockback_x = 11.0f;  // 後ろに吹き飛ぶ強さ
            float knockback_y = -11.0f; // 上に少し跳ね上がる強さ（マイナスが上方向）


            if (m_flip == true) {
                // プレイヤーが右を向いていたなら、左（マイナス方向）へ吹き飛ばす
                m_vec.x = -knockback_x;
            }
            else {
                // プレイヤーが左を向いていたなら、右（プラス方向）へ吹き飛ばす
                m_vec.x = knockback_x;
            }
            // 上方向に跳ね上がらせる
            m_vec.y = knockback_y;
            m_is_ground = false; // 空中に浮くため接地フラグをOFFにする




        }
        break;




    }
}


static TexAnim _idle[] = {
    {0,4},
    {1,4},
    {2,4},
    {3,4},
    {4,4},
};


static TexAnim _run[] = {
    {10,4},
    {11,4},
    {12,4},
    {13,4},
    {14,4},
    //{15,4},
};


static TexAnim _jumpUp[] = {
    {18,2},
    {19,2},
    {20,2},
    {21,2},
    {22,2},
    //{23,2},
};


static TexAnim _jumpDown[] = {
    {23,2},
    {24,2},
    {25,2},
    {26,2},
    //{27,2},
};


static TexAnim _turisagari[] = {
    {20,4},
};


static TexAnim _shootweb[] = {
    {36,6},
    {37,6},
    {38,6},
    {39,6},
};


static TexAnim _damage[] = {
    {45,3},
    {46,3},
    {47,3},
};


static TexAnim _death[] = {
    {54,4},
    {55,4},
    {56,4},
    {57,4},
    {58,4},
    {59,4},
    {60,4},
    {61,4},
    {62,4},
};




TexAnimData Player::_anim_data[] = {
    ANIMDATA(_idle),
    ANIMDATA(_run),
    ANIMDATA(_jumpUp),
    ANIMDATA(_jumpDown),
    ANIMDATA(_turisagari),
    ANIMDATA(_shootweb),
    ANIMDATA(_damage),
    ANIMDATA(_death),
};