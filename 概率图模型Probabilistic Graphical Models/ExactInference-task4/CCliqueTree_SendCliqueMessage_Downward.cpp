/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CCliqueTree_SendCliqueMessage_Downward.cpp
//��  �ܣ�		���·�������Ϣ
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��04��04��
//��  �£�		2021��05��18��
//��  �ȣ�		60��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CCliqueTree.h"							//������ȷ������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�


//��  �ƣ�		SendCliqueMessage_Downward()
//��  �ܣ�		���·�������Ϣ
//��  ����		unsigned int
//����ֵ��		��
void CCliqueTree::SendCliqueMessage_Downward(unsigned int nID, unsigned int nChildID)
{
    // �ҵ��ཻ�ı���ID����
    set<unsigned int> CommonVariableIDs;

    // ��ȡ�����ŵı���ID����
    FindCommonVariableIDs(nID, nChildID, CommonVariableIDs);

    // ��ȡ���ڵ���ӽڵ����
    CClique parentClique = m_Cliques[m_CliqueID2Poses[nID]];
    CClique childClique = m_Cliques[m_CliqueID2Poses[nChildID]];

    // ��ȥ�ı���ID����
    set<unsigned int> EliminateVariableIDs;

    // ���ڵ��ŵı���ID����
    set<unsigned int> parentVariableIDs(parentClique.GetVariableIDs().begin(), parentClique.GetVariableIDs().end());

    // �Ӹ��ڵ��ŵı���ID�����м�ȥ�ཻ����ID���ϣ��õ���ȥ�ı���ID����
    SubtractBetweenSets(parentVariableIDs, CommonVariableIDs, EliminateVariableIDs);

    // ���ӽڵ��ŵ�ÿһ�н��б�����ͣ���ȥ������
    for (unsigned int varID : EliminateVariableIDs)
    {
        childClique.SumOutVariable(varID);
    }

    // ���������ӽڵ��ŵ���Ϣ���͵����ڵ���
    parentClique = parentClique * childClique;

    // ��һ������
    parentClique.Normalize();

    // ���¸��ڵ���
    m_Cliques[m_CliqueID2Poses[nID]] = parentClique;
}