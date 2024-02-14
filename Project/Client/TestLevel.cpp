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
#include <Script\CPlanet_Lotating.h>

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

	pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
	pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 0);

	//// UI cameara
	//CGameObject* pUICam = new CGameObject;
	//pUICam->SetName(L"UICamera");
	//
	//pUICam->AddComponent(new CTransform);
	//pUICam->AddComponent(new CCamera);
	//
	//pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	//pUICam->Camera()->SetCameraIndex(1);		// Sub 카메라로 지정
	//pUICam->Camera()->SetLayerMask(31, true);	// 31번 레이어만 체크
	//
	//SpawnGameObject(pUICam, Vec3(0.f, 0.f, 0.f), 0);


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
	//pLightObj->Light3D()->SetLightType(LIGHT_TYPE::POINT);
	pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
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

		{	//태양
			CGameObject* Sun = new CGameObject;
			Sun->SetName(L"sun");
			Sun->AddComponent(new CTransform);
			Sun->AddComponent(new CMeshRender);
			Sun->AddComponent(new CPlanet_Lotating);

			Sun->Transform()->SetRelativeScale(Vec3(100000.f, 100000.f, 100000.f));
			Sun->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

			Sun->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			Sun->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			Sun->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"), 0);
			Sun->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solarsystem\\sun.jpg"));

			SpawnGameObject(Sun, Vec3(0.f, 0.f, 0.f), L"sun");
		}

		{	//수성
			CGameObject* Mercury = new CGameObject;
			Mercury->SetName(L"02_Mercury");
			Mercury->AddComponent(new CTransform);

			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\02_Mercury.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\02_Mercury.mdat", L"meshdata\\02_Mercury.mdat");
			Mercury = pMeshData->Instantiate();

			Mercury->AddComponent(new CPlanet_Lotating);
			Mercury->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 1.0f, 0.f));
			Mercury->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
			SpawnGameObject(Mercury, Vec3(5000.f, 0.f, 0.f), L"Default");
		}

		{	//금성
			CGameObject* Venus = new CGameObject;
			Venus->SetName(L"03_Venus");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\03_Venus.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\03_Venus.mdat", L"meshdata\\03_Venus.mdat");
			Venus = pMeshData->Instantiate();
			Venus->Transform()->SetRelativeScale(Vec3(20.f, 20.f, 20.f));

			Venus->AddComponent(new CPlanet_Lotating);
			Venus->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Venus, Vec3(7000.f, 0.f, 0.f), L"Default");
		}
		
		{	//지구
			CGameObject* Earth = new CGameObject;
			Earth->SetName(L"04_Earth");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_Earth.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\04_Earth.mdat", L"meshdata\\04_Earth.mdat");
			Earth = pMeshData->Instantiate();

			Earth->AddComponent(new CPlanet_Lotating);
			Earth->Transform()->SetRelativeScale(Vec3(0.8f, 0.8f, 0.8f));
			Earth->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Earth, Vec3(9000.f, 0.f, 0.f), L"Default");
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
			CGameObject* Mars = new CGameObject;
			Mars->SetName(L"05_Mars");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\05_Mars.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\05_Mars.mdat", L"meshdata\\05_Mars.mdat");
			Mars = pMeshData->Instantiate();
			
			Mars->AddComponent(new CPlanet_Lotating);
			Mars->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));
			Mars->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Mars, Vec3(11000.f, 0.f, 0.f), L"Default");
		}
		
		{	//목성
			CGameObject* Jupiter = new CGameObject;
			Jupiter->SetName(L"06_Jupiter");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\06_Jupiter.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\06_Jupiter.mdat", L"meshdata\\06_Jupiter.mdat");
			Jupiter = pMeshData->Instantiate();
			
			Jupiter->AddComponent(new CPlanet_Lotating);
			Jupiter->Transform()->SetRelativeScale(Vec3(5.f, 5.f, 5.f));
			Jupiter->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Jupiter, Vec3(20000.f, 0.f, 0.f), L"Default");
		}
		
		{	//토성
			CGameObject* Saturn = new CGameObject;
			Saturn->SetName(L"07_Saturn");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\07_Saturn.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\07_Saturn.mdat", L"meshdata\\07_Saturn.mdat");
			Saturn = pMeshData->Instantiate();
			
			Saturn->AddComponent(new CPlanet_Lotating);
			Saturn->Transform()->SetRelativeScale(Vec3(0.01f, 0.01f, 0.01f));
			Saturn->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Saturn, Vec3(30000.f, 0.f, 0.f), L"Default");
		}
		
		{	//토성 고리
			CGameObject* SaturnRing = new CGameObject;
			SaturnRing->SetName(L"07_SaturnRing");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\07_SaturnRing.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\07_SaturnRing.mdat", L"meshdata\\07_SaturnRing.mdat");
			SaturnRing = pMeshData->Instantiate();
			
			SaturnRing->AddComponent(new CPlanet_Lotating);
			SaturnRing->Transform()->SetRelativeScale(Vec3(0.01f, 0.01f, 0.01f));
			SaturnRing->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(SaturnRing, Vec3(30000.f, 0.f, 0.f), L"Default");
		}
		
		{	//천왕성
			CGameObject* Uranus = new CGameObject;
			Uranus->SetName(L"08_Uranus");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\08_Uranus.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\08_Uranus.mdat", L"meshdata\\08_Uranus.mdat");
			Uranus = pMeshData->Instantiate();
			
			Uranus->AddComponent(new CPlanet_Lotating);
			Uranus->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
			Uranus->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Uranus, Vec3(40000.f, 0.f, 0.f), L"Default");
		}
		
		{	//천왕성 고리
			CGameObject* UranusRing = new CGameObject;
			UranusRing->SetName(L"08_UranusRing");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\08_UranusRing.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\08_UranusRing.mdat", L"meshdata\\08_UranusRing.mdat");
			UranusRing = pMeshData->Instantiate();
			
			UranusRing->AddComponent(new CPlanet_Lotating);
			UranusRing->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
			UranusRing->Transform()->SetRelativeRot(Vec3(-1.0f, 0.f, 0.f));
			UranusRing->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(UranusRing, Vec3(40000.f, 0.f, 0.f), L"Default");
		}
		
		{	//해왕성
			CGameObject* Neptune = new CGameObject;
			Neptune->SetName(L"09_Neptune");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\09_Neptune.fbx");
			pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\09_Neptune.mdat", L"meshdata\\09_Neptune.mdat");
			Neptune = pMeshData->Instantiate();
			
			Neptune->AddComponent(new CPlanet_Lotating);
			Neptune->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
			Neptune->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Neptune, Vec3(48000.f, 0.f, 0.f), L"Default");
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
