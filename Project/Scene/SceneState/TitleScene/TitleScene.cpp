#include "TitleScene.h"



// 初期化処理
void TitleScene::Initialize()
{
	// メインカメラ
	camera_ = make_unique<Camera>();
	camera_->Initialize();

	// スプライト
	titleSpriteTexHD_ = TextureManager::LoadTexture("TitleSprite.png");
	titleSprite_ = make_unique<Sprite>();
	titleSprite_->Initialize({ 1280, 720 });
	titleSpriteWt_.Initialize();
}


// 更新処理
void TitleScene::Update(GameManager* state)
{
	/* ----- GameCamera ゲームカメラ ----- */
	camera_->UpdateMatrix();

	/* ----- Sprite スプライト ----- */
	titleSpriteWt_.UpdateMatrix();


	// ボタン押下でシーンチェンジ
	if (GamePadInput::TriggerButton(PadData::A)) {
		state->ChangeSceneState(new GameScene());
	}
	if (KeysInput::TriggerKey(DIK_SPACE)) {
		state->ChangeSceneState(new GameScene());
	}

#ifdef _DEBUG

	ImGui::Begin("TitleScene");
	ImGui::End();

#endif // _DEBUG
}


// 背景スプライトの描画処理
void TitleScene::BackSpriteDraw()
{

}


// ３Dオブジェクトの描画処理
void TitleScene::ModelDraw()
{
	
}


// 前景スプライトの描画処理
void TitleScene::FrontSpriteDraw()
{
	/* ----- Sprite スプライト ----- */
	titleSprite_->Draw(titleSpriteTexHD_, titleSpriteWt_, camera_.get());
}
