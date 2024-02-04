#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"


CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, PrevRot(Vec3(0.f,0.f,0.f))
	, PrevMousePos(Vec2(0.f,0.f))
	, m_fSpeed(100.f)
	, m_Booster(false)
	, ClearLZ(false)
	, ClearRZ(false)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Player Speed");
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::begin()
{
	PrevRot = Transform()->GetRelativeRot();
	//Vec2 PrevMousePos = CKeyMgr::GetInst()->GetMousePos();
	// 동적 재질 생성
	MeshRender()->GetDynamicMaterial(0);
}

void CPlayerScript::tick()
{
	Vec3 vCurPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRot();

	if (ClearRZ)
	{
		if (vRot.z < PrevRot.z)
			vRot.z += DT * 2.0f;
			
		if (vRot.z >= PrevRot.z)
			ClearRZ = false;
	}

	if (ClearLZ)
	{
		if (vRot.z > PrevRot.z)
			vRot.z -= DT * 2.0f;

		if (vRot.z <= PrevRot.z)
			ClearLZ = false;
	}

	if (KEY_PRESSED(KEY::W))
	{
		vCurPos.z += DT * m_fSpeed;
		//vPos += DT * vFront * fSpeed;

	}
	if (KEY_PRESSED(KEY::S))
	{
		vCurPos.z -= DT * m_fSpeed;
		//vPos += DT * vFront * fSpeed;

	}
	if (KEY_PRESSED(KEY::A))
	{
		//vCurPos.x -= DT * m_fSpeed;
		if (vRot.z < 0.25f)
			vRot.z += DT * 1.5f;
		
		//vRot.y += DT * 0.05f;
		//vRot.x -= DT * 0.05f;

		//vPos += DT * vFront * fSpeed;
	}

	if (KEY_RELEASE(KEY::A))
	{
		ClearLZ = true;
	}
	if (KEY_PRESSED(KEY::D))
	{
		//vCurPos.x += DT * m_fSpeed;
		if(vRot.z > -0.25f)
		vRot.z -= DT * 1.5f;
		//vPos += DT * vFront * fSpeed;
	}
	if (KEY_RELEASE(KEY::D))
	{
			ClearRZ = true;
	}
	if (KEY_PRESSED(KEY::LSHIFT))
	{
		if (KEY_PRESSED(KEY::W))
		{
			m_Booster = true;
			vCurPos.z += DT * m_fSpeed * 2.f;
			//vPos += DT * vFront * fSpeed;
		}
	}
	if (m_Booster)
	{
		if (KEY_RELEASE(KEY::LSHIFT))
			m_Booster = false;
	}

	//if (KEY_PRESSED(KEY::RBTN))
	//{
		//Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();
	     //Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		//vRot.y += DT * vMouseDir.x * 0.05f;
		//vRot.x -= DT * vMouseDir.y * 0.05f;
	//}

	if (KEY_PRESSED(KEY::Z))
	{
		Vec3 vRot = Transform()->GetRelativeRot();
		vRot.z += DT * XM_PI;
		Transform()->SetRelativeRot(vRot);
	}

	Transform()->SetRelativePos(vCurPos);			

	if (KEY_TAP(KEY::SPACE))
	{
		DrawDebugCircle(Transform()->GetWorldPos(), 500.f, Vec4(0.f, 0.f, 1.f, 1.f), Vec3(0.f, 0.f, 0.f), 2.f);

		Shoot();
	}	
	Transform()->SetRelativeRot(vRot);
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