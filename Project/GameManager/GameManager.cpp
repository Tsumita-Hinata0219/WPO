#include "GameManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameManager::GameManager() {

	Tsumi::Initialize();
	Scene_ = new TitleScene();
	Scene_->Initialize();
}


/// <summary>
/// デストラクタ
/// </summary>
GameManager::~GameManager() {

	delete Scene_;
	Tsumi::Finalize();
}


/// <summary>
/// ゲームループ
/// </summary>
void GameManager::Run() {

	while (Tsumi::ProcessMessage() == 0) {

		Tsumi::BeginFlame();

		Scene_->Update(this);
		Scene_->BackSpriteDraw();
		Scene_->ModelDraw();
		Scene_->FrontSpriteDraw();

		Tsumi::EndFlame();
	}
}


/// <summary>
/// シーンチェンジ
/// </summary>
void GameManager::ChangeSceneState(IScene* newScene) {

	delete Scene_;
	Scene_ = newScene;
	Scene_->Initialize();
	return;
}