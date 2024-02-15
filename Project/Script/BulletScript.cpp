#include "pch.h"
#include "BulletScript.h"
#include "CPlayerScript.h"

BulletScript::BulletScript()
	: CScript((UINT)SCRIPT_TYPE::BULLETSCRIPT)
	, m_TargetObject(nullptr)
{
}

BulletScript::~BulletScript()
{
}

void BulletScript::begin()
{
	// ������ �����ϴ� ���͸� ã�Ƽ� Ÿ������ ��´�.
	//m_TargetObject = CLevelMgr::GetInst()->FindObjectByName(L"Monster");
}

void BulletScript::tick()
{
}

void BulletScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* pOtherObject = _Other->GetOwner();

	if (L"House" == _Other->GetOwner()->GetName())
	{
		PlayerScript->SetBullet(nullptr);
		DestroyObject(GetOwner());
	}
}
