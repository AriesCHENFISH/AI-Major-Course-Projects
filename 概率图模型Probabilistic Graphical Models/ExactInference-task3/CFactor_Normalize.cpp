/////////////////////////////////////////////////////////////////////////////////////////////
//�ļ�����		CFactor_Normalize.cpp
//��  �ܣ�		�淶������
//�����ߣ�		��־ǿ
//��  �ڣ�		2021��03��15��
//��  �£�		2021��03��23��
//��  �£�		2021��03��29��
//��  �ȣ�		40��
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC��׼ͷ�ļ�
#include "CFactor.h"								//������ͷ�ļ�
#include "Helper.h"									//��������ͷ�ļ�
#include<iostream>
using namespace std;

//��  �ƣ�		Normalize()
//��  �ܣ�		�淶������
//��  ����		��
//����ֵ��		��
void CFactor::Normalize()
{
	
	double NormalF = 0.0f;

	//�����������Ӻͣ���Ϊ��һ������
	for (int i = 0; i < m_FactorRows.size(); i++)
	{
		//�ۼ���������ֵ
		NormalF += m_FactorRows[i].fValue;
	}

	//��һ��
	for (int i = 0; i < m_FactorRows.size(); i++)
	{
		
		m_FactorRows[i].fValue /= NormalF;
	}
}