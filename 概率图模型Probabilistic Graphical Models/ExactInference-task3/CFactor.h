/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor.h
//��  �ܣ�		����������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��12��
//��  �£�		2021��03��13��
//��  �£�		2021��03��29��
//��  �ȣ�		210��
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>							//mapͷ�ļ�
#include <set>							//setͷ�ļ�
#include <string>						//stringͷ�ļ�
#include <list>							//listͷ�ļ�
#include <vector>						//vectorͷ�ļ�
#include <algorithm>					//algorithm��ͷ�ļ�
#include <numeric>						//numeric��ͷ�ļ�
#include <sstream>						//sstream��ͷ�ļ�
#include <fstream>						//fstream��ͷ�ļ�
#include <time.h>						//ʱ�亯����ͷ�ļ�
#include "math.h"						//��ѧ����ͷ�ļ�
#include "Helper.h"						//��������ͷ�ļ�


//���������ռ�
using namespace std;					//ʹ�ñ�׼�����ռ�


//����������
typedef struct
{
	vector<unsigned int> ValueIDs;								//01 ����ֵID���б����ձ���ID�б��˳������
	double fValue;												//02 ���ӵ�ֵ
}FACTOR_ROW;


//����������
class CFactor
{
	//���캯������������
public:
	CFactor();													//���캯��
	~CFactor();													//��������

	//���з���
public:
	//��ʼ��
	void SetFactorVariableIDs(vector<unsigned int>&);			//�������ӵı���ID�б�
	void SetFactorRow(vector<unsigned int>&, double&);			//���������е�ֵ
	//����
	vector<unsigned int> GetFactorVariableIDs();				//��ȡ����ID�б�
	//����
	void ReduceGivenVariable(unsigned int, unsigned int);		//���ӻ���������������ID���ͱ���ֵID
	void SumOutVariable(unsigned int);								//������͵���������ID
	void Normalize();											//���ӹ�һ��
	//��ѯ
	double Query(vector<unsigned int>&,vector<unsigned int>&);	//���ݸ�������ID���ϡ�����ֵID�ļ��ϣ���ȡ�����ѯ�ĸ���ֵ

    // 1.1 �������ӻ��˷�
    CFactor operator*(const CFactor& other)
    {
        // �������ڴ洢�����������
        CFactor result;

        // ���ڴ洢�ӵ�һ�����ӵı������ڶ������ӵı���λ�õ�ӳ��
        map<unsigned int, unsigned int> FirstToSecondVars;

        // ������һ�����ӵı���
        for (unsigned int i = 0; i < m_VariableIDs.size(); i++)
        {
            // ��ȡ��һ�����ӵı���ID
            unsigned int firstVarID = m_VariableIDs[i];

            // �����ڶ������ӵı���
            for (unsigned int j = 0; j < other.m_VariableIDs.size(); j++)
            {
                // ��ȡ�ڶ������ӵı���ID
                unsigned int secondVarID = other.m_VariableIDs[j];

                // �������ID��ȣ����¼ӳ���ϵ
                if (firstVarID == secondVarID)
                {
                    FirstToSecondVars.insert(make_pair(i, j));
                }
            }
        }

        // ��ӳ������ȡ�ڶ������������һ�����ӱ�����ͬ��λ�ü���
        set<unsigned int> redundantSecondVars;
        for (const auto& pair : FirstToSecondVars)
        {
            redundantSecondVars.insert(pair.second);
        }

        // ���û����ͬ�ı�������ֱ��ƴ����������
        if (FirstToSecondVars.empty())
        {
            for (const auto& firstRow : m_FactorRows)
            {
                for (const auto& secondRow : other.m_FactorRows)
                {
                    // �����µ�������
                    FACTOR_ROW newRow;

                    // �ϲ�����ֵID����
                    newRow.ValueIDs = firstRow.ValueIDs;
                    newRow.ValueIDs.insert(newRow.ValueIDs.end(), secondRow.ValueIDs.begin(), secondRow.ValueIDs.end());

                    // �����������е�ֵ
                    newRow.fValue = firstRow.fValue * secondRow.fValue;

                    // ������������ӵ����������
                    result.m_FactorRows.push_back(newRow);
                }
            }

            // �ϲ�����ID����
            result.m_VariableIDs = m_VariableIDs;
            result.m_VariableIDs.insert(result.m_VariableIDs.end(), other.m_VariableIDs.begin(), other.m_VariableIDs.end());
        }
        // �������ͬ�ı���������ƴ����������
        else
        {
            for (const auto& firstRow : m_FactorRows)
            {
                for (const auto& secondRow : other.m_FactorRows)
                {
                    // ������ֵID�Ƿ�һ��
                    if (IsConsistentValueID(firstRow, secondRow, FirstToSecondVars))
                    {
                        // �����µ�������
                        FACTOR_ROW newRow;
                        newRow.ValueIDs = firstRow.ValueIDs;

                        // ��ӵڶ��������в����һ�����ӱ����ظ���ֵ
                        for (unsigned int k = 0; k < secondRow.ValueIDs.size(); k++)
                        {
                            if (!IsINTInSet(k, redundantSecondVars))
                            {
                                newRow.ValueIDs.push_back(secondRow.ValueIDs[k]);
                            }
                        }

                        // �����������е�ֵ
                        newRow.fValue = firstRow.fValue * secondRow.fValue;

                        // ������������ӵ����������
                        result.m_FactorRows.push_back(newRow);
                    }
                }
            }

            // �ϲ�����ID����
            result.m_VariableIDs = m_VariableIDs;
            for (unsigned int i = 0; i < other.m_VariableIDs.size(); i++)
            {
                if (!IsINTInSet(i, redundantSecondVars))
                {
                    result.m_VariableIDs.push_back(other.m_VariableIDs[i]);
                }
            }
        }

        // ���ؽ������
        return result;
    }



	
	//˽�з���
private:
	//�����ӻ�ʱ�ж������Ƿ���Ժϲ�
	bool IsConsistentValueID(const FACTOR_ROW&, const FACTOR_ROW&, map<unsigned int, unsigned int>&);	//��������Ƿ����	
	//�����ʱ�����ӵ�ֵ�ϲ�������
	void MergeIntoFirstRow(FACTOR_ROW&);
	
	//˽������
private:	
	vector<unsigned int> m_VariableIDs;					//���ӱ���ID�б�
	vector<FACTOR_ROW> m_FactorRows;					//�����е��б�
};