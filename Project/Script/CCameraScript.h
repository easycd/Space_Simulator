#pragma once
#include <Engine\CScript.h>
class CCameraScript
    : public CScript
{
private:
    float       m_fCamSpeed;

    Vec3        OffSet;


    //bool SetOff;

    //CPlayerScript* PlayerScript;
    Vec3 vFront;
    Vec3 vUp;
    Vec3 vRight;

    Vec2 PrevMousePos;
    Vector3 CameraPos;
    CGameObject* Muzzle;
    CGameObject* m_Target;

public:
    virtual void begin() override;
    virtual void tick() override;

    void SetTarget(CGameObject* target) { m_Target = target; }
    void SetMuzzle(CGameObject* muzzle) { Muzzle = muzzle; }
    //void SetOffset(Vec3(Off)) { Offset = Off; }
    //void SetPlayerScript(CPlayerScript ps) { PlayerScript = ps; }

    Vec3 GetvFront() { return vFront; }
    Vec3 GetvUp() { return vUp; }
    Vec3 GetvRight() { return vRight; }

private:
    void Camera3DMove();

    CLONE(CCameraScript);
public:
    CCameraScript();
    ~CCameraScript();
};
