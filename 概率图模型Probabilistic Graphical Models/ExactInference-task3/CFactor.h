/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CFactor.h
//功  能：		定义因子类
//开发者：		高志强
//日  期：		2021年03月12日
//更  新：		2021年03月13日
//更  新：		2021年03月29日
//长  度：		210行
/////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <map>							//map头文件
#include <set>							//set头文件
#include <string>						//string头文件
#include <list>							//list头文件
#include <vector>						//vector头文件
#include <algorithm>					//algorithm类头文件
#include <numeric>						//numeric类头文件
#include <sstream>						//sstream类头文件
#include <fstream>						//fstream类头文件
#include <time.h>						//时间函数类头文件
#include "math.h"						//数学函数头文件
#include "Helper.h"						//辅助函数头文件


//声明命名空间
using namespace std;					//使用标准命名空间


//定义因子行
typedef struct
{
	vector<unsigned int> ValueIDs;								//01 变量值ID的列表，按照变量ID列表的顺序排列
	double fValue;												//02 因子的值
}FACTOR_ROW;


//定义因子类
class CFactor
{
	//构造函数与析构函数
public:
	CFactor();													//构造函数
	~CFactor();													//析构函数

	//公有方法
public:
	//初始化
	void SetFactorVariableIDs(vector<unsigned int>&);			//设置因子的变量ID列表
	void SetFactorRow(vector<unsigned int>&, double&);			//设置因子行的值
	//访问
	vector<unsigned int> GetFactorVariableIDs();				//获取变量ID列表
	//操作
	void ReduceGivenVariable(unsigned int, unsigned int);		//因子化简。消除给定变量ID、和变量值ID
	void SumOutVariable(unsigned int);								//因子求和掉给定变量ID
	void Normalize();											//因子归一化
	//查询
	double Query(vector<unsigned int>&,vector<unsigned int>&);	//根据给定变量ID集合、变量值ID的集合，获取具体查询的概率值

    // 1.1 重载因子积乘法
    CFactor operator*(const CFactor& other)
    {
        // 定义用于存储结果的新因子
        CFactor result;

        // 用于存储从第一个因子的变量到第二个因子的变量位置的映射
        map<unsigned int, unsigned int> FirstToSecondVars;

        // 遍历第一个因子的变量
        for (unsigned int i = 0; i < m_VariableIDs.size(); i++)
        {
            // 获取第一个因子的变量ID
            unsigned int firstVarID = m_VariableIDs[i];

            // 遍历第二个因子的变量
            for (unsigned int j = 0; j < other.m_VariableIDs.size(); j++)
            {
                // 获取第二个因子的变量ID
                unsigned int secondVarID = other.m_VariableIDs[j];

                // 如果变量ID相等，则记录映射关系
                if (firstVarID == secondVarID)
                {
                    FirstToSecondVars.insert(make_pair(i, j));
                }
            }
        }

        // 从映射中提取第二个因子中与第一个因子变量相同的位置集合
        set<unsigned int> redundantSecondVars;
        for (const auto& pair : FirstToSecondVars)
        {
            redundantSecondVars.insert(pair.second);
        }

        // 如果没有相同的变量，则直接拼接两个因子
        if (FirstToSecondVars.empty())
        {
            for (const auto& firstRow : m_FactorRows)
            {
                for (const auto& secondRow : other.m_FactorRows)
                {
                    // 定义新的因子行
                    FACTOR_ROW newRow;

                    // 合并变量值ID序列
                    newRow.ValueIDs = firstRow.ValueIDs;
                    newRow.ValueIDs.insert(newRow.ValueIDs.end(), secondRow.ValueIDs.begin(), secondRow.ValueIDs.end());

                    // 计算新因子行的值
                    newRow.fValue = firstRow.fValue * secondRow.fValue;

                    // 将新因子行添加到结果因子中
                    result.m_FactorRows.push_back(newRow);
                }
            }

            // 合并变量ID序列
            result.m_VariableIDs = m_VariableIDs;
            result.m_VariableIDs.insert(result.m_VariableIDs.end(), other.m_VariableIDs.begin(), other.m_VariableIDs.end());
        }
        // 如果有相同的变量，则间接拼接两个因子
        else
        {
            for (const auto& firstRow : m_FactorRows)
            {
                for (const auto& secondRow : other.m_FactorRows)
                {
                    // 检查变量值ID是否一致
                    if (IsConsistentValueID(firstRow, secondRow, FirstToSecondVars))
                    {
                        // 定义新的因子行
                        FACTOR_ROW newRow;
                        newRow.ValueIDs = firstRow.ValueIDs;

                        // 添加第二个因子中不与第一个因子变量重复的值
                        for (unsigned int k = 0; k < secondRow.ValueIDs.size(); k++)
                        {
                            if (!IsINTInSet(k, redundantSecondVars))
                            {
                                newRow.ValueIDs.push_back(secondRow.ValueIDs[k]);
                            }
                        }

                        // 计算新因子行的值
                        newRow.fValue = firstRow.fValue * secondRow.fValue;

                        // 将新因子行添加到结果因子中
                        result.m_FactorRows.push_back(newRow);
                    }
                }
            }

            // 合并变量ID序列
            result.m_VariableIDs = m_VariableIDs;
            for (unsigned int i = 0; i < other.m_VariableIDs.size(); i++)
            {
                if (!IsINTInSet(i, redundantSecondVars))
                {
                    result.m_VariableIDs.push_back(other.m_VariableIDs[i]);
                }
            }
        }

        // 返回结果因子
        return result;
    }



	
	//私有方法
private:
	//在因子积时判断两行是否可以合并
	bool IsConsistentValueID(const FACTOR_ROW&, const FACTOR_ROW&, map<unsigned int, unsigned int>&);	//检查两行是否兼容	
	//在求和时将因子的值合并到首行
	void MergeIntoFirstRow(FACTOR_ROW&);
	
	//私有数据
private:	
	vector<unsigned int> m_VariableIDs;					//因子变量ID列表
	vector<FACTOR_ROW> m_FactorRows;					//因子行的列表
};