#include <iostream>
#include "CLTableManager.h"
#include "CLThread.h"
#include "CLBPlusTree.h"
#include "CLExecutiveFunctionInsert.h"
#include "CLExecutiveFunctionProvider.h"
#include "CLExecutiveFunctionGenerateData.h"
#include "CLExecutiveFunctionSearch.h"
// 插入数据
void run_insert_test()
{
    std::cout<<"==================插入数据====================="<<std::endl;
    CLExecutiveFunctionProvider* Insert = new CLExecutiveFunctionInsert();
    CLExecutive *thread = new CLThread(Insert);
    thread->Run();
    thread->WaitForDeath();
}
// 生成随机数据、默认生成10条
void run_generate_data_test(int length)
{
    std::cout<<"==================生成随机数据====================="<<std::endl;
    CLExecutiveFunctionProvider* Generate = new CLExecutiveFunctionGenerateData(length);
    CLExecutive * thread = new CLThread(Generate);
    thread->Run();
    thread->WaitForDeath();
}
// 区域搜索数据
void run_search_test(int col, int left, int right)
{
    std::cout<<"==================区域搜索数据====================="<<std::endl;
    CLExecutiveFunctionProvider* Search = new CLExecutiveFunctionSearch(col, left, right);
    CLExecutive * thread = new CLThread(Search);
    thread->Run();
    thread->WaitForDeath();
}
void run_load_b_plus_tree_search(int col, int left, int right)
{
    std::cout<<"==================区域搜索数据====================="<<std::endl;
    CLExecutiveFunctionProvider* Search = new CLExecutiveFunctionSearch(col, left, right);
    CLExecutive * thread = new CLThread(Search);
    thread->Run();
    thread->WaitForDeath();
}

void create_b_plus_tree(int length, int col, int left, int right)
{
    CLExecutiveFunctionProvider* Generate = new CLExecutiveFunctionGenerateData(length);
    CLExecutive * thread1 = new CLThread(Generate);
    thread1->Run();
    thread1->WaitForDeath();
    CLExecutiveFunctionProvider* Search = new CLExecutiveFunctionSearch(col, left, right);
    CLExecutive * thread = new CLThread(Search);
    thread->Run();
    thread->WaitForDeath();
}

int main() {
    CLTableManager* manager = CLTableManager::GetInstance();

    //test 1 随机生成数据
    std::cout<<"==================测试随机生成数据====================="<<std::endl;
    run_generate_data_test(10);
    manager->Display(10);
    
    //test 2 测试插入数据
    // std::cout<<"==================测试插入数据====================="<<std::endl;
    // run_insert_test();
    // manager->Display(11);

    //test 3 测试区域搜索数据
    // manager->Display(11);
    // std::cout<<"==================测试区域搜索数据====================="<<std::endl;
    // run_search_test(0, 0, 1000);

    //test 4 测试加载B+树区域搜索数据
    // manager->Display(11);
    // std::cout<<"==================测试加载B+树区域搜索数据====================="<<std::endl;
    // run_load_b_plus_tree_search(0, 0, 1000);

    //test 5 测试生成B+树区域搜索数据
    // std::cout<<"==================测试生成B+树区域搜索数据====================="<<std::endl;
    // create_b_plus_tree(20, 0, 0, 1000);
    // manager->Display(20);

    return 0;
}
