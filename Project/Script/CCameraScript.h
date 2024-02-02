#pragma once
#include <Engine\CScript.h>
class CCameraScript
     : public CScript
{
private:
    float       m_fCamSpeed;
    CGameObject* m_Target;

public:
    virtual void begin() override;
    virtual void tick() override;

    void SetTarget(CGameObject* target) { m_Target = target; }

private:
    void Camera2DMove();
    void Camera3DMove();

    CLONE(CCameraScript);
public:
    CCameraScript();
    ~CCameraScript();
};


