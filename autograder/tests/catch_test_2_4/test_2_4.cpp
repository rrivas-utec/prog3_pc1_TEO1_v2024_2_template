//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "shift_right.h"
#include <string>
using namespace std;

static void test_2_4() {
  std::string str = "abcdef";
  shift_right(str, 2);
  std::cout << str; // efabcd
}

TEST_CASE("Question #2.4") {
    execute_test("test_2_4.in", test_2_4);
}