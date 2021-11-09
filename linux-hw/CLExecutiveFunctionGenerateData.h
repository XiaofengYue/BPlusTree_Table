//
// Created by yxf on 2021/11/8.
//
#include "CLTableManager.h"
#ifndef LINUX_HW_CLEXECUTIVEFUNCTIONGENERATEDATA_H
#define LINUX_HW_CLEXECUTIVEFUNCTIONGENERATEDATA_H

class CLExecutiveFunctionGenerateData: public CLExecutiveFunctionProvider {
public:
    CLExecutiveFunctionGenerateData(int length) {
        m_length = length;
    }

    virtual ~CLExecutiveFunctionGenerateData() {}

    virtual void RunExecutiveFunction() {
        CLTableManager* manager = CLTableManager::GetInstance();
        manager->GenerateRandomData(m_length);
    }

private:
    int m_length;
};

#endif //LINUX_HW_CLEXECUTIVEFUNCTIONGENERATEDATA_H
