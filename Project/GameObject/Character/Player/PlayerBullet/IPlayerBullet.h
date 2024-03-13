#pragma once

#include "GameObject.h"
#include "OBBCollider.h"


/* Playerの前方宣言 */
class Player;


enum PlayerBulletType {
	Normal,
	Penetration,
};

class IPlayerBullet {

public: // プレイヤーバレット基底クラス : メンバ関数

	// コンストラクタとデストラクタ
	IPlayerBullet() {};
	~IPlayerBullet() {};

	// 初期化処理　更新処理　描画処理
	virtual void Initialize(Player* player, Model& modeHD, Vector3 initPos, Vector3 vel) = 0;
	virtual void Update() = 0;
	virtual void Draw3D(Camera* camera) = 0;

#pragma region Get 取得

	// 死亡フラグの取得
	virtual bool isDead() = 0;

	// OBBコライダーの取得
	virtual OBBCollider* GetOBBCOllider() = 0;

#pragma endregion 

protected: // プレイヤーバレット基底クラス : メンバ変数

	// 寿命の処理
	void RemoveAfterLifetime();

protected:

	// 死亡フラグ
	bool isDead_ = false;

	// 寿命のタイマー
	int lifeTimer_ = 0;

	// Player
	Player* player_ = nullptr;

};

