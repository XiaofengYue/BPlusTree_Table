//
// Created by yxf on 2021/11/5.
//

#ifndef LINUX_HW_STRUCT_H
#define LINUX_HW_STRUCT_H

#include <cstdint>

#define FILE_NAME "Tables.dat" // 文件名称
#define TABLE_ATTRIBUTES 100 //单条记录一共100个属性
#define TABLE_RECORD_SIZE (sizeof(int64_t)*(TABLE_ATTRIBUTES))//每条记录大小
#define TABLE_MAX_RECORDS 1000000

#define TREE_ORDER  3 //定义B+树的阶数


// 表的记录项
typedef struct Record
{
    int64_t id; //主键
    int64_t attributes[TABLE_ATTRIBUTES]; //100个属性 (int64_t 8字节)
}Record;
// B+树所存的数据项
typedef struct NumNode
{
    int64_t num;
    int64_t primary_key;
}NumNode;
// B+树节点的结构
typedef struct BPlusTreeNode
{
    bool is_leaf;
    struct BPlusTreeNode* next;
    struct BPlusTreeNode* pre;//方便建立向后的连接
    struct BPlusTreeNode* childs[TREE_ORDER];
    int num; //记录当前使用了多少
    NumNode num_node[TREE_ORDER+1];
}BPlusTreeNode;

#endif //LINUX_HW_STRUCT_H
