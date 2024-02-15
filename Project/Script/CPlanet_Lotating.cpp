#include "pch.h"
#include "CPlanet_Lotating.h"
#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>
#include <math.h>

CPlanet_Lotating::CPlanet_Lotating()
	:CScript((UINT)SCRIPT_TYPE::PLANET_LOTATING)
	, m_Rot(0.f, 0.0f, 0.0f)
{
}

CPlanet_Lotating::~CPlanet_Lotating()
{
}

void CPlanet_Lotating::begin()
{
}

void CPlanet_Lotating::tick()
{
	Vec3 Rot = Transform()->GetRelativeRot();

	Rot.y += DT * m_Rot.y;

	Transform()->SetRelativeRot(Rot);
}
