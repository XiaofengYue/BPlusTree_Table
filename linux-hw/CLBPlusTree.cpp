//
// Created by yxf on 2021/11/7.
//

#include "CLBPlusTree.h"


BPlusTreeNode* CLBPlusTree::Create_BPlusTreeNode()
{
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    for(int i = 0; i < TREE_ORDER; i++)
    {
        node->childs[i] = NULL;
        node->num_node[i].num = -1;
    }
    node->is_leaf = true;
    node->num = 0;
    node->next = NULL;
    node->pre = NULL;
    return node;
}

BPlusTreeNode* CLBPlusTree::Create_BPlusTree()
{
    BPlusTreeNode* node = Create_BPlusTreeNode();
    return node;
}

void CLBPlusTree::Insert_BPlusTreeNode(BPlusTreeNode *root, const Record& record, int col)
{
    NumNode num_node;
    num_node.num = record.attributes[col];
    num_node.primary_key = record.id;
    Insert_NumNode(root, num_node);
}

void CLBPlusTree::Insert_BPlusTreeNode_NotFull(BPlusTreeNode *node, const NumNode &num_node)
{
    int pos = node->num;
    while (pos >= 1 && num_node.num < node->num_node[pos - 1].num) {
        node->num_node[pos] = node->num_node[pos - 1];
        pos--;
    }
    node->num_node[pos] = num_node;
    node->num++;
}

void CLBPlusTree::Insert_NumNode(BPlusTreeNode *root, const NumNode &num_node)
{
    //找到叶子节点
    if(root->is_leaf)
    {
        //情况1 节点未满直接插入
        if(root->num < TREE_ORDER)
            Insert_BPlusTreeNode_NotFull(root, num_node);
        else
        {
            //情况2 节点满了分裂插入
            Insert_BPlusTreeNode_NotFull(root, num_node);
            BPlusTreeNode* new_child_1 = Create_BPlusTreeNode();
            BPlusTreeNode* new_child_2 = Create_BPlusTreeNode();
            for(int i = 0 ; i < (TREE_ORDER+1)/2; i++ )
            {
                new_child_1->num_node[i] = root->num_node[i];
                new_child_2->num_node[i] = root->num_node[i + (TREE_ORDER+1)/2];
            }
            new_child_1->num = (TREE_ORDER+1)/2;
            new_child_2->num = (TREE_ORDER+1)/2;
            new_child_2->next = root->next;
            new_child_2->pre = new_child_1;
            if(root->pre)
                root->pre->next = new_child_1;
            new_child_1->next = new_child_2;
            root->childs[0] = new_child_1;
            root->childs[1] = new_child_2;
            root->is_leaf = false;
            root->num = 2;
            root->num_node[0] = new_child_1->num_node[(TREE_ORDER+1)/2 - 1];
            root->num_node[1] = new_child_2->num_node[(TREE_ORDER+1)/2 - 1];
        }
        return;
    }
    // 情况3:不是叶子节点、就往下找
    int i;
    for(i = 0 ; i< root->num ; i++)
    {
        if(root->num_node[i].num > num_node.num)
            break;
    }
    Insert_NumNode(root->childs[i], num_node);
}

void CLBPlusTree::Search_NumRange(BPlusTreeNode *root, int left, int right) {
    if(root->is_leaf)
    {
        bool flag = true;
        while(flag) {
            for (int j = 0; j < root->num; j++) {
                if (root->num_node[j].num >= left && root->num_node[j].num <= right)
                    std::cout << "行：" << root->num_node[j].primary_key << std::endl;
                if(root->num_node[j].num > right)
                    flag = false;
            }
            root = root->next;
        }
        return ;
    }
    int i;
    for(i = 0 ; i< root->num ; i++)
    {
        if(root->num_node[i].num >= left)
            break;
    }
    Search_NumRange(root->childs[i], left, right);
}

void CLBPlusTree::writeBPlusTree(BPlusTreeNode *root, int col) {
    std::cout<<"保存索引col："<<col<<std::endl;
    char index_file_path[20];
    sprintf(index_file_path, "%s%d", "index_", col);
    //删除原来的索引文件
    if (access(index_file_path, F_OK) == 0) {
        if (remove(index_file_path ) == -1) {
            std::cout << "删除失败";
            throw "In BPlusTree::WriteBPlusTree(),remove error";
        }
    }
    int fd = open(index_file_path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
        throw "In BPlusTree::WriteBPlusTree(),open error";
    WriteBPlusTreeNode(fd, root);
    close(fd);
}

//将B+树节点写入文件
void CLBPlusTree::WriteBPlusTreeNode(int &fd, BPlusTreeNode *node) {
    if (node == NULL || fd == -1) {
        return ;
    }
    if (write(fd, node, sizeof(BPlusTreeNode)) == -1)
        throw "In BPlusTree::WriteBPlusTreeNode(),write error";
    for (int i = 0; i < node->num; i++)
        WriteBPlusTreeNode(fd, node->childs[i]);
}

//读取B+树
BPlusTreeNode* CLBPlusTree::ReadBPlusTree(int col) {
    std::cout<<"加载索引col："<<col<<std::endl;
    BPlusTreeNode* leaf_node_pre = NULL; //保存前一个叶节点
    char index_file_path[20];
    sprintf(index_file_path, "%s%d", "index_", col);
    if (access(index_file_path, F_OK) == -1)
        return NULL;
    int fd = open(index_file_path, O_RDONLY, S_IRUSR | S_IWUSR);
    if (fd == -1)
        return NULL;
    BPlusTreeNode *node = ReadBPlusTreeNode(fd, leaf_node_pre);
    close(fd);
    return node;
}

//读取B+树节点
BPlusTreeNode *CLBPlusTree::ReadBPlusTreeNode(int &fd, BPlusTreeNode* &leaf_node_pre) {

    BPlusTreeNode *node = Create_BPlusTreeNode();
    if (node == NULL)
        return NULL;
    if (read(fd, node, sizeof(BPlusTreeNode)) == -1)
        return NULL;
    if (node->is_leaf) {
        if (leaf_node_pre == NULL)
            leaf_node_pre = node;
        else
        {
            leaf_node_pre->next = node;
            leaf_node_pre=node;
        }
        return node;
    }
    for (int i = 0; i < node->num; i++)
        node->childs[i] = ReadBPlusTreeNode(fd,leaf_node_pre);
    return node;
}