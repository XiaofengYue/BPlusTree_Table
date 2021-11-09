//
// Created by yxf on 2021/11/7.
//
#include "struct.h"
#include <malloc.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#ifndef LINUX_HW_CLBPLUSTREE_H
#define LINUX_HW_CLBPLUSTREE_H


class CLBPlusTree {

public:
    BPlusTreeNode* Create_BPlusTreeNode();
    BPlusTreeNode* Create_BPlusTree();

    //索引插入
    void Insert_BPlusTreeNode(BPlusTreeNode* root, const Record& record, int col);
    void Insert_BPlusTreeNode_NotFull(BPlusTreeNode* node, const NumNode& num_node);
    void Insert_NumNode(BPlusTreeNode* root, const NumNode& num_node);

    //区域搜索 在索引上 值在[left,right]的行
    void Search_NumRange(BPlusTreeNode* root, int left, int right);

    //保存B+树、对应的某列
    void writeBPlusTree(BPlusTreeNode* root, int col);
    void WriteBPlusTreeNode(int &fd, BPlusTreeNode *node);

    //读取B+树
    BPlusTreeNode *ReadBPlusTree(int col);

    //读取B+树节点
    BPlusTreeNode *ReadBPlusTreeNode(int &fd,BPlusTreeNode* &leaf_node_pre);

};


#endif //LINUX_HW_CLBPLUSTREE_H
