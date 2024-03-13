#include "Ground.h"



// インスタンスの取得
Ground* Ground::GetInstance() 
{
	static Ground instance;
	return&instance;
}


// 初期化処理
void Ground::Initialize() 
{
	this->model_ = make_unique<Model>();
	this->model_->CreateFromObj("Ground");
	this->worldTransform_.Initialize();
	this->worldTransform_.scale = { 500.0f, 1.0f, 500.0f };
	this->worldTransform_.translate.y = -10.0f;
}


// 更新処理
void Ground::Update() 
{
	// ワールド座標の更新
	this->worldTransform_.UpdateMatrix();
}


// 描画処理
void Ground::Draw(Camera* camera) 
{
	this->model_->Draw(this->worldTransform_, camera);
}

