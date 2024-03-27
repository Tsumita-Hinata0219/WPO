#include "Photon.h"


// 初期化処理
void Photon::Initialize()
{
	particle1HD_ = TextureManager::LoadTexture("Particle1.png");
	particle2HD_ = TextureManager::LoadTexture("Particle2.png");

	particle1_ = make_unique<Particle>();
	particle2_ = make_unique<Particle>();

	emitter1_.worldTransform.Initialize();
	emitter1_.worldTransform.translate.x = 16.0f;
	emitter1_.count = 30;
	emitter1_.frequency = 1.0f * 60.0f;
	emitter1_.frequencyTime = 0;

	lifeTimeScope1_ = {
		.min = 3,
		.max = 5,
	};
	posScope1_ = {
		.X = {0.0f, 0.0f},
		.Y = {-4.0f, 4.0f},
		.Z = {0.0f, 0.0f},
	};
	velScope1_ = {
		.X = {-7.0f, -5.0f},
		.Y = {0.0f, 0.0f},
		.Z = {0.0f, 0.0f},
	};
	colorScope1_ = {
		.X = {0.0f, 256.0f},
		.Y = {0.0f, 256.0f},
		.Z = {0.0f, 256.0f},
		.W = {256.0f, 256.0f},
	};
	particle1_->Initialize(new ParticlePlane(), emitter1_.count);




	emitter2_.worldTransform.Initialize();
	emitter2_.worldTransform.translate.x = -16.0f;
	emitter2_.count = 30;
	emitter2_.frequency = 1.0f * 60.0f;
	emitter2_.frequencyTime = 0;

	lifeTimeScope2_ = {
		.min = 3,
		.max = 5,
	};
	posScope2_ = {
		.X = {0.0f, 0.0f},
		.Y = {-4.0f, 4.0f},
		.Z = {0.0f, 0.0f},
	};
	velScope2_ = {
		.X = {-7.0f, -5.0f},
		.Y = {0.0f, 0.0f},
		.Z = {0.0f, 0.0f},
	};
	colorScope2_ = {
		.X = {0.0f, 256.0f},
		.Y = {0.0f, 256.0f},
		.Z = {0.0f, 256.0f},
		.W = {256.0f, 256.0f},
	};
	particle2_->Initialize(new ParticlePlane(), emitter2_.count);
}


// 更新処理
void Photon::Update()
{
	emitter1_.frequencyTime += 1.0f;

	if (emitter1_.frequencyTime >= emitter1_.frequency) {
		emitter1_.frequencyTime = 0.0f;
		particle1_->Emit(emitter1_, lifeTimeScope1_, posScope1_, velScope1_, colorScope1_);
	}

	particlePropes1_ = particle1_->RetrieveFront();
	for (ParticleProperties& prope : particlePropes1_) {

		// 速度を座標に加算
		prope.worldTransform.translate += prope.velocity;

		// 寿命の処理
		prope.currentTime++;

		// alphaの処理
		float alpha = 1.0f - (float(prope.currentTime) / float(prope.lifeTime));
		prope.color.w = alpha;

		if (prope.currentTime >= prope.lifeTime) {
			continue;
		}

		particle1_->PushBackList(prope);
	}


	//emitter2_.frequencyTime += 1.0f;

	//if (emitter2_.frequencyTime >= emitter2_.frequency) {
	//	emitter2_.frequencyTime = 0.0f;
	//	particle2_->Emit(emitter2_, lifeTimeScope2_, posScope2_, velScope2_, colorScope2_);
	//}

	//particlePropes2_ = particle2_->RetrieveFront();
	//for (ParticleProperties& prope : particlePropes2_) {

	//	// 速度を座標に加算
	//	prope.worldTransform.translate -= prope.velocity;

	//	// 寿命の処理
	//	prope.currentTime++;

	//	// alphaの処理
	//	float alpha = 1.0f - (float(prope.currentTime) / float(prope.lifeTime));
	//	prope.color.w = alpha;

	//	if (prope.currentTime >= prope.lifeTime) {
	//		continue;
	//	}

	//	particle2_->PushBackList(prope);
	//}
}


// 描画処理
void Photon::Draw(Camera* camera)
{
	particle1_->Draw(particle1HD_, camera);
	//particle2_->Draw(particle2HD_, camera);
}
