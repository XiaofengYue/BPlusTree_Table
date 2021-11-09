//
// Created by yxf on 2021/11/8.
//
#include "CLTableManager.h"
#ifndef LINUX_HW_CLEXECUTIVEFUNCTIONSEARCH_H
#define LINUX_HW_CLEXECUTIVEFUNCTIONSEARCH_H

class CLExecutiveFunctionSearch:public CLExecutiveFunctionProvider{
public:

    CLExecutiveFunctionSearch(int col, int left,int right){
        m_left=left;
        m_right=right;
        m_col=col;
    }
    virtual ~CLExecutiveFunctionSearch(){}
    virtual void RunExecutiveFunction(){
        CLTableManager* manager = CLTableManager::GetInstance();
        manager->Search(m_col, m_left, m_right);
    }

private:
    //查询信息
    int m_left;
    int m_right;
    int m_col;
};


#endif //LINUX_HW_CLEXECUTIVEFUNCTIONSEARCH_H
