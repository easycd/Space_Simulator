#include "pch.h"
#include "CAnim3D.h"

#include "CTimeMgr.h"


CAnim3D::CAnim3D()
	: m_pOwner(nullptr)
	, m_bFinish(false)
	, m_pVecBones(nullptr)
	, m_pVecClip(nullptr)
	, m_iCurClip(0)
	, m_dCurTime(0.)
	, m_iFrameCount(30)
	, m_pBoneFinalMatBuffer(nullptr)
	, m_bFinalMatUpdate(false)
	, m_iFrameIdx(0)
	, m_iNextFrameIdx(0)
	, m_fRatio(0.f)
	, m_StartTime(0)
	, m_EndTime(0)
{
}

CAnim3D::~CAnim3D()
{
}

void CAnim3D::finaltick()
{
	//if (m_bFinish)
	//	return;

	//m_dCurTime = 0.f;
	//// 현재 재생중인 Clip 의 시간을 진행한다.
	//m_vecClipUpdateTime[m_iCurClip] += DT;

	//if (m_vecClipUpdateTime[m_iCurClip] >= m_pVecClip->at(m_iCurClip).dTimeLength)
	//{
	//	m_vecClipUpdateTime[m_iCurClip] = 0.f;
	//	m_bFinish = true;
	//}

	//m_dCurTime = m_pVecClip->at(m_iCurClip).dStartTime + m_vecClipUpdateTime[m_iCurClip];

	//// 현재 프레임 인덱스 구하기
	//double dFrameIdx = m_dCurTime * (double)m_iFrameCount;
	//m_iFrameIdx = (int)(dFrameIdx);

	//// 다음 프레임 인덱스
	//if (m_iFrameIdx >= m_pVecClip->at(0).iFrameLength - 1)
	//	m_iNextFrameIdx = m_iFrameIdx;	// 끝이면 현재 인덱스를 유지
	//else
	//	m_iNextFrameIdx = m_iFrameIdx + 1;

	//// 프레임간의 시간에 따른 비율을 구해준다.
	//m_fRatio = (float)(dFrameIdx - (double)m_iFrameIdx);

	//// 컴퓨트 쉐이더 연산여부
	//m_bFinalMatUpdate = false;
}

void CAnim3D::Create(const wstring& _strAnimName
	, double CurClipIndex, double mStartTime, double mFinalTime)
{
	SetName(_strAnimName);

	//m_pVecClip = m_pMesh->GetAnimClip();
	//m_vecClipUpdateTime.resize(m_pVecClip->size());

	m_iCurClip = CurClipIndex;

	tMTAnimClip mClip = {};

	mClip.strAnimName = _strAnimName;
	mClip.dStartTime = mStartTime;
	mClip.dEndTime = mFinalTime;
	mClip.dTimeLength = mClip.dEndTime - mClip.dStartTime;

	m_vecFrm.push_back(mClip);

}

void CAnim3D::SetAnimClip(const vector<tMTAnimClip>* _vecAnimClip, vector<float> _vecClipUpdateTime)
{
	m_pVecClip = _vecAnimClip;
	m_vecClipUpdateTime.resize(m_pVecClip->size());

	// 테스트 코드
	static float fTime = 0.f;
	fTime += 1.f;
	m_vecClipUpdateTime[0] = fTime;
}

void CAnim3D::SaveToLevelFile(FILE* _File)
{

}

void CAnim3D::LoadFromLevelFile(FILE* _File)
{

}