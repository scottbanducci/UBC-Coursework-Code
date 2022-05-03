#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "deque.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("deque::push + popR","[weight=1]"){
    Deque<int> myDeque;
    vector<int> result;
    vector<int> expected;
    

    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        myDeque.pushR(i);
    }
    while (!myDeque.isEmpty()) {
        result.push_back(myDeque.popR());
    }
    REQUIRE( result == expected);
}
TEST_CASE("queue::push + popL","[weight=1]"){
    Deque<int> myDeque;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        myDeque.pushR(i);
    }
    while (!myDeque.isEmpty()) {
        result.push_back(myDeque.popL());
    }
    REQUIRE( result == expected);
}
TEST_CASE("queue::push general test 1", "[weight = 1]"){
    Deque<int> myDeque;
    vector<int> result;
    vector<int> expected;
    myDeque.pushR(1);
    myDeque.pushR(3);
    myDeque.pushR(4);
    myDeque.pushR(2);
    REQUIRE( 2 == myDeque.peekR());
    REQUIRE( 1 == myDeque.peekL());
    result.push_back(myDeque.popL());
    result.push_back(myDeque.popR());
    result.push_back(myDeque.popL());
    result.push_back(myDeque.popL());

    for(int i = 1; i<=4 ; i++){
        expected.push_back(i);
    }
    REQUIRE( result == expected);

    myDeque.pushR(5);
    REQUIRE(5 == myDeque.popL());
}
TEST_CASE("queue::isEmpy", "[weight=1]"){
    Deque<int> myDeque;
    myDeque.pushR(3);
    myDeque.popR();
    REQUIRE(myDeque.isEmpty());
}