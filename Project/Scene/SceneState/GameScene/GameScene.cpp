#include "GameScene.h"



/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {

}


/// <summary>
/// 初期化処理
/// </summary>
void GameScene::Initialize() {

	/* ----- Camera カメラ ----- */
	camera_ = make_unique<Camera>();
	camera_->Initialize();
	camera_->rotate = { 0.3f, 0.0f, 0.0f };
	camera_->translate = { 0.0f, 25.0f, -72.0f };

}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) {

	/* ----- GameCamera ゲームカメラ----- */
	camera_->UpdateMatrix();

}


/// <summary>
/// 背景スプライトの描画処理
/// </summary>
void GameScene::BackSpriteDraw() {

}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw() {

	
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() {

	
}
