//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "shift_right.h"
#include <array>
using namespace std;

static void test_2_2() {
  std::array<int, 4> arr = {10, 20, 30, 40};
  shift_right(arr, 1);
  for (const auto& item: arr) std::cout << item << " "; // 40 10 20 30
}

TEST_CASE("Question #2.2") {
    execute_test("test_2_2.in", test_2_2);
}