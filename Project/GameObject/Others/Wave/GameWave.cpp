#include "GameWave.h"



// 各ウェーブの初期化処理
void GameWave::Initialize()
{


}


// 各ウェーブの更新処理
void GameWave::Update()
{
	// フェーズチェック
	prevWave_ = currentWave_;
	currentWave_ = waveNum_;

	// ウェーブ変更チェック
	if (prevWave_ != currentWave_) {

		// 変更していたら初期化処理に入る
		Initialize();
	}

	// ウェーブ変更処理フラグが立っていたら終了処理に入ってウェーブ変更
	if (isWaveChange_) {
		Exit();
	}


#ifdef _DEBUG

	ImGui::Begin("GameWave");

	ImGui::Text("CurrentWave = %d", currentWave_);
	ImGui::Text(" PrevWave   = %d", prevWave_);


	ImGui::End();

#endif // _DEBUG
}


// 各ウェーブの描画処理
void GameWave::Draw2DB(Camera* camera)
{
	// 背景スプライト

}

void GameWave::Draw3D(Camera* camera)
{
	// 3Dモデル

}

void GameWave::Draw2DF(Camera* camera)
{
	// 前景スプライト


}


// 各ウェーブの終了処理
void GameWave::Exit()
{


	ChangeWave(1);
}


// ウェーブんの変更処理
void GameWave::ChangeWave(int nextWaveCount)
{
	// ウェーブナンバーの設定
	// この引数でウェーブチェックをしている
	waveNum_ = nextWaveCount;
}
