#pragma once
#include <Engine\CScript.h>

class CPlayerScript :
    public CScript
{
private:
    bool ClearLZ;
    bool ClearRZ;
    Vec3 PrevRot;
    Vec2 PrevMousePos;
    float       m_fSpeed;
    bool m_Booster;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetBooster(bool Booster) { m_Booster = Booster; }
    bool GetBooster() { return m_Booster; }

    CPlayerScript* GetPlayerScript() { return this; }

private:
    void Shoot();
    void Booster();

public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};

