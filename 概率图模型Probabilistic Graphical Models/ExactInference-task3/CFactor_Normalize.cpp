/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor_Normalize.cpp
//功  能：		规范化因子
//开发者：		高志强
//日  期：		2021年03月15日
//更  新：		2021年03月23日
//更  新：		2021年03月29日
//长  度：		40行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CFactor.h"								//因子类头文件
#include "Helper.h"									//辅助函数头文件
#include<iostream>
using namespace std;

//名  称：		Normalize()
//功  能：		规范化因子
//参  数：		无
//返回值：		无
void CFactor::Normalize()
{
	
	double NormalF = 0.0f;

	//计算所有因子和，作为归一化因子
	for (int i = 0; i < m_FactorRows.size(); i++)
	{
		//累计所有因子值
		NormalF += m_FactorRows[i].fValue;
	}

	//归一化
	for (int i = 0; i < m_FactorRows.size(); i++)
	{
		
		m_FactorRows[i].fValue /= NormalF;
	}
}