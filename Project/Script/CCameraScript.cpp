#include "pch.h"
#include "CCameraScript.h"

#include <Engine\CTransform.h>
#include <Engine\CCamera.h>

#include "CPlayerScript.h"

CCameraScript::CCameraScript()
	: CScript((UINT)SCRIPT_TYPE::CAMERASCRIPT)
	, vFront(Vec3(0.f,0.f,0.f))
	, vUp(Vec3(0.f, 0.f, 0.f))
	, vRight(Vec3(0.f,0.f,0.f))
	, m_Target(nullptr)
	, m_fCamSpeed(100.f)
	, BoosterState(false)
	, Offset(Vec3(0.f, 0.f, 0.f))
	, OffsetRot(Vec3(0.f,0.f,0.f))
	, CameraPos(Vec3(0.f,0.f,0.f))
	, PrevOffset(Vec3(0.f,0.f,0.f))
	, PrevMousePos(Vec2(0.f,0.f))
	//, SetOff(false)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::begin()
{
	CPlayerScript* PlayerScript = m_Target->GetScript<CPlayerScript>()->GetPlayerScript();
	PlayerScript->SetCameraScript(this);
	//if (m_Target != nullptr) {
	//	//CameraPos = GetOwner()->Transform()->GetRelativePos();
	//	Offset = GetOwner()->Transform()->GetRelativePos() - m_Target->Transform()->GetRelativePos();
	//	Offset.x += 40;
	//	Offset.y += 180;
	//	//Offset.z += 500;



	//	//CameraPos = m_Target->Transform()->GetRelativePos() + Offset;

	//	//Transform()->SetRelativePos(CameraPos);


	//	

	//	//OffsetRot = GetOwner()->Transform()->GetRelativeRot();
	//
	//	
	//	PrevOffset.z = Offset.z;
	//}
}


void CCameraScript::tick()
{
	//PrevMousePos = CKeyMgr::GetInst()->GetMousePos();
	// X 684
		Camera3DMove();
}

void CCameraScript::Camera3DMove() // 카메라 원점 기준에서 비행기 Trasform 100 -50 500 
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
	
	//m_Target->Transform()->SetRelativePos(Vec3(CameraPos.x , CameraPos.y , CameraPos.z));
	Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();

	float RotXDiff = PlayerScript->GetRotXDiff();
	float RotYDiff = PlayerScript->GetRotYDiff();

	//vRot.x += RotXDiff;
	//vRot.y += RotYDiff;
	//RotYDiff = 0;
	Transform()->SetRelativeRot(vRot);

	Offset = m_Target->Transform()->GetRelativePos() - GetOwner()->Transform()->GetRelativePos();
	//Transform()->SetRelativePos(Vec3();

	//vPos = TarGetPos;

	//CameraPos = TarGetPos + Offset;

	if (KEY_PRESSED(KEY::W))
	{
		vRot.x -= DT * 1.0f;
		vPos += DT * vUp * fSpeed;
		//TarGetPos += DT * vFront * fSpeed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vRot.x += DT * 1.0f;
		vPos -= DT * vUp * fSpeed;
		//TarGetPos -= DT * vFront * fSpeed;
		//m_Target->Transform()->SetRelativePos(TarGetPos);
	}

	if (KEY_PRESSED(KEY::A))
	{
		vRot.y -= DT * 1.0f;
		vPos -= DT * vRight * fSpeed;
		//TarGetPos -= DT * vRight * fSpeed;
		//m_Target->Transform()->SetRelativePos(TarGetPos);
	}

	if (KEY_PRESSED(KEY::D))
	{
		vRot.y += DT * 1.0f;
		vPos += DT * vRight * fSpeed;
		//TarGetPos += DT * vRight * fSpeed;
		//m_Target->Transform()->SetRelativePos(TarGetPos);
	}

	if (KEY_PRESSED(KEY::LSHIFT))
	{
		vPos += DT * vFront * fSpeed;
	}

	//if (MousePos.x - PrevMousePos.x >= 0 /*&& MousePos.x > 750 && MousePos.x < 1270*/)
	//{
	//	vRot.y += DT * 1.0f;
	//	
	//	//TarGetRot.y += 0.5f * DT;
	//	//m_Target->Transform()->SetRelativeRot(Vec3(TarGetRot.x, TarGetRot.y, TarGetRot.z));
	//}

	//if (MousePos.x - PrevMousePos.x <= 0 /*&& MousePos.x < 600 && MousePos.x > 0*/)
	//{
	//	vRot.y -= DT * 1.0f;
	//	
	//	//TarGetRot.y -= 0.5f * DT;
	//	//m_Target->Transform()->SetRelativeRot(Vec3(TarGetRot.x, TarGetRot.y, TarGetRot.z));
	//}

	//if (MousePos.y - PrevMousePos.y <= 0 && MousePos.y > 0 && MousePos.y < 800)
	//{
	//	vRot.x -= DT * 1.0f;
	//}
	//if (MousePos.y - PrevMousePos.y >= 0 && MousePos.y > 0 && MousePos.y < 800)
	//{
	//	vRot.x += DT * 1.0f;
	//}

	

	if (KEY_PRESSED(KEY::RBTN))
	{
		Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();
		vRot.y += DT * vMouseDir.x * 5.f;
		vRot.x -= DT * vMouseDir.y * 5.f;
		
	}




	//if (m_Target != nullptr)
	//{
	//	CPlayerScript* PlayerScript = m_Target->GetScript<CPlayerScript>()->GetPlayerScript();

	//	if (PlayerScript->GetBooster() /*&& BoosterState == false*/) // 부스터가 켜져있는상태
	//	{
	//		//BoosterState = true;
	//		//Offset = GetOwner()->Transform()->GetRelativePos() - m_Target->Transform()->GetRelativePos();
	//		//Offset.x += 40;
	//		//Offset.y += 180;
	//		//Offset.z -= 10.0 * DT;
	//		if(Offset.z <= -490 && Offset.z >= -530)
	//			Offset.z -= 70.0 * DT;
	//	}

	//	if (PlayerScript->GetBooster() == false /*&& BoosterState == true*/) // 부스터가 꺼져있는상태
	//	{
	//		//BoosterState = false;
	//		//Offset = GetOwner()->Transform()->GetRelativePos() - m_Target->Transform()->GetRelativePos();
	//		//Offset.x += 40;
	//		//Offset.y += 180;

	//		if(Offset.z < PrevOffset.z)
	//	     Offset.z += 60.0 * DT;
	//			
	//	}

	//	//float fSpeed = m_fCamSpeed;

	//	if (m_Target != nullptr) /*&& BoosterState == false*/
	//	{
	//		Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();
	//		Vec3 CameraPos = GetOwner()->Transform()->GetRelativePos();

	//		Vec3 TarGetRot = m_Target->Transform()->GetRelativeRot();
	//		Vec3 CameraRot = Transform()->GetRelativeRot();

	//		//float RotXDiff = PlayerScript->GetRotXDiff();
	//		//float RotYDiff = PlayerScript->GetRotYDiff();

	//		//CameraRot = TarGetRot * 0.05f;
	//		CameraPos = TarGetPos + Offset;
	//		//CameraRot.x += RotXDiff;
	//		//CameraRot.y += RotYDiff * 0.1f;
	//		

	//		//Transform()->SetRelativeRot(CameraRot);
	//		Transform()->SetRelativePos(CameraPos);
	//	}

	//	if (m_Target != nullptr && BoosterState)
	//	{
	//		Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();
	//		Vec3 CameraPos = GetOwner()->Transform()->GetRelativePos();

	//		Vec3 CameraRot = m_Target->Transform()->GetRelativeRot();
	//		Vec3 TarGetRot = m_Target->Transform()->GetRelativeRot();

	//		//CameraRot = TarGetRot * 0.05f;
	//		CameraPos = TarGetPos + Offset;

	//		Transform()->SetRelativePos(CameraPos);
	//	}

		PrevMousePos = CKeyMgr::GetInst()->GetMousePos();
		Transform()->SetRelativePos(vPos);
		Transform()->SetRelativeRot(vRot);
		//m_Target->Transform()->SetRelativePos(Vec3(vRight.x + 100, vUp.y - 50, vFront.z + 500));
	//}
}
