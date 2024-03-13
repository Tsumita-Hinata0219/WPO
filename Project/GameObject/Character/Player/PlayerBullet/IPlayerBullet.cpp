#include "IPlayerBullet.h"



// 寿命の処理
void IPlayerBullet::RemoveAfterLifetime()
{
	// 寿命の時間をデクリメント
	lifeTimer_--;

	// 0以下で死亡フラグを立てる
	if (lifeTimer_ <= 0) {
		isDead_ = true;
	}
}