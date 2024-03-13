#pragma once

#include "IScene.h"
#include "GameManager.h"
#include "GameObject.h"

#include "Wave/GameWave.h"

#include "Player/Player.h"
#include "Player/PlayerBullet/IPlayerBullet.h"
#include "Player/PlayerBullet/NormalBullet/NormalBullet.h"

#include "Skydome/Skydome.h"
#include "Ground/Ground.h"

#include "CollisionManager.h"
#include "Enemy/Trace/Trace.h"
#include "Enemy/EnemyManager/EnemyManager.h"


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

	/// <summary>
	/// プレイヤーバレットリストの追加
	/// </summary>
	void AddPlayerBullets(shared_ptr<IPlayerBullet> bullet) { playerBullets_.push_back(bullet); }

	/// <summary>
	/// Enemyの追加
	/// </summary>
	/// <param name="IEnemy"></param>
	void AddEnemy(std::vector<IEnemy*> IEnemy) { enemies_; }
  
public:

	/// <summary>
	/// ウェーブの初期化処理
	/// </summary>
	void WaveInit();

	/// <summary>
	/// ウェーブの更新処理
	/// </summary>
	void WaveUpdate();

	/// <summary>
	/// ウェーブの終了処理
	/// </summary>
	void WaveExit();

private:

	/// <summary>
	/// コライダーの衝突判定
	/// </summary>
	void CheckAllCollision();

	/// <summary>
	/// プレイヤー関連の更新処理
	/// </summary>
	void PlayerUpdate();

private:

	// メインカメラ
	unique_ptr<Camera> camera_ = nullptr;

	/* ----- GameWave ゲームウェーブ ----- */
	unique_ptr<GameWave> gameWave_ = nullptr;


	/* ----- Player プレイヤー ----- */
	unique_ptr<Player> player_ = nullptr;
	list<shared_ptr<IPlayerBullet>> playerBullets_{};


	//std::vector<std::unique_ptr<Trace>> enemy_;
	EnemyManager enemyManager_;

	/* ----- CollisionManager コリジョンマネージャー ----- */
	unique_ptr<CollisionManager> collisionManager_ = nullptr;
	
	std::vector<IEnemy*> enemies_{};
};

