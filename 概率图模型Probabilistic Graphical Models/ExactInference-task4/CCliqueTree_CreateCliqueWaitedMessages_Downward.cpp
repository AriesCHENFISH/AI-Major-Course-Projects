/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_CreateCliqueWaitedMessages_Downward.cpp
//��  �ܣ�		���´�����Ϣʱ�������ŵĵȴ���Ϣ����
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��04��
//��  �£�		2021��05��18��
//��  �ȣ�		70��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		CreateCliqueWaitedMessages_Downward()
//��  �ܣ�		���´�����Ϣʱ�������ŵĵȴ���Ϣ����
//��  ����		map<unsigned int,set<unsigned int>>&
//����ֵ��		��
void CCliqueTree::CreateCliqueWaitedMessages_Downward(map<unsigned int, set<unsigned int>>& WaitedMessages)
{
    ////////////////////////////////////////////////////////////////////////////////
    // ����1�����������ţ���ʼ�����´�����Ϣʱ���ŵĵȴ���Ϣ����Ϊ��
    for (unsigned int i = 0; i < m_CTNodes.size(); i++)
    {
        WaitedMessages[m_CTNodes[i].nID] = set<unsigned int>();
    }

    ////////////////////////////////////////////////////////////////////////////////
    // ����2���������еĸ��ڵ���ӽڵ��ϵ�����ȴ���Ϣ����
    for (auto parentChildPair = m_Parent2Childs.begin(); parentChildPair != m_Parent2Childs.end(); ++parentChildPair)
    {
        unsigned int parentID = parentChildPair->first;
        const set<unsigned int>& childIDs = parentChildPair->second;

        // ����3��Ϊÿ���ӽڵ����õȴ���Ϣ���ϣ����ӽڵ�ȴ��丸�ڵ����Ϣ��
        for (auto childID = childIDs.begin(); childID != childIDs.end(); ++childID)
        {
            WaitedMessages[*childID].insert(parentID);
        }
    }
}