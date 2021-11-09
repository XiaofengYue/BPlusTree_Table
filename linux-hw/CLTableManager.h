//
// Created by yxf on 2021/11/5.
//

#ifndef LINUX_HW_CLTABLEMANAGER_H
#define LINUX_HW_CLTABLEMANAGER_H

#include <pthread.h>
#include "struct.h"
#include "CLBPlusTree.h"

class CLTableManager {
public:
    // 单例
    static CLTableManager* GetInstance();
    // 插入数据
    void InsertData();
    // 生成随机数据
    void GenerateRandomData(int64_t length);
    // 加载表
    void LoadTable();
    //展示数据
    void Display(int length);

    //创建索引
    BPlusTreeNode* Create_index(int col);
    // 搜索功能 属性attr位于[left, right]的数据
    void Search(int col, int left, int right);



private:

    CLTableManager(const CLTableManager&);
    CLTableManager& operator=(const CLTableManager&);

    CLTableManager();
    ~CLTableManager();

    static pthread_mutex_t *InitializeMutex();//初始化

    // 下列有关索引的操作

private:
    // 文件描述符
    int m_Fd;
    // 类实例
    static CLTableManager *m_pManager;
    // 互斥-建立实例
    static pthread_mutex_t *m_pCreateManager;
    // 互斥-表操作。写
    pthread_mutex_t *m_pMutexForTable;
    // 已有记录数量
    int64_t record_num;
    // 记录组成的表
    Record* m_pTable;
};


#endif //LINUX_HW_CLTABLEMANAGER_H
