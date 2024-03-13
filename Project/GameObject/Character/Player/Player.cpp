#include "Player.h"
#include "GameScene/GameScene.h"
#include "Enemy/IEnemy/IEnemy.h"


// 初期化処理
void Player::Initialize()
{
	// Bodyの初期化処理
	bodyModel_ = make_unique<Model>();
	bodyModel_->CreateFromObj("PlayerBody", "Player");
	bodyWt_.Initialize();

	// 移動速度
	velocity_ = Vector3::zero;
	moveVector_ = 0.3f;

	// Bulletの初期化処理
	bulletModel_ = make_unique<Model>();
	bulletModel_->CreateFromObj("PlayerBullet", "Player");
	bulletVelocity_ = 1.5f;
	AttackInterval_ = 10;
	AttackTimer_ = 1;

	// Reticleの初期化処理
	reticle_ = make_unique<PlayerReticle>();
	reticle_->Initialize();
	reticle_->SetParent(&bodyWt_);

	// 初期レベル
	levelPrope_ = HP;
	hpLv_ = LvOne;
	velLv_ = LvOne;
	attackLv_ = LvOne;;
	attackIntervalLv_ = LvOne;

	// ダッシュしているかのフラグ
	isDash_ = false;

	// ダッシュにかかるフレーム
	ASDashFrame_ = 20;

	// エネルギーの初期設定
	energy_ = 0;
	
	// Colliderのビットのセッティング
	SettingColliderBit();
}


// 更新処理
void Player::Update(Camera* camera)
{
	// ワールドトランスフォームの初期化
	bodyWt_.UpdateMatrix();

	// Reticleの更新処理
	reticle_->Update(camera);

	// 射撃処理
	IsAttack();

	// 移動処理
	Move();

	// 姿勢の処理
	CalcBodyRotate();

	// ダッシュの処理
	DashFunc();

	// レベルによる各種パラメーターの処理
	SetthingLevel();

	// レベル変更処理
	SettingLev();

	// OBBColliderのセッティング
	SettingCollider();

#ifdef _DEMO

#endif // DEMO



#ifdef _DEBUG

	if (ImGui::TreeNode("Player")) {

		ImGui::Text("Player_Manual");
		ImGui::Text("R_Stick : Move");
		ImGui::Text("L_Stick : Reticle");
		ImGui::Text("R_Shoulder : Attack");
		ImGui::Text("A_Button : Dash");
		ImGui::Text("");

		ImGui::Text("L_Shoulder_Keep and Up or Down : LevelPrope Change");
		ImGui::Text("L_Shoulder_Keep and A_Button : LevelUp");
		ImGui::Text("");
		ImGui::Text("Level Up kinou ga wakari zurakute sumimasen");
		ImGui::Text("L_Shoulder wo ositamama de ijiremasu");

		/*ImGui::Text("");
		ImGui::Text("WorldTransform");
		ImGui::DragFloat3("Scale", &bodyWt_.scale.x, 0.01f, 0.0f, 10.0f);
		ImGui::DragFloat3("Rotate", &bodyWt_.rotate.x, 0.01f);
		ImGui::DragFloat3("Translate", &bodyWt_.translate.x, 0.01f);*/

		ImGui::Text("");
		ImGui::Text("Energy = %d", energy_);

		ImGui::Text("");
		if (levelPrope_ == HP) {
			ImGui::Text("LevelPrope = HP");
		}
		else if (levelPrope_ == Vel) {
			ImGui::Text("LevelPrope = Vel");
		}
		else if (levelPrope_ == Attack) {
			ImGui::Text("LevelPrope = Attack");
		}
		else if (levelPrope_ == AttackInter) {
			ImGui::Text("LevelPrope = AttackInterval");
		}
		ImGui::Text(" HPLv = %d : val = %d", hpLv_, hp_);
		ImGui::Text("VelLv = %d : val = %.2f", velLv_, vel_);
		ImGui::Text("AttLv = %d : val = %d", attackLv_, attack_);
		ImGui::Text("AtILv = %d : val = %d", attackIntervalLv_, attackInterval_);

		ImGui::TreePop();
	}

#endif // _DEBUG
}


// 描画処理
void Player::Draw3D(Camera* camera)
{
	// Bodyの描画
	bodyModel_->Draw(bodyWt_, camera);

	// Reticleの初期化
	reticle_->Draw3D(camera);
}
void Player::Draw2DFront(Camera* camera)
{ 
	camera;
}


// 衝突判定
void Player::OnCollision(uint32_t id)
{
	id;
}


// エネミーとの個別衝突判定
void Player::OnCollisionWithEnemy(IEnemy* enemy)
{
	enemy;
}


// Colliderのビットのセッティング
void Player::SettingColliderBit()
{
	OBBCollider::SetCollosionAttribute(ObjectAttribute::Player);
	OBBCollider::SetCollisionMask(ObjectMask::Player);
	OBBCollider::SetID(ObjectId::Player);
}


// OBBColliderのセッティング
void Player::SettingCollider()
{
	// OBBのサイズの設定
	this->size_ = 2.0f * bodyWt_.scale;
	OBBCollider::SetSize(this->size_);
	OBBCollider::SetRotate(bodyWt_.rotate);
}


// 移動処理
void Player::Move() {

	// velocityは0で毎フレーム初期化
	velocity_ = Vector3::zero;

	// キーの処理
	if (KeysInput::PressKeys(DIK_W)) 
	{
		velocity_.z = moveVector_;
	};
	if (KeysInput::PressKeys(DIK_A)) 
	{
		velocity_.x = -moveVector_;
	};
	if (KeysInput::PressKeys(DIK_S)) 
	{
		velocity_.z = -moveVector_;
	};
	if (KeysInput::PressKeys(DIK_D)) 
	{
		velocity_.x = moveVector_;
	};

	// パッドの処理
	if (GamePadInput::GetLStick().x <= -0.3f) 
	{
		velocity_.x = -1.0f;
	}
	if (GamePadInput::GetLStick().x >= 0.3f)
	{
		velocity_.x = 1.0f;
	}
	if (GamePadInput::GetLStick().y <= -0.3f)
	{
		velocity_.z = -1.0f;
	}
	if (GamePadInput::GetLStick().y >= 0.3f)
	{
		velocity_.z = 1.0f;
	}

	// 正規化
	if (velocity_.x != 0.0f || velocity_.z != 0.0f) {
		float length = Length({ velocity_.x, velocity_.z });
		velocity_.x /= length;
		velocity_.z /= length;
	} 

	// velocityに速度を掛けて座標に加算
	bodyWt_.translate += (velocity_ * moveVector_);
}


// プレイヤー本体の姿勢処理
void Player::CalcBodyRotate()
{
	Vector2 addRotate{};

	if (GamePadInput::GetLStick().x <= -0.3f || 
		GamePadInput::GetLStick().x >= 0.3f)
	{
		addRotate.x = bodyWt_.translate.x + GamePadInput::GetLStick().x;
	}

	if (GamePadInput::GetLStick().y <= -0.3f ||
		GamePadInput::GetLStick().y >= 0.3f)
	{
		addRotate.y = bodyWt_.translate.z + GamePadInput::GetLStick().y;
	}

	// Y軸周り角度(θy)
	bodyWt_.rotate.y = std::atan2(addRotate.x, addRotate.y);

	ImGui::Begin("rotate");
	ImGui::DragFloat2("pos", &addRotate.x, 0.0f);
	ImGui::End();


}


// ダッシュの処理
void Player::DashFunc()
{
	// ダッシュ先のベクトル取得
	if (GamePadInput::TriggerButton(PadData::A)) {
		Log("Button_A\n");

		// ボタン押下時にフラグが立っていなかったら
		if (!isDash_) {

			// フラグを立てる
			isDash_ = true;

			// 移動先の座標の計算
			toDashPosition_ = bodyWt_.translate;
			toDashPosition_.z += 5.0f;

			// ダッシュ処理開始時の座標
			toInitDashPosition_ = bodyWt_.GetWorldPos();

			// ダッシュのフレームを０に設定
			nowDashFrame_ = 0;
		}
	}


	// ダッシュのフラグがたったら
	if (isDash_) {

		// ダッシュのフレームをインクリメン
		nowDashFrame_++;

		// 今のフレームを終了フレームで割る
		float dashTime = float(nowDashFrame_) / float (ASDashFrame_);

		// イージングで座標に加算
		bodyWt_.translate.z = toDashPosition_.z + (toDashPosition_.z - toInitDashPosition_.z) * Ease::OutExpo(dashTime);


		// 終了したらフラグを折る
		if (nowDashFrame_ == ASDashFrame_) {

			isDash_ = false;
			nowDashFrame_ = 0;
		}
	}

}


// レベルによる処理
void Player::SetthingLevel()
{
	// HP
	if (hpLv_ == LvOne) {
		hp_ = 10;
	}
	else if (hpLv_ == LvTwo) {
		hp_ = 20;
	}
	else if (hpLv_ == LvThree) {
		hp_ = 30;
	}
	else if (hpLv_ == LvFour) {
		hp_ = 40;
	}
	else if (hpLv_ == LvFive) {
		hp_ = 50;
	}

	//Vel
	if (velLv_ == LvOne) {
		vel_ = 0.2f;
	}
	else if (velLv_ == LvTwo) {
		vel_ = 0.25f;
	}
	else if (velLv_ == LvThree) {
		vel_ = 0.3f;
	}
	else if (velLv_ == LvFour) {
		vel_ = 0.35f;
	}
	else if (velLv_ == LvFive) {
		vel_ = 0.4f;
	}
	moveVector_ = vel_;

	// Attack
	if (attackLv_ == LvOne) {
		attack_ = 10;
	}
	else if (attackLv_ == LvTwo) {
		attack_ = 10;
	}
	else if (attackLv_ == LvThree) {
		attack_ = 10;
	}
	else if (attackLv_ == LvFour) {
		attack_ = 10;
	}
	else if (attackLv_ == LvFive) {
		attack_ = 10;
	}

	// AttackInterval
	if (attackIntervalLv_ == LvOne) {
		attackInterval_ = 20;
	}
	else if (attackIntervalLv_ == LvTwo) {
		attackInterval_ = 17;
	}
	else if (attackIntervalLv_ == LvThree) {
		attackInterval_ = 13;
	}
	else if (attackIntervalLv_ == LvFour) {
		attackInterval_ = 10;
	}
	else if (attackIntervalLv_ == LvFive) {
		attackInterval_ = 7;
	}
	AttackInterval_ = attackInterval_;
}


// レベルの変更処理
void Player::SettingLev()
{
	if (GamePadInput::PressButton(PadData::LEFT_SHOULDER)) {

		if (GamePadInput::TriggerButton(PadData::UP)) {
			levelPrope_ = levelPrope_ + 1;
		}
		if (GamePadInput::TriggerButton(PadData::DOWN)) {
			levelPrope_ = levelPrope_ - 1;
		}

		if (levelPrope_ > 3) {
			levelPrope_ = 0;
		}
		if (levelPrope_ < 0) {
			levelPrope_ = 3;
		}

		if (GamePadInput::TriggerButton(PadData::A)) {

			if (levelPrope_ == HP) {
				hpLv_ = hpLv_ + 1;
			}
			else if (levelPrope_ == Vel) {
				velLv_ = velLv_ + 1;
			}
			else if (levelPrope_ == Attack) {
				attackLv_ = attackLv_ + 1;
			}
			else if (levelPrope_ == AttackInter) {
				attackIntervalLv_ = attackIntervalLv_ + 1;
			}
		}
	}
}


// 射撃処理
void Player::IsAttack()
{
	// キー押下でタイマーを減らし射撃
	if (KeysInput::PressKeys(DIK_SPACE)) {

		// 射撃タイマーを減らす
		AttackTimer_--;

		// 0以下になったら射撃
		if (AttackTimer_ <= 0) {
			
			// 設定し直す
			AttackTimer_ = AttackInterval_;
			// バレットの設定をして射撃
			SettingNewBullet();
		}
	}
	else if (KeysInput::ReleaseKeys(DIK_SPACE)) {
		
		// キーを離したら次の瞬間押してすぐ射撃できるように
		// １フレームを入れておく
		AttackTimer_ = 1;
	}

	// ボタン押下でタイマーを減らし射撃
	if (GamePadInput::PressButton(PadData::RIGHT_SHOULDER)) {

		// 射撃タイマーを減らす
		AttackTimer_--;

		// 0以下になったら射撃
		if (AttackTimer_ <= 0) {

			// 設定し直す
			AttackTimer_ = AttackInterval_;
			// バレットの設定をして射撃
			SettingNewBullet();
		}
	}
	else if (GamePadInput::ReleaseButton(PadData::RIGHT_SHOULDER)) {

		// キーを離したら次の瞬間押してすぐ射撃できるように
		// １フレームを入れておく
		AttackTimer_ = 1;
	}
}


// バレットの設定
void Player::SettingNewBullet()
{
	// バレットのインスタンス作成
	shared_ptr<IPlayerBullet> newbullet = make_unique<PenetrationBullet>();

	// 初期座標
	Vector3 initPos = bodyWt_.GetWorldPos();
	// 移動速度
	Vector3 vel = CalcBulletDirection();

	// Bulletの初期化処理
	newbullet->Initialize(this, (*bulletModel_), initPos, vel);

	// シーンに登録
	registerScene_->AddPlayerBullets(newbullet);
}


// バレットの進行方向の計算
Vector3 Player::CalcBulletDirection()
{
	Vector3 ReticlePos = reticle_->GetWorldPos();
	Vector3 PlaToRet = Normalize(ReticlePos - bodyWt_.GetWorldPos());
	return PlaToRet * bulletVelocity_;
}
