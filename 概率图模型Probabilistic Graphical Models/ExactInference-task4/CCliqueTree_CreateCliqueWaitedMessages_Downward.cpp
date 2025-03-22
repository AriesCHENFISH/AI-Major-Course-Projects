/////////////////////////////////////////////////////////////////////////////////////////////
//文件名：		CCliqueTree_CreateCliqueWaitedMessages_Downward.cpp
//功  能：		向下传递消息时，创建团的等待消息集合
//开发者：		高志强
//日  期：		2021年04月04日
//更  新：		2021年05月18日
//长  度：		70行
/////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"									//MFC标准头文件
#include "CCliqueTree.h"							//团树精确推理类头文件
#include "Helper.h"									//辅助函数头文件


//名  称：		CreateCliqueWaitedMessages_Downward()
//功  能：		向下传递消息时，创建团的等待消息集合
//参  数：		map<unsigned int,set<unsigned int>>&
//返回值：		无
void CCliqueTree::CreateCliqueWaitedMessages_Downward(map<unsigned int, set<unsigned int>>& WaitedMessages)
{
    ////////////////////////////////////////////////////////////////////////////////
    // 步骤1：遍历所有团，初始化向下传递消息时，团的等待消息集合为空
    for (unsigned int i = 0; i < m_CTNodes.size(); i++)
    {
        WaitedMessages[m_CTNodes[i].nID] = set<unsigned int>();
    }

    ////////////////////////////////////////////////////////////////////////////////
    // 步骤2：遍历所有的父节点和子节点关系，填充等待消息集合
    for (auto parentChildPair = m_Parent2Childs.begin(); parentChildPair != m_Parent2Childs.end(); ++parentChildPair)
    {
        unsigned int parentID = parentChildPair->first;
        const set<unsigned int>& childIDs = parentChildPair->second;

        // 步骤3：为每个子节点设置等待消息集合（即子节点等待其父节点的消息）
        for (auto childID = childIDs.begin(); childID != childIDs.end(); ++childID)
        {
            WaitedMessages[*childID].insert(parentID);
        }
    }
}