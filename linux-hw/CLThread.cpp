//
// Created by yxf on 2021/11/5.
//

#include "CLThread.h"

CLThread::CLThread(CLExecutiveFunctionProvider *pExecutiveFunctionProvider): CLExecutive(pExecutiveFunctionProvider) {}

CLThread::~CLThread() noexcept {}

void *CLThread::StartFunctionOfThread(void *pThis) {
    CLThread* pThreadThis = (CLThread*)pThis;
    std::cout<<"线程ID："<<pThreadThis <<std::endl;
    pThreadThis->m_pExecutiveFunctionProvider->RunExecutiveFunction();
    return 0;
}

void CLThread::Run() {
    int r = pthread_create(&m_ThreadID, 0, StartFunctionOfThread, this);
    if(r!=0)
    {
        std::cout<<"Thread create error!!"<<std::endl;
        return ;
    }
}

void CLThread::WaitForDeath() {
    int r = pthread_join(m_ThreadID, 0);
    if(r!=0)
    {
        std::cout<<"Thread death error!!"<<std::endl;
        return ;
    }
}
