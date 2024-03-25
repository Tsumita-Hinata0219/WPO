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
	camera_->rotate = { 0.2f, 0.0f, 0.0f };
	camera_->translate = { 0.0f, 10.0f, 0.0f };


	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Initialize();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Initialize();


	// スプライト
	GamePlaySpriteTexHD_ = TextureManager::LoadTexture("GamePlay.png");
	GamePlaySprite_ = make_unique<Sprite>();
	GamePlaySprite_->Initialize({ 512, 256 });
	GamePlaySpriteWt_.Initialize();
	GamePlaySpriteWt_.translate.y = 500;
}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update(GameManager* state) {

	/* ----- GameCamera ゲームカメラ----- */
	camera_->UpdateMatrix();


	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Update();


	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Update();


	/* ----- Sprite スプライト ----- */
	GamePlaySpriteWt_.UpdateMatrix();

	// ボタン押下でシーンチェンジ
	if (GamePadInput::PressButton(PadData::RIGHT)) {

		if (GamePadInput::TriggerButton(PadData::X)) {
			state->ChangeSceneState(new ClearScene());
		}
		if (GamePadInput::TriggerButton(PadData::Y)) {
			state->ChangeSceneState(new OverScene());
		}
	}

#ifdef _DEBUG

	ImGui::Begin("GameScene");
	
	ImGui::Text("");

	ImGui::Text("Camera");
	ImGui::DragFloat3("Rotate", &camera_->rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &camera_->translate.x, 0.01f);
	ImGui::Text("");

	ImGui::End();

#endif // _DEBUG
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

	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Draw(camera_.get());

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Draw(camera_.get());
	
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() {

	/* ----- Sprite スプライト ----- */
	GamePlaySprite_->Draw(GamePlaySpriteTexHD_, GamePlaySpriteWt_, camera_.get());
}
