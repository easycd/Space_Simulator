#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CCollisionMgr.h>

#include <Script\CPlayerScript.h>
#include <Script\CMonsterScript.h>
#include <Script\CCameraScript.h>

#include "CLevelSaveLoad.h"


#include <Engine/CSetColorShader.h>


void CreateTestLevel()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Tile");
	pCurLevel->GetLayer(2)->SetName(L"Player");
	pCurLevel->GetLayer(3)->SetName(L"Monster");
	pCurLevel->GetLayer(4)->SetName(L"PlayerProjectile");
	pCurLevel->GetLayer(5)->SetName(L"MonsterProjectile");
	pCurLevel->GetLayer(31)->SetName(L"ViewPort UI");


	// Main Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);
	pMainCam->AddComponent(new CCameraScript);

	pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
	pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.

	//pMainCam->Transform()->SetRelativeRot(-XM_PI * 1.6, XM_PI * 3, 0.f);

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 0);
	pMainCam->Transform()->SetMainCamera(pMainCam);

	//// UI cameara
	////CGameObject* pUICam = new CGameObject;
	////pUICam->SetName(L"UICamera");

	////pUICam->AddComponent(new CTransform);
	////pUICam->AddComponent(new CCamera);

	////pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	////pUICam->Camera()->SetCameraIndex(1);		// Sub 카메라로 지정
	////pUICam->Camera()->SetLayerMask(31, true);	// 31번 레이어만 체크

	////SpawnGameObject(pUICam, Vec3(0.f, 0.f, 0.f), 0);


	// SkyBox 추가
	CGameObject* pSkyBox = new CGameObject;
	pSkyBox->SetName(L"SkyBox");

	pSkyBox->AddComponent(new CTransform);
	pSkyBox->AddComponent(new CSkyBox);

	pSkyBox->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	pSkyBox->SkyBox()->SetSkyBoxType(SKYBOX_TYPE::SPHERE);
	pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\Space.png"));

	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), L"Player");

	// 광원 추가
	CGameObject* pLightObj = new CGameObject;
	pLightObj->SetName(L"Directional Light");

	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight3D);

	pLightObj->Transform()->SetRelativeRot(Vec3(XM_PI / 4.f, XM_PI / 4.f, 0.f));
	pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObj->Light3D()->SetRadius(10000.f);
	pLightObj->Light3D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLightObj->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));

	SpawnGameObject(pLightObj, Vec3(-2000, 2000.f, -2000.f), 0);

	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"Directional Light");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);


	//SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);

	// ============
	// FBX Loading
	// ============	




	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* Plane = nullptr;

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\untitled.fbx");
	//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\untitled.mdat");
	Plane = pMeshData->Instantiate();
	Plane->Transform()->SetRelativeScale(Vec3(0.3f, 0.3f, 0.3f));
	//pObj->Animator3D()->CreateAnimation(L"Walk", 0, 2, 7);
	//pObj->Animator3D()->Play(L"Walk", true);
	Plane->Transform()->SetRelativeRot(Vec3(XM_PI / 2.2f, XM_PI * 1.05, XM_PI / 90.f));
	//Plane->Transform()->SetRelativeRot(Vec3(0.f,0.f,0.f));
	Plane->AddComponent(new CPlayerScript);



	CCameraScript* CCS = pMainCam->GetScript<CCameraScript>();
	CCS->SetTarget(Plane);


	//Plane->AddComponent(new CCollider2D);
	//Plane->Collider2D()->SetOffsetPos(Vec3(0.f, -300.f, 0.f));
	//Plane->Collider2D()->SetOffsetScale(Vec3(1000.f,1000.f, 1000.f));
	Plane->SetName(L"SpaceShip");
	SpawnGameObject(Plane, Vec3(53.f, -170.f, 500.f), L"Player");

	//Plane->AddChild(pMainCam);


	//CGameObject* Muzzle = new CGameObject;
	//Muzzle->SetName(L"Muzzle");
	//Muzzle->AddComponent(new CTransform);
	//Muzzle->AddComponent(new CMeshRender);

	//Muzzle->Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));
	//Muzzle->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
	//Muzzle->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//Muzzle->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);

	//Muzzle->AddComponent(new CCollider2D);
	//Muzzle->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	//Muzzle->Collider2D()->SetOffsetScale(Vec3(1000.f,1000.f, 1000.f));

	//SpawnGameObject(Muzzle, Vec3(-1.f,-909.f,-233.f), 0);

	//Plane->AddChild(Muzzle);
	pMainCam->AddChild(Plane);

	{
		Ptr<CMeshData> HouseMeshData = nullptr;
		CGameObject* pHouse = nullptr;

		//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\House.fbx");
		HouseMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\House.mdat");
		pHouse = HouseMeshData->Instantiate();
		CPlayerScript* PS = Plane->GetScript<CPlayerScript>();
		PS->SetEnemy(pHouse);
		pHouse->Transform()->SetRelativeScale(Vec3(0.5f, 0.5f, 0.5f));
		pHouse->AddComponent(new CCollider2D);
		pHouse->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		pHouse->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
		pHouse->SetName(L"House");
		SpawnGameObject(pHouse, Vec3(200.f, 300.f, 1000.f), L"Monster");

	}


	//{

	//	Ptr<CMeshData> HouseMeshData2 = nullptr;
	//	CGameObject* pHouse2 = nullptr;

	//	//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\SpaceShuttle.fbx");
	//	HouseMeshData2 = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\House.mdat");
	//	pHouse2 = HouseMeshData2->Instantiate();
	//	pHouse2->Transform()->SetRelativeScale(Vec3(0.5f, 0.5f, 0.5f));
	//	pHouse2->AddComponent(new CCollider2D);
	//	pHouse2->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	//	pHouse2->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
	//	pHouse2->SetName(L"House2");
	//	SpawnGameObject(pHouse2, Vec3(1500.f, 2500.f, 3000.f), L"Monster");
	//}


		//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\Monster.mdat");		
		//for (int i = 0; i < 10; ++i)
		//{
		//	pObj = pMeshData->Instantiate();
		//	pObj->Animator3D()->CreateAnimation(L"Walk", 0, 2, 7);
		//	pObj->Animator3D()->Play(L"Walk", true);
		//	pObj->SetName(L"Monster");
		//	SpawnGameObject(pObj, Vec3((i + 1) * 50.f, 200.f, 500.f), 0);
		//}


	//// LandScape Object
	//CGameObject* pLandScape = new CGameObject;
	//pLandScape->SetName(L"LandScape");

	//pLandScape->AddComponent(new CTransform);
	//pLandScape->AddComponent(new CLandScape);

	//pLandScape->Transform()->SetRelativeScale(Vec3(500.f, 3000.f, 500.f));

	//pLandScape->LandScape()->SetFace(64, 64);
	//pLandScape->LandScape()->SetFrustumCheck(false);
	////pLandScape->LandScape()->SetHeightMap(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\HeightMap_01.jpg"));

	//SpawnGameObject(pLandScape, Vec3(0.f, 0.f, 0.f), 0);

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");
}
