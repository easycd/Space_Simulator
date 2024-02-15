#include "pch.h"
#include "CCameraScript.h"

#include <Engine\CTransform.h>
#include <Engine\CCamera.h>

#include "CPlayerScript.h"

CCameraScript::CCameraScript()
	: CScript((UINT)SCRIPT_TYPE::CAMERASCRIPT)
	, vFront(Vec3(0.f, 0.f, 0.f))
	, vUp(Vec3(0.f, 0.f, 0.f))
	, vRight(Vec3(0.f, 0.f, 0.f))
	, m_Target(nullptr)
	, m_fCamSpeed(100.f)
	, CameraPos(Vec3(0.f, 0.f, 0.f))
	, PrevMousePos(Vec2(0.f, 0.f))
	, OffSet(Vec3(0.f, 0.f, 0.f))

{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::begin()
{
	//Vec3 vPos = Transform()->GetRelativePos();
	
	//Transform()->SetMainCamera(this->GetOwner());
	Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();
	OffSet = Vec3(0.f,0.f,-500.f);
	//CameraPos = TarGetPos - CameraPos;
	//Transform()->SetRelativePos(CameraPos);

	CPlayerScript* PlayerScript = m_Target->GetScript<CPlayerScript>()->GetPlayerScript();
	PlayerScript->SetCameraScript(this);

	//Vec3 MuzzlePos = Muzzle->Transform()->GetRelativePos();
	//MuzzlePos = Transform()->GetRelativePos() + OffSet;

	
}


void CCameraScript::tick()
{
	Camera3DMove();
}

void CCameraScript::Camera3DMove()
{
	CPlayerScript* PlayerScript = m_Target->GetScript<CPlayerScript>()->GetPlayerScript();

	float fSpeed = m_fCamSpeed;
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRot();

	vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
	vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);
	Vec2 MousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 TarGetRot = m_Target->Transform()->GetRelativeRot();
	Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();


	if (KEY_PRESSED(KEY::W))
	{
		vRot.x -= DT * 0.7f;
		vPos += DT * vUp * fSpeed;
		if (TarGetRot.x <= XM_PI / 2.1f)
		{
			TarGetRot.x += DT * 0.2f;
			m_Target->Transform()->SetRelativeRot(TarGetRot);
		}
	}

	if (KEY_PRESSED(KEY::S))
	{
		vRot.x += DT * 0.7f;
		vPos -= DT * vUp * fSpeed;
		if (TarGetRot.x >= XM_PI / 2.3f)
		{
			TarGetRot.x -= DT * 0.2f;
			m_Target->Transform()->SetRelativeRot(TarGetRot);
		}
	}

	if (KEY_PRESSED(KEY::A))
	{
		vRot.z += DT * 1.0f;
		vPos -= DT * vRight * fSpeed;
		if (TarGetRot.z <= XM_PI / 20.f)
		{
			TarGetRot.z += DT * 0.3f;
			m_Target->Transform()->SetRelativeRot(TarGetRot);
		}
	}

	if (KEY_PRESSED(KEY::D))
	{
		vRot.z -= DT * 1.0f;
		vPos += DT * vRight * fSpeed;

		if (TarGetRot.z >= -(XM_PI / 20.f))
		{
			TarGetRot.z -= DT * 0.3f;
			m_Target->Transform()->SetRelativeRot(TarGetRot);
		}
	}


	if (KEY_PRESSED(KEY::LSHIFT))
	{
		vPos += DT * vFront * fSpeed;
	}

	if (KEY_PRESSED(KEY::RBTN))
	{
		Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();
		vRot.y += DT * vMouseDir.x * 5.f;
		vRot.x -= DT * vMouseDir.y * 5.f;
	}




	if (m_Target != nullptr)
	{
		if (PlayerScript->GetBooster()) // 부스터가 켜져있는상태
		{
			vPos += DT * vFront * fSpeed * 2;

			if (TarGetPos.z <= 550.f)
			{

				TarGetPos.z += 50.f * DT;
				m_Target->Transform()->SetRelativePos(TarGetPos);
			}
		}

		if (PlayerScript->GetBooster() == false) // 부스터가 꺼져있는상태

			if (TarGetPos.z >= 500.f && TarGetPos.z <= 551.f)
			{
				TarGetPos.z -= DT * 50.f;
				m_Target->Transform()->SetRelativePos(TarGetPos);
			}
	}
	PrevMousePos = MousePos;
	Transform()->SetRelativePos(vPos);
	m_Target->Transform()->SetRelativePos(TarGetPos);
	Transform()->SetRelativeRot(vRot);

}
