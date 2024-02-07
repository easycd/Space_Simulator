#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"
#include "CCameraScript.h"


CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, PrevRot(Vec3(0.f,0.f,0.f))
	, PrevRotX(0.f)
	, PrevRotY(0.f)
	, RotXDiff(0.f)
	, RotYDiff(0.f)
	, PrevMousePos(Vec2(0.f,0.f))
	, m_fSpeed(100.f)
	, m_Booster(false)
	, ClearLZ(false)
	, ClearRZ(false)
	, OffSet(Vec3(0.f,0.f,0.f))
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Player Speed");
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::begin()
{
	OffSet = Vec3(0.f, 0.f, -500.f);

	PrevRot = Transform()->GetRelativeRot();
	// 동적 재질 생성
	MeshRender()->GetDynamicMaterial(0);
}

void CPlayerScript::tick()
{
	//PrevMousePos = CKeyMgr::GetInst()->GetMousePos();

	Move();
}

void CPlayerScript::Shoot()
{
	// 미사일 프리팹 참조
	Ptr<CPrefab> pMissilePrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"MissilePrefab");
	Vec3 vMissilePos = Transform()->GetRelativePos() + Vec3(0.f, 0.5f, 0.f) * Transform()->GetRelativeScale();
	CGameObject* pCloneMissile = pMissilePrefab->Instantiate();

	// 레벨에 추가
	SpawnGameObject(pCloneMissile, vMissilePos, L"PlayerProjectile");
}

void CPlayerScript::Move()
{
	Vec3 vCurPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRot();
	Vec2 MousePos = CKeyMgr::GetInst()->GetMousePos(); //Y = 426

	//Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	//Vec3 vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
	//Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);


	//if (MousePos.x - PrevMousePos.x > 0 && MousePos.x > 750 && MousePos.x < 1270) //화면 중앙에서 오른쪽 
	//{
	//	vRot.y += DT * 0.5f;
	//	RotYDiff = vRot.y - PrevRotY; // 카메라에 넘겨줄 Diff값 = 현재 회전 값 - 전 프레임 회전 값

	//}
	//if (MousePos.x - PrevMousePos.x < 0 && MousePos.x < 600 && MousePos.x > 0)
	//{
	//	//if (vRot.y > 3.0)
	//		vRot.y -= DT * 0.5f;
	//		RotYDiff = vRot.y - PrevRotY;
	//}

	//if (MousePos.y - PrevMousePos.y > 0)
	//{
	//	vRot.x -= DT * 0.5f;
	//	RotXDiff = vRot.x - PrevRotX;
	//}
	//if (MousePos.y - PrevMousePos.y < 0)
	//{
	//	vRot.x += DT * 0.5f;
	//	RotXDiff = vRot.x - PrevRotX;
	//}

	if (KEY_PRESSED(KEY::W))
	{
		//if (CameraScript != nullptr)
		//{
		//	//Vec3 vFront = CameraScript->GetvFront();
		////vCurPos += DT * vFront * m_fSpeed;
		//CameraScript->GetOwner()->Transform()->SetRelativePos(vCurPos.x + 40, vCurPos.y + 180, vCurPos.z - 500);
		//}
	}


	if (KEY_PRESSED(KEY::S))
	{
		//vCurPos.z -= DT * m_fSpeed;
	}
	if (KEY_PRESSED(KEY::A))
	{

			//vRot.y -= DT * 0.2f;
		   //RotYDiff = vRot.y - PrevRotY;
			//if (CameraScript != nullptr)
			//{
			//	Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();
			//	CameraRot.y -= DT * 0.5f;
			//	CameraScript->GetOwner()->Transform()->SetRelativeRot(CameraRot);
			//	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
			//	CameraScript->GetOwner()->Transform()->SetRelativePos(vCurPos.x, vCurPos.y, vCurPos.z - 500);
			//}




		//vCurPos.x -= DT * m_fSpeed;
		//if (vRot.z < 0.25f)
		//	vRot.z += DT * 1.5f;

		//vRot.y += DT * 0.05f;
		//vRot.x -= DT * 0.05f;

		//vPos += DT * vFront * fSpeed;
	}

	//if (KEY_RELEASE(KEY::A))
	//{
	//	ClearLZ = true;
	//}
	if (KEY_PRESSED(KEY::D))
	{



			//vRot.y += DT * 0.2f;
         	//RotYDiff = vRot.y - PrevRotY; // 카메라에 넘겨줄 Diff값 = 현재 회전 값 - 전 프레임 회전 값 
			//if (CameraScript != nullptr)
			//{
			//	Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();
			//	CameraRot.y += DT * 1.0f;
			//	CameraScript->GetOwner()->Transform()->SetRelativeRot(CameraRot);
			//	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
			//	CameraScript->GetOwner()->Transform()->SetRelativePos(vCurPos.x + 40, vCurPos.y + 180, vCurPos.z - 500);
			//}
			// 
			// 
			// 
			// 
		//vCurPos.x += DT * m_fSpeed;
		//if(vRot.z > -0.25f)
		//vRot.z -= DT * 1.5f;
		//vPos += DT * vFront * fSpeed;
	}
	//if (KEY_RELEASE(KEY::D))
	//{
	//	ClearRZ = true;
	//}
	//if (KEY_PRESSED(KEY::LSHIFT))
	//{
	//	if (KEY_PRESSED(KEY::W))
	//	{
	//		m_Booster = true;
	//		vCurPos.z+= DT * m_fSpeed * 2.f;
	//	}
	//}
	//if (m_Booster)
	//{
	//	if (KEY_RELEASE(KEY::LSHIFT))
	//		m_Booster = false;
	//}
	Transform()->SetRelativeRot(vRot);
	Transform()->SetRelativePos(vCurPos);
	PrevRotX = Transform()->GetRelativeRot().x;
	PrevRotY = Transform()->GetRelativeRot().y;
	PrevMousePos = CKeyMgr::GetInst()->GetMousePos();
}

void CPlayerScript::Booster()
{
}

void CPlayerScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* pOtherObject = _Other->GetOwner();

	if (pOtherObject->GetName() == L"Monster")
	{
		DestroyObject(pOtherObject);		
	}
}







void CPlayerScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
}