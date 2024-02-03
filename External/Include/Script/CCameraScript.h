#pragma once
#include <Engine\CScript.h>
class CCameraScript
     : public CScript
{
private:
    float       m_fCamSpeed;
    bool BoosterState;

    //bool SetOff;

    //CPlayerScript* PlayerScript;

    Vector3 PrevOffset;
    Vector3 Offset;
    CGameObject* m_Target;

public:
    virtual void begin() override;
    virtual void tick() override;

    void SetTarget(CGameObject* target) { m_Target = target; }
    //void SetOffset(Vec3(Off)) { Offset = Off; }
    //void SetPlayerScript(CPlayerScript ps) { PlayerScript = ps; }

private:
    void Camera3DMove();

    CLONE(CCameraScript);
public:
    CCameraScript();
    ~CCameraScript();
};


