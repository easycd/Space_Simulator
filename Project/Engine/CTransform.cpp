#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_vRelativeScale(Vec3(1.f, 1.f, 1.f))
	, m_bAbsolute(false)	
	, m_vRelativeDir{
		  Vec3(1.f, 0.f, 0.f)
		, Vec3(0.f, 1.f, 0.f)
		, Vec3(0.f, 0.f, 1.f)}	
{
	SetName(L"Transform");
}

CTransform::~CTransform()
{
}

void CTransform::finaltick()
{
	if (L"Muzzle" == GetOwner()->GetName())
	{
		m_matWorldScale = XMMatrixIdentity();
		m_matWorldScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);

		Matrix matCameraScale = GetCameraWorldScaleMat();
		Matrix matCameraScaleInv = XMMatrixInverse(nullptr, matCameraScale);

		Matrix matRot = XMMatrixIdentity();
		matRot = XMMatrixRotationX(m_vRelativeRot.x);
		matRot *= XMMatrixRotationY(m_vRelativeRot.y);
		matRot *= XMMatrixRotationZ(m_vRelativeRot.z);

		Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);

		m_matWorld = m_matWorldScale * matRot * matTranslation;

		Vec3 vDefaultDir[3] = {
			  Vec3(1.f, 0.f, 0.f)
			, Vec3(0.f, 1.f, 0.f)
			, Vec3(0.f, 0.f, 1.f)
		};

		for (int i = 0; i < 3; ++i)
		{
			m_vWorldDir[i] = m_vRelativeDir[i] = XMVector3TransformNormal(vDefaultDir[i], matRot);
		}

		// 부모 오브젝트 확인
		CGameObject* pParent = GetOwner()->GetParent();
		if (pParent)
		{
			if (m_bAbsolute)
			{
				Matrix matParentWorld = pParent->Transform()->m_matWorld;
				Matrix matParentScale = pParent->Transform()->m_matWorldScale;
				Matrix matParentScaleInv = XMMatrixInverse(nullptr, matParentScale);

				// 월드 = 로컬월드 * 부모크기 역 * 부모 월드(크기/회전/이동)
				m_matWorld = m_matWorld * matParentScaleInv * matParentWorld;
			}
			else
			{
				m_matWorldScale = pParent->Transform()->m_matWorldScale;
				m_matWorld *= pParent->Transform()->m_matWorld;
			}


			for (int i = 0; i < 3; ++i)
			{
				m_vWorldDir[i] = XMVector3TransformNormal(vDefaultDir[i], m_matWorld);
				m_vWorldDir[i].Normalize();
			}
		}

		m_matWorldInv = XMMatrixInverse(nullptr, m_matWorld);
	}

	if (L"SpaceShip" == GetOwner()->GetName())
	{
		Player_matWorldScale = XMMatrixIdentity();
		Player_matWorldScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);

		SetPlayerWorldScaleMat(Player_matWorldScale);

		m_matWorldScale = Player_matWorldScale;

		//Matrix matCameraScale = GetCameraWorldScaleMat();
		//Matrix matCameraScaleInv = XMMatrixInverse(nullptr, matCameraScale);

		matRot = XMMatrixIdentity();
		matRot = XMMatrixRotationX(m_vRelativeRot.x);
		matRot *= XMMatrixRotationY(m_vRelativeRot.y);
		matRot *= XMMatrixRotationZ(m_vRelativeRot.z);

		Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);

		Player_matWorld = m_matWorldScale * matRot * matTranslation;
		SetPlayerWorldMat(Player_matWorld);
		m_matWorld = Player_matWorld;

		Vec3 vDefaultDir[3] = {
			  Vec3(1.f, 0.f, 0.f)
			, Vec3(0.f, 1.f, 0.f)
			, Vec3(0.f, 0.f, 1.f)
		};

		for (int i = 0; i < 3; ++i)
		{
			m_vWorldDir[i] = m_vRelativeDir[i] = XMVector3TransformNormal(vDefaultDir[i], matRot);
		}

		// 부모 오브젝트 확인
		CGameObject* pParent = GetOwner()->GetParent();
		if (pParent)
		{
			if (m_bAbsolute)
			{
				Matrix matParentWorld = GetCameraWorldMat();
				Matrix matParentScale = GetCameraWorldScaleMat();
				Matrix matParentScaleInv = XMMatrixInverse(nullptr, matParentScale);

				// 월드 = 로컬월드 * 부모크기 역 * 부모 월드(크기/회전/이동)
				m_matWorld = m_matWorld * matParentScaleInv * matParentWorld;
			}
			else
			{
				m_matWorldScale = pParent->Transform()->m_matWorldScale;
				m_matWorld *= pParent->Transform()->m_matWorld;
			}


			for (int i = 0; i < 3; ++i)
			{
				m_vWorldDir[i] = XMVector3TransformNormal(vDefaultDir[i], m_matWorld);
				m_vWorldDir[i].Normalize();
			}
		}

		m_matWorldInv = XMMatrixInverse(nullptr, m_matWorld);
	}

	if(L"MainCamera" == GetOwner()->GetName())
	{
		Camera_matWorldScale = XMMatrixIdentity();
		Camera_matWorldScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);

		Matrix matPlayerWorld = Player_matWorld;
		//Matrix matParentScale = pParent->Transform()->m_matWorldScale;

		//Matrix m_PlayerWorldScale = Camera_matWorldScale;

		matRot = XMMatrixIdentity();
		matRot = XMMatrixRotationX(m_vRelativeRot.x);
		matRot *= XMMatrixRotationY(m_vRelativeRot.y);
		matRot *= XMMatrixRotationZ(m_vRelativeRot.z);

		Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);


		Camera_matWorld = Camera_matWorldScale * matRot;
		m_matWorld = Camera_matWorld * matTranslation;

		Vec3 vDefaultDir[3] = {
			  Vec3(1.f, 0.f, 0.f)
			, Vec3(0.f, 1.f, 0.f)
			, Vec3(0.f, 0.f, 1.f)
		};

		for (int i = 0; i < 3; ++i)
		{
			m_vWorldDir[i] = m_vRelativeDir[i] = XMVector3TransformNormal(vDefaultDir[i], matRot);
		}

		// 부모 오브젝트 확인
		CGameObject* pParent = GetOwner()->GetParent();
		if (pParent)
		{
			if (m_bAbsolute)
			{
				Matrix matParentWorld = pParent->Transform()->m_matWorld;
				Matrix matParentScale = pParent->Transform()->m_matWorldScale;
				Matrix matParentScaleInv = XMMatrixInverse(nullptr, matParentScale);
				Matrix matParentRot = pParent->Transform()->matRot;

				// 월드 = 로컬월드 * 부모크기 역 * 부모 월드(크기/회전/이동)
				m_matWorld = m_matWorld * matParentScaleInv * matParentWorld;
			}
			else
			{
				m_matWorldScale = pParent->Transform()->m_matWorldScale;
				m_matWorld *= pParent->Transform()->m_matWorld;
			}


			for (int i = 0; i < 3; ++i)
			{
				m_vWorldDir[i] = XMVector3TransformNormal(vDefaultDir[i], m_matWorld);
				m_vWorldDir[i].Normalize();
			}
		}

		m_matWorldInv = XMMatrixInverse(nullptr, m_matWorld);
	}
	else
	{
		m_matWorldScale = XMMatrixIdentity();
		m_matWorldScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);

		Matrix matRot = XMMatrixIdentity();
		matRot = XMMatrixRotationX(m_vRelativeRot.x);
		matRot *= XMMatrixRotationY(m_vRelativeRot.y);
		matRot *= XMMatrixRotationZ(m_vRelativeRot.z);

		Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);

		m_matWorld = m_matWorldScale * matRot * matTranslation;

		Vec3 vDefaultDir[3] = {
			  Vec3(1.f, 0.f, 0.f)
			, Vec3(0.f, 1.f, 0.f)
			, Vec3(0.f, 0.f, 1.f)
		};

		for (int i = 0; i < 3; ++i)
		{
			m_vWorldDir[i] = m_vRelativeDir[i] = XMVector3TransformNormal(vDefaultDir[i], matRot);
		}

		// 부모 오브젝트 확인
		CGameObject* pParent = GetOwner()->GetParent();
		if (pParent)
		{
			if (m_bAbsolute)
			{
				Matrix matParentWorld = pParent->Transform()->m_matWorld;
				Matrix matParentScale = pParent->Transform()->m_matWorldScale;
				Matrix matParentScaleInv = XMMatrixInverse(nullptr, matParentScale);

				// 월드 = 로컬월드 * 부모크기 역 * 부모 월드(크기/회전/이동)
				m_matWorld = m_matWorld * matParentScaleInv * matParentWorld;
			}
			else
			{
				m_matWorldScale = pParent->Transform()->m_matWorldScale;
				m_matWorld *= pParent->Transform()->m_matWorld;
			}


			for (int i = 0; i < 3; ++i)
			{
				m_vWorldDir[i] = XMVector3TransformNormal(vDefaultDir[i], m_matWorld);
				m_vWorldDir[i].Normalize();
			}
		}

		m_matWorldInv = XMMatrixInverse(nullptr, m_matWorld);
	}
}

void CTransform::UpdateData()
{
	// 위치값을 상수버퍼에 전달 및 바인딩		
	CConstBuffer* pTransformBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);

	g_transform.matWorld = m_matWorld;
	g_transform.matWorldInv = m_matWorldInv;
	g_transform.matWV = g_transform.matWorld * g_transform.matView;
	g_transform.matWVP = g_transform.matWV * g_transform.matProj;


	pTransformBuffer->SetData(&g_transform);
	pTransformBuffer->UpdateData();
}

void CTransform::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_vRelativePos	, sizeof(Vec3), 1, _File);
	fwrite(&m_vRelativeScale, sizeof(Vec3), 1, _File);
	fwrite(&m_vRelativeRot	, sizeof(Vec3), 1, _File);
	fwrite(&m_bAbsolute, sizeof(bool), 1, _File);
}

void CTransform::LoadFromLevelFile(FILE* _FILE)
{	
	fread(&m_vRelativePos, sizeof(Vec3), 1, _FILE);
	fread(&m_vRelativeScale, sizeof(Vec3), 1, _FILE);
	fread(&m_vRelativeRot, sizeof(Vec3), 1, _FILE);
	fread(&m_bAbsolute, sizeof(bool), 1, _FILE);
}
