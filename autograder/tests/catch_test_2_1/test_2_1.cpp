//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "shift_right.h"
#include <vector>
using namespace std;

static void test_2_1() {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  shift_right(vec, 2);
  for (const auto& item: vec) std::cout << item << " "; // 4 5 1 2 3
}

TEST_CASE("Question #2.1") {
    execute_test("test_2_1.in", test_2_1);
}