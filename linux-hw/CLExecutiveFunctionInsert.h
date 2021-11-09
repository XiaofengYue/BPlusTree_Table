//
// Created by yxf on 2021/11/8.
//
#include "CLTableManager.h"
#ifndef LINUX_HW_CLEXECUTIVEFUNCTIONINSERT_H
#define LINUX_HW_CLEXECUTIVEFUNCTIONINSERT_H

class CLExecutiveFunctionInsert: public CLExecutiveFunctionProvider {
public:
    CLExecutiveFunctionInsert() {}

    virtual ~CLExecutiveFunctionInsert() {}

    virtual void RunExecutiveFunction() {
        CLTableManager* manager = CLTableManager::GetInstance();
        manager->InsertData();
    }
};

#endif //LINUX_HW_CLEXECUTIVEFUNCTIONINSERT_H
