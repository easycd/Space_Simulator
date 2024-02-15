#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"

class BulletScript :
    public CScript
{
private:
    CPlayerScript* PlayerScript;
    CGameObject* m_TargetObject;

public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    CLONE(BulletScript);
public:
    BulletScript();
    ~BulletScript();
};

