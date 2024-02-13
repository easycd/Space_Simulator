#pragma once
#include <Engine\CScript.h>

class CPlanet_Lotating : public CScript
{
public:
    CPlanet_Lotating();
    ~CPlanet_Lotating();

private:
    Vec3 m_Rot;

public:
    virtual void begin() override;
    virtual void tick() override;

public:
    virtual void SetRot(Vec3 _rot) { m_Rot = _rot; }

    CLONE(CPlanet_Lotating);
};

