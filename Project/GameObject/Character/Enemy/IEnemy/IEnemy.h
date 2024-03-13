#pragma once
#include "MyMath.h"
#include "Model.h"
#include "Player/Player.h"
#include "Enemy/Bullet/EnemyBullet.h"
#include "OBBCollider.h"

enum EnemyType
{
    TRACE,
    BLAST,
    FIRE,
    MORTAR
};

class IEnemy {
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="player : プレイヤーのポインタ"></param>
    /// <param name="position : 初期位置"></param>
    /// <param name="level : レベル(これによってパラメーターが変化する)"></param>
    virtual void Initialize(Player* player, Vector3 position, int level) = 0;
    /// <summary>
    /// 更新処理
    /// </summary>
    virtual void Update() = 0;
    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="view"></param>
    virtual void Draw(Camera* camera) = 0;

    /// <summary>
    /// 敵のタイプを返す関数
    /// </summary>
    /// <returns></returns>
    int GetEnemyType() { return enemyType; }

    /// <summary>
    /// 敵のタイプをセットする関数
    /// </summary>
    /// <param name="num"></param>
    void SetEnemyType(int num) { enemyType = num; }

    virtual OBBCollider* GetOBBCollider() = 0;

protected:
    static int enemyType;
    //player
    Player* player_;
    //worldTransform
    WorldTransform worldTransform_;
    //速度
    Vector3 velocity_;
    //モデル
    Model model_;
    //生存しているかのフラグ
    bool isAlive_;
    //Enemyの持つ弾を可変長配列で管理
    //std::list<std::shared_ptr<EnemyBullet>> bullet_;
    //playerとの距離
    float distanceToPlayer_;

    /// <summary>
    /// 敵のパラメーター（レベルによって上下する値）
    /// </summary>
    /// <param name="hp : 体力"></param>
    /// <param name="power : 攻撃力"></param>
    /// <param name="speed : 速度"></param>
    struct Parameter
    {
        int hp;
        int power;
        float speed;
        float searchDistance;
    };
};

