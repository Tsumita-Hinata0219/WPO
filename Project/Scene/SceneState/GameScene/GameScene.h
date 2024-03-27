#pragma once

#include "IScene.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Skydome/Skydome.h"
#include "Ground/Ground.h"

#include "CollisionManager.h"

#include "Photon/Photon.h"


class GameScene : public IScene {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(GameManager* state) override;

	/// <summary>
	/// 背景スプライトの描画処理
	/// </summary>
	void BackSpriteDraw() override;

	/// <summary>
	/// ３Dオブジェクトの描画処理
	/// </summary>
	void ModelDraw() override;

	/// <summary>
	/// 前景スプライトの描画処理
	/// </summary>
	void FrontSpriteDraw() override;

private:

	// メインカメラ
	unique_ptr<Camera> camera_ = nullptr;


	// Game
	uint32_t GamePlaySpriteTexHD_;
	unique_ptr<Sprite> GamePlaySprite_ = nullptr;
	WorldTransform GamePlaySpriteWt_{};

	// Photon
	unique_ptr<Photon> photon_ = nullptr;

	// Push
	uint32_t pushSpriteTexHD_;
	unique_ptr<Sprite> pushSprite_ = nullptr;
	WorldTransform pushSpriteWt_{};

	// Manual
	uint32_t manualSpriteTexHD_;
	unique_ptr<Sprite> manualSprite_ = nullptr;
	WorldTransform manualSpriteWt_{};
};

