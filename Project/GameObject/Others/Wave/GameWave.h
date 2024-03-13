#pragma once

#include "GameObject.h"
#include "IWave.h"


// ゲームオブジェクト
#include "Player/Player.h"



class GameWave : public IWave {

public:

	// コンストラクタとデストラクタ
	GameWave() {};
	~GameWave() {};

	// 初期化処理 更新処理 描画処理 終了処理
	void Initialize() override;
	void Update() override;
	void Draw2DB(Camera* camera) override;
	void Draw3D(Camera* camera) override;
	void Draw2DF(Camera* camera) override;
	void Exit() override;

	// ウェーブ変更処理
	void ChangeWave(int nextWaveCount) override;

#pragma region Get

	// 現在のウェーブの取得
	int GetCurrentWaveCount() { return this->currentWave_; }

	// ウェーブナンバーの取得
	int GetWaveNum() { return this->waveNum_; }

#pragma endregion 

#pragma region Set

	// 現在のウェーブの設定
	void SetCurrentWave(int wave) { this->currentWave_ = wave; }

	// 前のウェーブの設定
	void SetPrevWave(int wave) { this->prevWave_ = wave; }

	// ウェーブナンバーの設定
	void SetWaveNum(int wave) { this->waveNum_ = wave; }

#pragma endregion 

private:

	// 現在と一個前のウェーブ、ウェーブナンバー
	int currentWave_;
	int prevWave_;
	int waveNum_;

	// ウェーブ変更フラグ
	bool isWaveChange_;





private: // <! ゲームオブジェクトは以下に記述 メンバ関数

	/// <summary>
	/// プレイヤー関連の更新処理
	/// </summary>
	void PlayerUpdate();

	/// <summary>
	/// プレイヤーバレットリストの追加
	/// </summary>
	//void AddPlayerBullet(shared_ptr<PlayerBullet> playerBullet) { playerBullets_.push_back(playerBullet); }



private: // <! ゲームオブジェクトは以下に記述 メンバ変数


	/* ----- Player プレイヤー ----- */
	unique_ptr<Player> player_ = nullptr;
	//list<shared_ptr<PlayerBullet>> playerBullets_{};


};

