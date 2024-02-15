#pragma once
#include <Engine\CScript.h>
#include "CCameraScript.h"

class CPlayerScript :
    public CScript
{
private:
    CGameObject* Camera;
    CGameObject* Bullet;
    CGameObject* Enemy;
    CCameraScript* CameraScript;
    Vec2        PrevMousePos;
    float       m_fSpeed;
    bool        m_Booster;

    Vec3        OffSet;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetBooster(bool Booster) { m_Booster = Booster; }
    bool GetBooster() { return m_Booster; }

    CPlayerScript* GetPlayerScript() { return this; }
    void SetCameraScript(CCameraScript* CS) { CameraScript = CS; }
    CCameraScript* GetCameraScript() { return CameraScript; }

    void SetBullet(CGameObject* bullet) { Bullet = bullet; }

    void SetEnemy(CGameObject* enemy) { Enemy = enemy; }

private:
    void Shoot();
    void Move();
    void Booster();
    void CreateBullet();
   

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};