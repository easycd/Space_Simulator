#include "pch.h"
#include "CCameraScript.h"

#include <Engine\CTransform.h>
#include <Engine\CCamera.h>

CCameraScript::CCameraScript()
	: CScript((UINT)SCRIPT_TYPE::CAMERASCRIPT)
	, m_Target(nullptr)
	, m_fCamSpeed(100.f)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::begin()
{
}

void CCameraScript::tick()
{
		Camera3DMove();
}

void CCameraScript::Camera2DMove()
{
	// 키 입력에 따른 카메라 이동
	Vec3 vPos = Transform()->GetRelativePos();

	float fSpeed = m_fCamSpeed;
	if (KEY_PRESSED(KEY::LSHIFT))
		fSpeed *= 5.f;

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT * fSpeed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * fSpeed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * fSpeed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * fSpeed;
	}


	if (KEY_PRESSED(KEY::_1))
	{
		float fScale = Camera()->GetScale();
		fScale += DT * 1.f;
		Camera()->SetScale(fScale);
	}

	if (KEY_PRESSED(KEY::_2))
	{
		float fScale = Camera()->GetScale();
		fScale -= DT * 1.f;
		Camera()->SetScale(fScale);
	}

	Transform()->SetRelativePos(vPos);
}

void CCameraScript::Camera3DMove()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRot();

	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);

	float fSpeed = m_fCamSpeed;

	if (m_Target != nullptr)
	{
		Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();
		if (KEY_PRESSED(KEY::LSHIFT))
			fSpeed *= 10.f;

		if (KEY_PRESSED(KEY::W))
		{
			//TarGetPos += DT * vFront * fSpeed;
			vPos += DT * vFront * fSpeed;
			
		}

		if (KEY_PRESSED(KEY::S))
		{
			//vPos -= DT * vFront * fSpeed;
		}

		if (KEY_PRESSED(KEY::A))
		{
			//vPos -= DT * vRight * fSpeed;
		}

		if (KEY_PRESSED(KEY::D))
		{
			//vPos += DT * vRight * fSpeed;
		}



		if (KEY_PRESSED(KEY::RBTN))
		{
			Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();
			vRot.y += DT * vMouseDir.x * 0.5f;
			vRot.x -= DT * vMouseDir.y * 0.5f;
		}

		Transform()->SetRelativePos(TarGetPos);
		Transform()->SetRelativePos(vPos);
		Transform()->SetRelativeRot(vRot);
	}

}
