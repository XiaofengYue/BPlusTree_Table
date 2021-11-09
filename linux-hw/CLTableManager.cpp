//
// Created by yxf on 2021/11/5.
//

#include "CLTableManager.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>


//实例对象
CLTableManager* CLTableManager::m_pManager = 0;
pthread_mutex_t *CLTableManager::m_pCreateManager = CLTableManager::InitializeMutex();

pthread_mutex_t *CLTableManager::InitializeMutex()
{
    pthread_mutex_t *p = new pthread_mutex_t;
    if(pthread_mutex_init(p, 0)!=0)
    {
        delete p;
        return 0;
    }
    return p;
}
CLTableManager::CLTableManager()
{
    m_Fd = open(FILE_NAME, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

    // 初始化表
    m_pTable = new Record[TABLE_MAX_RECORDS];
    // 加载数据
    LoadTable();
    // 设置随机数种子
    srand((unsigned)time(NULL));
    // 初始化互斥量
    m_pMutexForTable = new pthread_mutex_t ;
    if(pthread_mutex_init(m_pMutexForTable, 0)!=0)
    {
        delete m_pMutexForTable;
        close(m_Fd);
    }
}

//单例模式 获得实例
CLTableManager* CLTableManager::GetInstance()
{
    if(m_pManager != 0)
    {
        return m_pManager;
    }
    if (pthread_mutex_lock(m_pCreateManager) != 0)
    {
        return 0;
    }
    if(m_pManager == 0)
    {
        m_pManager = new CLTableManager;
    }
    if(pthread_mutex_unlock(m_pCreateManager)!=0)
    {
        return 0;
    }
    return m_pManager;
}

//lseek末尾、末尾插入数据。
void CLTableManager::InsertData()
{
    pthread_mutex_lock(m_pMutexForTable); //加锁

    lseek(m_Fd, 0, SEEK_END);
    Record p;
    p.id = record_num;
    for(int i = 0; i < TABLE_ATTRIBUTES; i++){
        p.attributes[i] = (rand() % 2000) + 1;
    }
    m_pTable[record_num++] = p;
    // 写入 互斥写。后面注意改正
    write(m_Fd, (char*)&p.attributes, TABLE_RECORD_SIZE);
    std::cout<<"插入数据--成功--属性0的值为："<<p.attributes[0]<<std::endl;

    pthread_mutex_unlock(m_pMutexForTable);// 解锁

}

//加载已经存在的表
void CLTableManager::LoadTable()
{
    Record p;
    //从头开始读取
    lseek(m_Fd, 0, SEEK_SET);
    while(read(m_Fd,(char*)&p.attributes, sizeof(p.attributes)))
    {
        p.id = record_num;
        m_pTable[record_num++] = p;
    }
}

// 生成随机数据
void CLTableManager::GenerateRandomData(int64_t length)
{
    std::cout<<"准备生成随机数据，长度为："<<length<<std::endl;
    if(access(FILE_NAME, F_OK) == 0){
        std::cout<<"生成随机数据--删除原数据文件"<<std::endl;
        remove(FILE_NAME);
        std::cout<<"生成随机数据--删除原数据文件--删除成功"<<std::endl;
    }
    m_Fd = open(FILE_NAME, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    record_num = 0;
    std::cout<<"生成随机数据--随机生成数据"<<std::endl;
    lseek(m_Fd, 0, SEEK_SET); //游标指向0重新开始写
    for (int i = 0; i < length; i++)
    {
        m_pManager->InsertData();
    }
    std::cout<<"生成随机数据--随机生成数据--生成成功"<<std::endl;

    char index_file_path[20];
    for(int col = 0 ; col < TABLE_ATTRIBUTES; col ++ ){
        sprintf(index_file_path, "%s%d", "index_", col);
        //删除原来的索引文件
        if (access(index_file_path, F_OK) == 0) {
            if (remove(index_file_path ) == -1) {
                std::cout << "删除失败";
                throw "In BPlusTree::WriteBPlusTree(),remove error";
            }
        }
    }
}

//展示数据
void CLTableManager::Display(int length)
{
    std::cout<<"==================SHOW====================="<<std::endl;
    for(int i = 0 ; i < length; i++)
    {
        std::cout<<"属性0的值为："<<m_pTable[i].attributes[0]<<std::endl;
    }
}

BPlusTreeNode* CLTableManager::Create_index(int col)
{
    std::cout<<"尝试加载索引，col为："<<col<<std::endl;
    CLBPlusTree* tree;
    BPlusTreeNode* root;
    root = tree->ReadBPlusTree(col);
    if(root == NULL){
        root = tree->Create_BPlusTree();
        //预防最大数字插入产生的复杂操作、人为的加入最大的数值
        Record r;
        r.id = -1;
        for(int i = 0 ; i< TABLE_ATTRIBUTES; i++) {
            r.attributes[i] = 2000;
        }
        tree->Insert_BPlusTreeNode(root, r, col);
        for(int i = 0 ; i < record_num ; i++)
        {
            tree->Insert_BPlusTreeNode(root, m_pTable[i], col);
        }
        std::cout<<"索引建立成功"<<std::endl;
        tree->writeBPlusTree(root, col);
    }
    return root;
}

//区域搜索
void CLTableManager::Search(int col, int left, int right) {
    std::cout<<"搜索中，属性："<<col<<"区间最小值："<<left<<"区间最大值为："<<right<<std::endl;
    CLBPlusTree* tree;
    //在col列属性建立索引
    BPlusTreeNode* root = Create_index(col);
    tree->Search_NumRange(root, left,right);

}