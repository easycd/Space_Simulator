#include "pch.h"
#include "CCameraScript.h"

#include <Engine\CTransform.h>
#include <Engine\CCamera.h>

#include "CPlayerScript.h"

CCameraScript::CCameraScript()
	: CScript((UINT)SCRIPT_TYPE::CAMERASCRIPT)
	, m_Target(nullptr)
	, m_fCamSpeed(5.f)
	, BoosterState(false)
	, Offset(Vec3(0.f, 0.f, 0.f))
	, PrevOffset(Vec3(0.f,0.f,0.f))
	//, SetOff(false)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::begin()
{
	if (m_Target != nullptr) {
		Offset = GetOwner()->Transform()->GetRelativePos() - m_Target->Transform()->GetRelativePos();
		Offset.x += 40;
		Offset.y += 180;
		PrevOffset.z = Offset.z;
	}
}


void CCameraScript::tick()
{
	Vec2 MousePos = CKeyMgr::GetInst()->GetMousePos();
		Camera3DMove();
}

void CCameraScript::Camera3DMove()
{
	if (m_Target != nullptr)
	{
		CPlayerScript* PlayerScript = m_Target->GetScript<CPlayerScript>()->GetPlayerScript();

		if (PlayerScript->GetBooster() /*&& BoosterState == false*/) // 부스터가 켜져있는상태
		{
			//BoosterState = true;
			//Offset = GetOwner()->Transform()->GetRelativePos() - m_Target->Transform()->GetRelativePos();
			//Offset.x += 40;
			//Offset.y += 180;
			//Offset.z -= 10.0 * DT;
			if(Offset.z <= -490 && Offset.z >= -530)
				Offset.z -= 70.0 * DT;
		}

		if (PlayerScript->GetBooster() == false /*&& BoosterState == true*/) // 부스터가 꺼져있는상태
		{
			//BoosterState = false;
			//Offset = GetOwner()->Transform()->GetRelativePos() - m_Target->Transform()->GetRelativePos();
			//Offset.x += 40;
			//Offset.y += 180;

			if(Offset.z < PrevOffset.z)
		     Offset.z += 60.0 * DT;
				
		}

		Vec3 vPos = Transform()->GetRelativePos();
		Vec3 vRot = Transform()->GetRelativeRot();

		Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
		Vec3 vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
		Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);

		//float fSpeed = m_fCamSpeed;

		if (m_Target != nullptr) /*&& BoosterState == false*/
		{
			Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();
			Vec3 CameraPos = GetOwner()->Transform()->GetRelativePos();

			Vec3 CameraRot = m_Target->Transform()->GetRelativeRot();
			Vec3 TarGetRot = m_Target->Transform()->GetRelativeRot();

			//CameraRot = TarGetRot * 0.05f;
			CameraPos = TarGetPos + Offset;

			Transform()->SetRelativePos(CameraPos);
		}

		//if (m_Target != nullptr && BoosterState)
		//{
		//	Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();
		//	Vec3 CameraPos = GetOwner()->Transform()->GetRelativePos();

		//	Vec3 CameraRot = m_Target->Transform()->GetRelativeRot();
		//	Vec3 TarGetRot = m_Target->Transform()->GetRelativeRot();

		//	//CameraRot = TarGetRot * 0.05f;
		//	CameraPos = TarGetPos + Offset;

		//	Transform()->SetRelativePos(CameraPos);
		//}

	}
}
