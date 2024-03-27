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
	camera_->rotate = { 0.0f, 0.0f, 0.0f };
	camera_->translate = { 0.0f, 0.0f, -15.0f };


	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Initialize();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Initialize();


	/* ----- Sprite スプライト ----- */
	GamePlaySpriteTexHD_ = TextureManager::LoadTexture("GamePlay.png");
	GamePlaySprite_ = make_unique<Sprite>();
	GamePlaySprite_->Initialize({ 512, 256 });
	GamePlaySpriteWt_.Initialize();
	GamePlaySpriteWt_.translate.y = 500;
	

	/* ----- Photon 光子 ----- */
	photon_ = make_unique<Photon>();
	photon_->Initialize();

	/* ----- Push ボタン押下スプライト ----- */
	pushSpriteTexHD_ = TextureManager::LoadTexture("PushA.png");
	pushSprite_ = make_unique<Sprite>();
	pushSprite_->Initialize({ 512, 256 });
	pushSpriteWt_.Initialize();

	/* ----- Manual マニュアルスプライト ----- */
	manualSpriteTexHD_ = TextureManager::LoadTexture("Manual.png");
	manualSprite_ = make_unique<Sprite>();
	manualSprite_->Initialize({ 512, 256 });
	manualSpriteWt_.Initialize();
	manualSpriteWt_.translate = { 700.0f, 550.0f, 0.0f };
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
	pushSpriteWt_.UpdateMatrix();
	manualSpriteWt_.UpdateMatrix();


	/* ----- Photon 光子 ----- */
	photon_->Update();


	// WASDもしくは十字キーでカメラ移動
	if (KeysInput::PressKeys(DIK_UP)) {

		camera_->translate.y += 1.0f;
	}
	if (KeysInput::PressKeys(DIK_LEFT)) {

		camera_->translate.x -= 1.0f;
	}
	if (KeysInput::PressKeys(DIK_DOWN)) {

		camera_->translate.y -= 1.0f;
	}
	if (KeysInput::PressKeys(DIK_RIGHT)) {

		camera_->translate.x += 1.0f;
	}

	// ボタン押下でシーンチェンジ
	if (GamePadInput::TriggerButton(PadData::A) || KeysInput::TriggerKey(DIK_A)) {
		state->ChangeSceneState(new TitleScene());
	}
	

#ifdef _DEBUG

	/*ImGui::Begin("GameScene");
	
	ImGui::Text("");

	ImGui::Text("Camera");
	ImGui::DragFloat3("Rotate", &camera_->rotate.x, 0.01f);
	ImGui::DragFloat3("Translate", &camera_->translate.x, 0.01f);
	ImGui::Text("");

	ImGui::End();*/

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

	/* ----- Photon 光子 ----- */
	photon_->Draw(camera_.get());
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() {

	/* ----- Sprite スプライト ----- */
	GamePlaySprite_->Draw(GamePlaySpriteTexHD_, GamePlaySpriteWt_, camera_.get());
	pushSprite_->Draw(pushSpriteTexHD_, pushSpriteWt_, camera_.get());
	manualSprite_->Draw(manualSpriteTexHD_, manualSpriteWt_, camera_.get());
}
