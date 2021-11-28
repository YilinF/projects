// Project UID c1f28c309e55405daf00c565d57ff9ad
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <utility>
#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_list_cpy_ctor) {
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    List<int> copy_list = test_list;
    ASSERT_TRUE(copy_list.size() == 3);
}

TEST(test_list_empty) {
    List<int> empty;
    ASSERT_TRUE(empty.empty());
    empty.push_front(1);
    ASSERT_FALSE(empty.empty());
}

TEST(test_list_size) {
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    ASSERT_TRUE(test_list.size() == 3);
    List<int> empty;
    ASSERT_TRUE(empty.size() == 0);
}

TEST(test_list_front) {
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    ASSERT_TRUE(test_list.front() == 1);
    List<int> test_list2;
    test_list2.push_front(2);
    ASSERT_TRUE(test_list2.front() == 2);
}

TEST(test_list_back) {
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    ASSERT_TRUE(test_list.back() == 3);
    List<int> test_list2;
    test_list2.push_front(2);
    ASSERT_TRUE(test_list2.back() == 2);
}

TEST(test_list_push_front) {
    List<int> empty_list;
    int datum1 = 1;
    empty_list.push_front(datum1);
    ASSERT_FALSE(empty_list.empty());
}

TEST(test_list_push_front2) {
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_front(2);
    test_list.push_front(3);
    test_list.push_front(4);
    test_list.push_front(5);
    ASSERT_TRUE(test_list.front() == 5);
}

TEST(test_size) {
    List<int>::Iterator it;
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    ASSERT_EQUAL(test_list.size(), 3);
}

TEST(test_begin) {
    List<int>::Iterator it;
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    ASSERT_EQUAL(test_list.front(), 1);
}

TEST(test_list_push_back) {
    List<int> empty_list;
    empty_list.push_back(2);
    ASSERT_FALSE(empty_list.empty());
}

TEST(test_list_push_back2) {
    List<int> test_list;
    test_list.push_back(1);
    test_list.push_back(2);
    test_list.push_back(3);
    test_list.push_back(4);
    test_list.push_back(5);
    ASSERT_TRUE(test_list.back() == 5);
}

TEST(test_list_pop_front) {
    List<int> list;
    int datum = 5;
    list.push_front(0);
    list.pop_front();
    list.push_back(datum);
    list.push_back(datum);
    list.pop_front();
}

TEST(test_list_pop_back) {
    List<int> list;
    int datum = 99;
    list.push_front(2000);
    list.pop_back();
    ASSERT_TRUE(list.empty());
    list.push_back(datum);
    list.push_back(-5);
    list.pop_back();
}

TEST(test_clear1) {
    List<int> empty_list;
    empty_list.clear();
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_clear2) {
    List<int> list;
    int datum = 99;
    list.push_back(datum);
    list.push_front(2000);
    list.push_back(-5);
    list.clear();
    ASSERT_TRUE(list.empty());
}

TEST(test_copy_ctor1) {
    List<int> empty_list;
    List<int> copy_list = empty_list;
    ASSERT_TRUE(copy_list.empty());
}

TEST(test_copy_ctor2) {
    List<int> list;
    int datum = 99;
    list.push_back(2000);
    list.push_front(datum);
    list.push_front(-5);
    List<int> copy_list = list;
    ASSERT_FALSE(copy_list.empty());
}

TEST(test_it_dec_op) {
    List<int>::Iterator it;
    List<int> test_list;
    test_list.push_front(1);
    it = test_list.begin();
    --it;
    ASSERT_TRUE(it == --test_list.begin());
}

TEST(test_it_dec_op_2) {
    List<int>::Iterator it;
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    it = test_list.begin();
    ++it;
    ++it;
    --it;
    ASSERT_TRUE(*it == 2);
}

TEST(test_it_inc_op) {
    List<int>::Iterator it;
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    it = test_list.begin();
    ++it;
    ASSERT_TRUE(*it == 2);
}

TEST(test_it_inc_op_2) {
    List<int>::Iterator it;
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    it = test_list.begin();
    ++it;
    ++it;
    ASSERT_TRUE(*it == 3);
}

TEST(test_it_equal_op) {
    List<int>::Iterator it;
    List<int>::Iterator it2;
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    
    it = test_list.begin();
    it2 = test_list.begin();
    
    ASSERT_TRUE(it == it2);
}

TEST(test_it_notequal_op) {
    List<int>::Iterator it;
    List<int>::Iterator it2;
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    
    it = test_list.begin();
    it2 = test_list.end();
    
    ASSERT_TRUE(it != it2);
}

TEST(test_star_op) {
    List<int>::Iterator it;
    List<int> test_list;
    test_list.push_front(1);
    test_list.push_back(2);
    test_list.push_back(3);
    it = test_list.begin();
    ASSERT_EQUAL(*it, 1);
}

//TEST(test_erase1) {
//    List<int> list;
//    list.push_back(2000);
//    list.push_front(0);
//    list.push_front(-5);
//    List<int>::Iterator it = list.begin();
//    list.erase(it);
//    ++it;
//    list.erase(it);
//}

TEST(test_erase2) {
    List<int> list;
    list.push_back(2000);
    List<int>::Iterator it = list.begin();
    list.erase(it);
    ASSERT_TRUE(list.empty());
}

TEST(test_insert1) {
    List<int> list;
    list.push_back(2000);
    List<int>::Iterator it = list.begin();
    list.insert(it, 3);
}

TEST(test_insert2) {
    List<int> list;
    List<int>::Iterator it = list.begin();
    list.insert(it, -99);
}

TEST(test_insert3) {
    List<int> list;
    list.push_back(2000);
    list.push_front(0);
    list.push_front(-5);
    List<int>::Iterator it = list.begin();
    ++it;
    ++it;
    list.insert(it, 3);
    list.size();
}

TEST(test_self_assigment) {
    List<int> list;
    list.push_back(5);
    list.push_back(-12);
    list.push_back(6);
    list.push_back(88);
    list = list;
    List<int>::Iterator iter = list.begin();
    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE(*list.begin() == 5);
    ++iter;
    ASSERT_TRUE(*iter == -12);
    ++iter;
    ASSERT_TRUE(*iter == 6);
    ++iter;
    ASSERT_TRUE(*iter == 88);
}

TEST(test_insert_at_end) {
    List<int> list_1;
    list_1.push_front(-5);
    list_1.push_front(22);
    list_1.push_front(0);
    list_1.push_front(190);
    list_1.push_back(37);

    List<int> list_2;
    list_2.push_front(-5);
    list_2.push_front(22);
    list_2.push_front(0);
    list_2.push_front(190);
    
    List<int>::Iterator iter_3 = list_1.begin();
    List<int>::Iterator iter_1 = list_2.end();
    List<int>::Iterator iter_2 = list_2.begin();

    list_2.insert(iter_1, 37);

    for (; iter_3 != list_2.end(); ++iter_3) {
        ASSERT_EQUAL(*iter_3 ,*iter_2) ;
        ++iter_2;
    }
}

//TEST(copy_all){
//    List<int> list;
//    list.push_back(0);
//    list.push_back(-99);
//
//    List<int> copy_list(list);
//
//    List<int>::Iterator it = list.begin();
//
//      for (List<int>::Iterator i = copy_list.begin(); i != copy_list.end(); ++i){
//            ASSERT_EQUAL(*i ,*it) ;
//            ++it;
//      }
//}

TEST(test_double) {
    List<double> test_list;
    test_list.push_back(-0.6);
    test_list.push_back(2.4);
    test_list.push_back(99.777);
    ASSERT_TRUE(test_list.size() == 3);
}

//TEST(test_list_copy_ctor) {
//    List<int> first_list;
//    first_list.push_front(1);
//    first_list.push_back(2);
//    first_list.push_back(3);
//    first_list.push_back(4);
//    List<int> copy_list = first_list;
//    copy_list.clear();
//    ASSERT_TRUE(copy_list.empty());
//}
//
//TEST(test_copy_all) {
//    List<int> first_list;
//    first_list.push_front(1);
//    first_list.push_back(2);
//    first_list.push_back(3);
//    first_list.push_back(4);
//    List<int> copy_list = first_list;
//}
TEST_MAIN()
