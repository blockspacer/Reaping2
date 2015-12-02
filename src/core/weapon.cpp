#include "platform/i_platform.h"
#include "core/weapon.h"
#include "core/i_position_component.h"
#include "core/i_move_component.h"
#include "core/scene.h"

Weapon::Weapon( int32_t Id )
    : Item( Id )
    , mActorFactory(ActorFactory::Get())
    , mCooldown( 0.0 )
    , mShootCooldown( 1.0 )
    , mShootAltCooldown( 1.0 )
    , mScatter( 0 )
    , mShoot(false)
    , mShootAlt(false)
    , mBullets(0.0)
    , mBulletsMax(10.0)
    , mShotCost(1)
    , mShotCostAlt(1)
    , mReloadTime(0.0)
    , mReloadTimeMax(2.0)
    , mStaticReload(0.0)
{
    mType = ItemType::Weapon;
}

bool Weapon::IsShoot() const
{
    return mShoot&&mBullets>=mShotCost;
}

void Weapon::SetShoot(bool shoot)
{
    mShoot = shoot;
}

bool Weapon::IsShootAlt() const
{
    return mShootAlt&&mBullets>=mShotCostAlt;
}

void Weapon::SetShootAlt(bool shoot)
{
    mShootAlt = shoot;
}

double Weapon::GetCooldown() const
{
    return mCooldown;
}

void Weapon::SetCooldown(double cooldown)
{
    mCooldown = cooldown;
}

double Weapon::GetShootCooldown() const
{
    return mShootCooldown;
}

void Weapon::SetShootCooldown(double cooldown)
{
    mShootCooldown = cooldown;
}

double Weapon::GetShootAltCooldown() const
{
    return mShootAltCooldown;
}

void Weapon::SetShootAltCooldown(double cooldown)
{
    mShootAltCooldown = cooldown;
}

Scatter& Weapon::GetScatter()
{
    return mScatter;
}

void Weapon::SetBullets(double bullets)
{
    mBullets=bullets;
}

double Weapon::GetBullets()const
{
    return mBullets;
}

void Weapon::SetBulletsMax(double bulletsMax)
{
    mBulletsMax=bulletsMax;
}

double Weapon::GetBulletsMax()const
{
    return mBulletsMax;
}

void Weapon::SetShotCost(int32_t shotCost)
{
    mShotCost=shotCost;
}

int32_t Weapon::GetShotCost()const
{
    return mShotCost;
}

void Weapon::SetShotCostAlt(int32_t shotCostAlt)
{
    mShotCostAlt=shotCostAlt;
}

int32_t Weapon::GetShotCostAlt()const
{
    return mShotCostAlt;
}

void Weapon::SetReloadTime(double reloadTime)
{
    mReloadTime=reloadTime;
}

double Weapon::GetReloadTime()const
{
    return mReloadTime;
}

void Weapon::SetReloadTimeMax(double reloadTimeMax)
{
    mReloadTimeMax=reloadTimeMax;
}

double Weapon::GetReloadTimeMax()const
{
    return mReloadTimeMax;
}

void Weapon::SetStaticReload(double staticReload)
{
    mStaticReload=staticReload;
}

double Weapon::GetStaticReload()const
{
    return mStaticReload;
}



Scatter::Scatter(double increase/*=0.0*/,double altIncrease/*=0.0*/, double chill/*=0.0*/, double magicNumber/*=100*/)
    :mCurrent(0.0)
    ,mIncrease(increase)
    ,mAltIncrease(altIncrease)
    ,mChill(chill)
    ,mMagicNumber(magicNumber)
{

}

void Scatter::Update(double DeltaTime)
{
    //want to chill the scatter on a linear way
    // e.g. magic=100, current=100, calculated=1/2, 
    // newCalc=50-chill*dt; 
    // chill=20, dt=1.0; // lets say 1 sec with 20 chill means newCalc is 20
    double newCalculated=(GetCalculated()*mMagicNumber-mChill*DeltaTime)/mMagicNumber; 
    newCalculated=std::max(0.0,newCalculated);
    L1("newCalc: %f calc: %f \n",newCalculated,mCurrent);
    if(newCalculated!=0.0)
    {
        mCurrent=(newCalculated*mMagicNumber)/(1-newCalculated); //inverse of GetCalculated
    }
    L1("newCurrent: %f \n",mCurrent);
}

void Scatter::Shot(bool alt)
{
    mCurrent+=alt?mAltIncrease:mIncrease;
}

double Scatter::GetCalculated()
{
    return mCurrent/(mMagicNumber+mCurrent);
}
