#include "core/plasma_gun.h"

PlasmaGun::PlasmaGun( int32_t Id )
    : Weapon( Id )
{
    mScatter.mIncrease=12;
    mScatter.mChill=40;
    mScatter.mAltIncrease=20;

    mShootCooldown = 0.15;
    mShootAltCooldown = 0.35;

    mBulletsMax = 200.0;
    mShotCost=10;
    mShotCostAlt=30;
    mReloadTimeMax=0.2;
    mStaticReload=5;
    mBullets=mBulletsMax;
}