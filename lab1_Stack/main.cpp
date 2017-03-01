#include <iostream>
#include <gtest/gtest.h>

#include "stack.h"


TEST (Stack, PushPop) {
    Stack<int> st;
    ASSERT_EQ(0, st.size());
    ASSERT_NO_THROW(st.pop());
    st.push(1);
    ASSERT_EQ(1, st.size());
    ASSERT_EQ(1, st.top());
    st.push(2);
    st.push(3);
    ASSERT_EQ(3, st.size());
}

TEST (Stack, Copy){
    Stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    Stack<int> st2(st);

    ASSERT_EQ(3, st2.size());

    st.pop();
    st.pop();

    ASSERT_EQ(1, st.size());
    ASSERT_EQ(3, st2.size());
}

TEST (Stack, TopEmpty){
    Stack<int> st;

    ASSERT_TRUE(st.empty());

    st.push(1);
    st.push(2);
    st.push(3);

    ASSERT_FALSE(st.empty());

    ASSERT_EQ(3, st.size());

    ASSERT_EQ(3, st.top());
    st.pop();
    ASSERT_EQ(2, st.top());
    st.pop();
    ASSERT_EQ(1, st.top());
    st.pop();
    ASSERT_ANY_THROW(st.top());
}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS( );
}
