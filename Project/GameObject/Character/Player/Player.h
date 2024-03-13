#pragma once

#include "GameObject.h"
#include "PlayerReticle/PlayerReticle.h"
#include "PlayerBullet/IPlayerBullet.h"
#include "PlayerBullet/NormalBullet/NormalBullet.h"
#include "PlayerBullet/PenetrationBullet/PenetrationBullet.h"

#include "OBBCollider.h"


enum LevelNum {
	LvZero,
	LvOne,
	LvTwo,
	LvThree,
	LvFour,
	LvFive,
};

enum LevelPrope {
	HP,
	Vel,
	Attack,
	AttackInter,
};

/* GameSceneの前方宣言 */
class GameScene;

/* Enemyの前方宣言 */
class IEnemy;

/* Playerクラス */
class Player : public OBBCollider {

public: // プレイヤー本体 : メンバ関数

	// コンストラクタとデストラクタ
	Player() {};
	~Player() {};

	// 初期化処理　更新処理　描画処理
	void Initialize();
	void Update(Camera* camera);
	void Draw3D(Camera* camera);
	void Draw2DFront(Camera* camera);

#pragma region Get 取得

	// ワールド座標の取得
	Vector3 GetWorldPos() { return this->bodyWt_.GetWorldPos(); }

#pragma endregion

#pragma region Set 設定

	// エネルギーの設定
	void AddEnergy(int add) { this->energy_ += add; }

#pragma endregion

#pragma region Collider 衝突判定

	// 衝突判定
	void OnCollision(uint32_t id) override;

	// エネミーとの個別衝突判定
	void OnCollisionWithEnemy(IEnemy* enemy);

	// コライダーのゲッター
	Vector3 GetOBBWorldPos() override { return bodyWt_.GetWorldPos(); }
	Vector3 GetSize() override { return this->size_; }
	Vector3 GetRotate() override { return this->bodyWt_.rotate; }

#pragma endregion 

private:

	// Colliderのビットのセッティング
	void SettingColliderBit();

	// OBBColliderのセッティング
	void SettingCollider();

	// 移動処理
	void Move();

	// プレイヤー本体の姿勢処理
	void CalcBodyRotate();

	// ダッシュの処理
	void DashFunc();

	// レベルによる各種パラメーターの処理
	void SetthingLevel();

	// レベルの変更処理
	void SettingLev();

private: // プレイヤー本体 : メンバ変数

	// 本体
	unique_ptr<Model> bodyModel_ = nullptr;
	WorldTransform bodyWt_{};

	// 移動速度
	Vector3 velocity_{};
	float moveVector_;

	// サイズ
	Vector3 size_{};

	// 移動先のベクトル
	Vector2 moveV_{};

	// LevelPrope
	int levelPrope_;

	// HP
	int hp_;
	int hpLv_;

	// Vel
	float vel_;
	int velLv_;

	// Attack
	int attack_;
	int attackLv_;

	// AttackInterval
	int attackInterval_;
	int attackIntervalLv_;

	// ダッシュしているかのフラグ
	bool isDash_;
	
	// ダッシュ先の座標
	Vector3 toDashPosition_{};
	Vector3 toInitDashPosition_{};

	// ダッシュに必要なフレーム
	int ASDashFrame_;

	// ダッシュにかかってるフレーム
	int nowDashFrame_;

	// エネルギー
	int energy_;


public: // バレット : メンバ関数

#pragma region Set 設定

	// バレットの登録先のシーン
	void SetGameScene(GameScene* scene) { this->registerScene_ = scene; }

	// 射撃のインターバルの設定
	void SetAttackInterval(uint32_t newInterval) { this->AttackTimer_ = newInterval; }

#pragma endregion

private:

	// 射撃処理
	void IsAttack();

	// バレットの設定
	void SettingNewBullet();

	// バレットの進行方向の計算
	Vector3 CalcBulletDirection();

private: // バレット : メンバ変数

	// Bullet
	unique_ptr<Model> bulletModel_ = nullptr;

	// バレットの速度
	float bulletVelocity_;

	// 射撃のインターバル
	int AttackInterval_;
	int AttackTimer_;



private: // レティクル : メンバ変数

	// Reticle
	unique_ptr<PlayerReticle> reticle_ = nullptr;



private: // シーン : メンバ変数

	// 登録先シーン
	GameScene* registerScene_ = nullptr;

};

