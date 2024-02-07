#pragma once
#include <Engine\CScript.h>
#include "CCameraScript.h"

class CPlayerScript :
    public CScript
{
private:
    CCameraScript* CameraScript;
    bool ClearLZ;
    bool ClearRZ;
    Vec3 PrevRot;
    Vec2 PrevMousePos;
    float       m_fSpeed;
    bool m_Booster;

    double PrevRotY;
    double PrevRotX;
 
    double RotXDiff;
    double RotYDiff;

    Vec3 OffSet;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetBooster(bool Booster) { m_Booster = Booster; }
    bool GetBooster() { return m_Booster; }

    double GetRotXDiff() { return RotXDiff; }
    double GetRotYDiff() { return RotYDiff; }

    CPlayerScript* GetPlayerScript() { return this; }
    void SetCameraScript(CCameraScript* CS) { CameraScript = CS; }
 
private:
    void Shoot();
    void Move();
    void Booster();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};

