#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"
#include "CCameraScript.h"
#include "BulletScript.h"


CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, PrevMousePos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_Booster(false)
	, OffSet(Vec3(0.f, 0.f, 0.f))
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Player Speed");
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::begin()
{
	Camera = GetCameraScript()->GetOwner();
	//Vec3 CameraPos = Camera->Transform()->GetRelativePos();
	//Transform()->SetRelativePos(CameraPos.x + 53.f, CameraPos.y - 170.f, CameraPos.z + 500);
	//OffSet = Vec3(0.f, 0.f, -500.f);
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
	CreateBullet();
	// //미사일 프리팹 참조
	//Ptr<CPrefab> pMissilePrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"MissilePrefab");
	//Vec3 vMissilePos = Transform()->GetRelativePos() + Vec3(0.f, 0.5f, 0.f) * Transform()->GetRelativeScale();
	//CGameObject* pCloneMissile = pMissilePrefab->Instantiate();

	//// 레벨에 추가
	//SpawnGameObject(pCloneMissile, vMissilePos, L"PlayerProjectile");
}

void CPlayerScript::Move()
{
	Vec3 vCurPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRot();
	Vec2 MousePos = CKeyMgr::GetInst()->GetMousePos(); //Y = 426

	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);



	if (KEY_PRESSED(KEY::Q))
		m_Booster = true;

	if (KEY_RELEASE(KEY::Q))
		m_Booster = false;

	if (KEY_TAP(KEY::F))
	{
		CreateBullet();
	}

	if (Bullet != nullptr)
	{
		if (Enemy != nullptr)
		{
			Vec3 BulletPos = Bullet->Transform()->GetRelativePos();
			//Vec3 EnemyPos = Enemy->Transform()->GetRelativePos();
			Vec3 ShootDir = CameraScript->GetvFront();

			BulletPos += ShootDir * DT * 1000.f;
			Bullet->Transform()->SetRelativePos(BulletPos);
		}
	}

	if (KEY_PRESSED(KEY::W))
	{
	}


	if (KEY_PRESSED(KEY::S))
	{

	}
	if (KEY_PRESSED(KEY::A))
	{
	}

	if (KEY_PRESSED(KEY::D))
	{
	}

	Transform()->SetRelativeRot(vRot);
	Transform()->SetRelativePos(vCurPos);
	PrevMousePos = CKeyMgr::GetInst()->GetMousePos();
}

void CPlayerScript::Booster()
{
}

void CPlayerScript::CreateBullet()
{
	
	CGameObject* Parent = GetOwner()->GetParent();
	Vec3 ParentPos = Parent->Transform()->GetRelativePos();
	Vec3 ParentRot = Parent->Transform()->GetRelativeRot();
	//Vec3 BulletPos = Vec3(ParentPos.x + 122.f, ParentPos.y - 100.f, ParentPos.z + 913.f);
	//Vec3 ParentPos = Transform()->GetRelativePos();
	Bullet = new CGameObject;
	SetBullet(Bullet);
	Bullet->SetName(L"Bullet");
	Bullet->AddComponent(new CTransform);
	Bullet->AddComponent(new CMeshRender);
	Bullet->AddComponent(new BulletScript);

	BulletScript* BS = Bullet->GetScript<BulletScript>();
	BS->SetPlayerScript(this);

	Bullet->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	Bullet->Transform()->SetRelativeRot(Vec3(ParentRot));
	Bullet->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	Bullet->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);

	
	Bullet->AddComponent(new CCollider2D);
	Bullet->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Bullet->Collider2D()->SetOffsetScale(Vec3(1.f,1.f, 1.f));

	SpawnGameObject(Bullet, Vec3(ParentPos.x,ParentPos.y,ParentPos.z), L"Player");
}

void CPlayerScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* pOtherObject = _Other->GetOwner();

	if (pOtherObject->GetName() == L"Monster")
	{
		DestroyObject(pOtherObject);
	}

	//test
}







void CPlayerScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
}