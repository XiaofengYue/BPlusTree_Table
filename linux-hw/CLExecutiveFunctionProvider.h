//
// Created by yxf on 2021/11/5.
//

#ifndef LINUX_HW_CLEXECUTIVEFUNCTIONPROVIDER_H
#define LINUX_HW_CLEXECUTIVEFUNCTIONPROVIDER_H
class CLExecutiveFunctionProvider{
public:
    CLExecutiveFunctionProvider(){}
    virtual ~CLExecutiveFunctionProvider(){}

public:
    virtual void RunExecutiveFunction() = 0;
};
#endif //LINUX_HW_CLEXECUTIVEFUNCTIONPROVIDER_H
