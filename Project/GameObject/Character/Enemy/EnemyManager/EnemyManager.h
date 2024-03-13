#pragma once
#include <sstream>
#include "Player/Player.h"
#include "GameObject.h"
#include "Enemy/Trace/Trace.h"
#include "Enemy/Blast/Blast.h"
#include "Enemy/IEnemy/IEnemy.h"

class GameScene;

#define MAX_ENEMY 20

class EnemyManager
{
public:
	EnemyManager();

	~EnemyManager();

	void LoadEnemyPopData();

	void UpdateEnemyPopCommands(Player* player,int level);

	void EnemySpawn(Player* player, int level);

	void Update();

	void Draw(Camera* camera);

	std::vector<IEnemy*> GetEnemy() { return enemies_; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }
private:
	Vector3 CalculateNextPosition(const Vector3& position, float radius);
private:
	// 敵発生コマンド
	std::stringstream popCommands;

	int flame_;

	int traceMax_;

	int blastMax_;

	float rad_;

	Vector3 tmpPos_;

	std::vector<IEnemy*> enemies_;

	//IEnemy* enemyArr_[4];

	//std::vector<std::unique_ptr<Trace>> trace_;
	//std::vector<std::unique_ptr<Blast>> blast_;

	GameScene* gameScene_;
};

