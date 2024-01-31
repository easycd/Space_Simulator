#pragma once
#include "CEntity.h"

#include "ptr.h"
#include "CTexture.h"
#include "CMesh.h"


class CStructuredBuffer;
class CAnimator3D;

class CAnim3D :
    public CEntity
{
private:
    CAnimator3D* m_pOwner;

    int                 m_iCurFrm;
    float               m_fTime;

    bool                m_bFinish;

    Ptr<CMesh>				m_pMesh;

    const vector<tMTBone>* m_pVecBones;
    const vector<tMTAnimClip>* m_pVecClip;


    vector<tMTAnimClip> mClip;
    vector<tMTAnimClip> m_vecFrm;

    vector<float>				m_vecClipUpdateTime;
    vector<Matrix>				m_vecFinalBoneMat; // 텍스쳐에 전달할 최종 행렬정보
    int							m_iFrameCount; // 30
    double						m_dCurTime;
    int							m_iCurClip; // 클립 인덱스	

    int                         m_StartTime;
    int                         m_EndTime;

    int							m_iFrameIdx; // 클립의 현재 프레임
    int							m_iNextFrameIdx; // 클립의 다음 프레임
    float						m_fRatio;	// 프레임 사이 비율

    CStructuredBuffer* m_pBoneFinalMatBuffer;  // 특정 프레임의 최종 행렬
    bool						m_bFinalMatUpdate; // 최종행렬 연산 수행여부

public:
    void finaltick();
    void Create(const wstring& _strAnimName
        , double CurClipIndex, double mStartTime, double mFinalTime);

    void SetAnimClip(const vector<tMTAnimClip>* _vecAnimClip, vector<float> m_vecClipUpdateTime);
    const tMTAnimClip& GetCurFrame() { return m_vecFrm[m_iCurClip]; }

    bool IsFinish() { return m_bFinish; }
    void Reset()
    {
        m_dCurTime = 0.f;
        m_bFinish = false;
    }

    void SaveToLevelFile(FILE* _File);
    void LoadFromLevelFile(FILE* _File);


    CLONE(CAnim3D);
public:
    CAnim3D();
    ~CAnim3D();

    friend class CAnimator3D;
};
