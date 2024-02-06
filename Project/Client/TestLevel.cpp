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

#include "CLevelSaveLoad.h"


#include <Engine/CSetColorShader.h>


void CreateTestLevel()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(6)->SetName(L"sun");
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

	pMainCam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
	pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 0);

	// UI cameara
	CGameObject* pUICam = new CGameObject;
	pUICam->SetName(L"UICamera");

	pUICam->AddComponent(new CTransform);
	pUICam->AddComponent(new CCamera);

	pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pUICam->Camera()->SetCameraIndex(1);		// Sub 카메라로 지정
	pUICam->Camera()->SetLayerMask(31, true);	// 31번 레이어만 체크

	SpawnGameObject(pUICam, Vec3(0.f, 0.f, 0.f), 0);


	// SkyBox 추가
	CGameObject* pSkyBox = new CGameObject;
	pSkyBox->SetName(L"SkyBox");

	pSkyBox->AddComponent(new CTransform);
	pSkyBox->AddComponent(new CSkyBox);

	pSkyBox->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100));
	pSkyBox->SkyBox()->SetSkyBoxType(SKYBOX_TYPE::SPHERE);
	pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\skybox.png"));
	//pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\test.png"));


	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);

	// 광원 추가
	CGameObject* pLightObj = new CGameObject;
	pLightObj->SetName(L"Point Light");

	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight3D);

	pLightObj->Transform()->SetRelativeRot(Vec3(XM_PI / 4.f, XM_PI / 4.f, 0.f));
	pLightObj->Light3D()->SetLightType(LIGHT_TYPE::POINT);
	pLightObj->Light3D()->SetRadius(100000.f);
	pLightObj->Light3D()->SetLightColor(Vec3(1.f, 1.f, 1.f));	
	pLightObj->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));
	
	SpawnGameObject(pLightObj, Vec3(-10000.f, 0.f, 0.f), 0);

	// ============
	// FBX Loading
	// ============	
	{
		// 인스턴싱 테스트
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;

		//{	//태양
		//	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\01_Sun.fbx");
		//	pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\01_Sun.mdat", L"meshdata\\01_Sun.mdat");
		//	pObj = pMeshData->Instantiate();
		//
		//	pObj->SetName(L"01_Sun");
		//	pObj->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
		//	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"), 0);
		//
		//	SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), L"Default");
		//}

		{	//태양
			CGameObject* pObject = new CGameObject;
			pObject->SetName(L"sun");
			pObject->AddComponent(new CTransform);
			pObject->AddComponent(new CMeshRender);

			pObject->Transform()->SetRelativeScale(Vec3(2000.f, 2000.f, 2000.f));
			pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));


			pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"), 0);
			pObject->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solarsystem\\sun.jpg"));

			SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), L"sun");
		}

		{	//수성
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\02_Mercury.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\02_Mercury.mdat", L"meshdata\\02_Mercury.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"02_Mercury");
			pObj->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
			SpawnGameObject(pObj, Vec3(5000.f, 0.f, 0.f), L"Default");
		}

		{	//금성
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\03_Venus.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\03_Venus.mdat", L"meshdata\\03_Venus.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"03_Venus");
			pObj->Transform()->SetRelativeScale(Vec3(20.f, 20.f, 20.f));
			SpawnGameObject(pObj, Vec3(7000.f, 0.f, 0.f), L"Default");
		}
		
		{	//지구
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_Earth.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\04_Earth.mdat", L"meshdata\\04_Earth.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"04_Earth");
			pObj->Transform()->SetRelativeScale(Vec3(0.8f, 0.8f, 0.8f));
			SpawnGameObject(pObj, Vec3(9000.f, 0.f, 0.f), L"Default");
		}

		{	//달
			//pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_Moon.fbx");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\04_Moon.mdat", L"meshdata\\04_Moon.mdat");
			//pObj = pMeshData->Instantiate();
			//pObj->SetName(L"04_Moon");
			//pObj->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
			//SpawnGameObject(pObj, Vec3(3000.f, 0.f, 0.f), L"Default");
		}

		{	//화성
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\05_Mars.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\05_Mars.mdat", L"meshdata\\05_Mars.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"05_Mars");
			pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));
			SpawnGameObject(pObj, Vec3(11000.f, 0.f, 0.f), L"Default");
		}
		
		{	//목성
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\06_Jupiter.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\06_Jupiter.mdat", L"meshdata\\06_Jupiter.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"06_Jupiter");
			pObj->Transform()->SetRelativeScale(Vec3(5.f, 5.f, 5.f));
			SpawnGameObject(pObj, Vec3(20000.f, 0.f, 0.f), L"Default");
		}
		
		{	//토성
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\07_Saturn.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\07_Saturn.mdat", L"meshdata\\07_Saturn.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"07_Saturn");
			pObj->Transform()->SetRelativeScale(Vec3(0.01f, 0.01f, 0.01f));
			SpawnGameObject(pObj, Vec3(30000.f, 0.f, 0.f), L"Default");
		}
		
		{	//토성 고리
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\07_SaturnRing.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\07_SaturnRing.mdat", L"meshdata\\07_SaturnRing.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"07_SaturnRing");
			pObj->Transform()->SetRelativeScale(Vec3(0.01f, 0.01f, 0.01f));
			SpawnGameObject(pObj, Vec3(30000.f, 0.f, 0.f), L"Default");
		}
		
		{	//천왕성
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\08_Uranus.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\08_Uranus.mdat", L"meshdata\\08_Uranus.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"08_Uranus");
			pObj->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
			SpawnGameObject(pObj, Vec3(40000.f, 0.f, 0.f), L"Default");
		}
		
		{	//천왕성 고리
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\08_UranusRing.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\08_UranusRing.mdat", L"meshdata\\08_UranusRing.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"08_UranusRing");
			pObj->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
			pObj->Transform()->SetRelativeRot(Vec3(-1.0f, 0.f, 0.f));
			SpawnGameObject(pObj, Vec3(40000.f, 0.f, 0.f), L"Default");
		}
		
		{	//해왕성
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\09_Neptune.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\09_Neptune.mdat", L"meshdata\\09_Neptune.mdat");
		
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"09_Neptune");
			pObj->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
			SpawnGameObject(pObj, Vec3(48000.f, 0.f, 0.f), L"Default");
		}
	}


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
