#include "TitleScene.h"



// 初期化処理
void TitleScene::Initialize()
{
	// メインカメラ
	camera_ = make_unique<Camera>();
	camera_->Initialize();
}


// 更新処理
void TitleScene::Update(GameManager* state)
{
	/* ----- GameCamera ゲームカメラ ----- */
	camera_->UpdateMatrix();

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


}
