#pragma once

// ウェーブカウント
enum WaveCount {
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven
};

// カメラクラスの前方宣言
class Camera;

/* ウェーブの基底クラス */
class IWave {

public:

	// コンストラクタとデストラクタ
	IWave() {};
	~IWave() {};

	// 初期化処理 更新処理 描画処理 終了処理
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw2DB(Camera* camera) = 0;
	virtual void Draw3D(Camera* camera) = 0;
	virtual void Draw2DF(Camera* camera) = 0;
	virtual void Exit() = 0;

	// ウェーブ変更処理
	virtual void ChangeWave(int nextWaveCount) = 0;
};