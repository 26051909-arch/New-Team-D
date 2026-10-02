#include "Game.h" 
#include "Field.h" 
#include "Player.h" 
#include "UI.h"
#include "../Title/Title.h" // ゲームオーバー時にタイトルへ戻す場合

Game::Game() : Base(eType_Scene) {
	new Field(CVector2D(0, 0));
	new Player(CVector2D(256, 400), false);
	new UI();
}

void Game::Update() {
	if (!Base::FindObject(eType_Player)&&PUSH(CInput::eButton1)) {
		Base::KillAll();
		new Title();
	}
}