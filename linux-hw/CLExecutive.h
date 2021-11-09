//
// Created by yxf on 2021/11/5.
//

#ifndef LINUX_HW_CLEXECUTIVE_H
#define LINUX_HW_CLEXECUTIVE_H

#include "CLExecutiveFunctionProvider.h"
class CLExecutive{
public:
    explicit CLExecutive(CLExecutiveFunctionProvider* pExecutiveFunctionProvider){
        m_pExecutiveFunctionProvider = pExecutiveFunctionProvider;
    }
    virtual ~CLExecutive(){}
    virtual void Run() = 0;
    virtual void WaitForDeath() = 0;

protected:
    CLExecutiveFunctionProvider* m_pExecutiveFunctionProvider;
};
#endif //LINUX_HW_CLEXECUTIVE_H
