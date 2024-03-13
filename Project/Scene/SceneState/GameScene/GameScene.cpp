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


	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Initialize();

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Initialize();


	/* ----- Player プレイヤー ----- */
	player_ = make_unique<Player>();
	player_->Initialize();
	player_->SetGameScene(this);


	/* ----- CollisionManager コリジョンマネージャー ----- */
	collisionManager_ = make_unique<CollisionManager>();


	/* ----- GameWave ゲームウェーブ ----- */
	/*gameWave_ = make_unique<GameWave>();
	gameWave_->SetWaveNum(One);
	gameWave_->SetCurrentWave(One);
	gameWave_->SetPrevWave(One);
	gameWave_->Initialize();*/
	/* ----- Enemy 敵 ----- */
	enemyManager_.EnemySpawn(player_.get(),0);
	enemies_ = enemyManager_.GetEnemy();
	enemyManager_.SetGameScene(this);
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


	/* ----- Player プレイヤー ----- */
	PlayerUpdate();


	/* ----- Enemy 敵 ----- */
	//enemyManager_.Update();
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemies_[i]->Update();
	}


	/* ----- CollisionManager コリジョンマネージャー ----- */
	CheckAllCollision();

	/* ----- GameWave ゲームウェーブ ----- */
	//gameWave_->Update();

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
	ImGui::Text("Description of scene change");
	ImGui::Text("Scene change to 'ClearScene' by pressing X button while holding down Right.");
	ImGui::Text("Scene change to 'OverScene' by pressing Y button while holding down Right.");
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

	/* ----- GameWave ゲームウェーブ ----- */
	//gameWave_->Draw2DB(camera_.get());
}


/// <summary>
/// ３Dオブジェクトの描画処理
/// </summary>
void GameScene::ModelDraw() {

	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Draw(camera_.get());

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Draw(camera_.get());

	/* ----- Player プレイヤー ----- */
	player_->Draw3D(camera_.get());
	for (shared_ptr<IPlayerBullet> bullet : playerBullets_) {
		bullet->Draw3D(camera_.get());
	}

	/* ----- GameWave ゲームウェーブ ----- */
	//gameWave_->Draw3D(camera_.get());
	/* ----- Skydome 天球 ----- */
	Skydome::GetInstance()->Draw(camera_.get());

	/* ----- Ground 床 ----- */
	Ground::GetInstance()->Draw(camera_.get());

	/* ----- Enemy 敵 ----- */
	//enemyManager_.Draw(camera_.get());

	for (int i = 0; i < MAX_ENEMY; i++) {
		enemies_[i]->Draw(camera_.get());
	}
	
}


/// <summary>
/// 前景スプライトの描画処理
/// </summary>
void GameScene::FrontSpriteDraw() {

	//player_->Draw2DFront(camera_.get());

	/* ----- GameWave ゲームウェーブ ----- */
	//gameWave_->Draw2DF(camera_.get());
}


/// <summary>
/// ウェーブの初期化処理
/// </summary>
void GameScene::WaveInit()
{



}


/// <summary>
/// ウェーブの更新処理
/// </summary>
void GameScene::WaveUpdate()
{
	/* ----- GameCamera ゲームカメラ----- */
	camera_->UpdateMatrix();


	/* ----- Player プレイヤー ----- */
	PlayerUpdate();
}


/// <summary>
/// ウェーブの終了処理
/// </summary>
void GameScene::WaveExit()
{


}


// コライダーの衝突判定
void GameScene::CheckAllCollision()
{
	// プレイヤーとエネミーの個別処理
	for (int i = 0; i < MAX_ENEMY; ++i) {

		if (CollisionManager::CheckOBBxOBB(player_.get(), enemies_[i]->GetOBBCollider())) {
			
			player_->OnCollisionWithEnemy(enemies_[i]);
		}
	}


	// コライダーリストのクリア
	collisionManager_->ColliderClear();

	// コライダーリストの追加
	collisionManager_->AddOBBColliders(player_.get());
	for (shared_ptr<IPlayerBullet> bullet : playerBullets_) {
		collisionManager_->AddOBBColliders(bullet->GetOBBCOllider());
	}
	for (int i = 0; i < MAX_ENEMY; i++) {
		collisionManager_->AddOBBColliders(enemies_[i]->GetOBBCollider());
	}

	// コライダーの衝突判定
	collisionManager_->CheckAllCollision();
}


// プレイヤー関連の更新処理
void GameScene::PlayerUpdate()
{
	// プレイヤー本体
	player_->Update(camera_.get());

	// プレイヤーバレット
	for (shared_ptr<IPlayerBullet> bullet : playerBullets_) {
		bullet->Update();
	}
	playerBullets_.remove_if([](shared_ptr<IPlayerBullet> bullet) {
		if (bullet->isDead()) {
			bullet.reset();
			return true;
		}
		return false;
		}
	);

}

