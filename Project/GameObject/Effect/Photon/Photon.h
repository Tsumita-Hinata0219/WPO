#pragma once

#include "GameObject.h"

class Photon {

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(Camera* camera);

private:

	uint32_t particle1HD_;
	uint32_t particle2HD_;

	// Particle
	std::unique_ptr<Particle> particle1_ = nullptr;

	// パーティクルリスト
	std::list<ParticleProperties> particlePropes1_{};
	Emitter emitter1_{};
	Scope lifeTimeScope1_{};
	ScopeVec3 posScope1_{};
	ScopeVec3 velScope1_{};
	ScopeVec4 colorScope1_{};
	
	
	// Particle
	std::unique_ptr<Particle> particle2_ = nullptr;

	// パーティクルリスト
	std::list<ParticleProperties> particlePropes2_{};
	Emitter emitter2_{};
	Scope lifeTimeScope2_{};
	ScopeVec3 posScope2_{};
	ScopeVec3 velScope2_{};
	ScopeVec4 colorScope2_{};
};
