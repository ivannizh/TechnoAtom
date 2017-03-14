#include <iostream>
#include <gtest/gtest.h>

#include "myvector.h"

using namespace std;

TEST(vector, test){
    MyVector<int> vec;
    ASSERT_EQ(0, vec.size());
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    ASSERT_EQ(3, vec.size());
    ASSERT_EQ(3, vec.back());

    MyVector<int> vec2(vec);
    ASSERT_EQ(3, vec2.size());
    ASSERT_EQ(3, vec2.back());
    vec2.push_back(4);

    vec = vec2;

    ASSERT_EQ(4, vec.size());
}

TEST (vector, iterator) {
    MyVector<int> vec, vec2;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    vec2 = vec;

    ASSERT_EQ(*vec.begin(), *vec2.begin());
    ASSERT_EQ(*(vec.end()-1), *(vec2.end()-1));
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS( );
}
