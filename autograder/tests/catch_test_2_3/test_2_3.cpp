//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "shift_right.h"
using namespace std;

static void test_2_3() {
  double arr[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
  shift_right(arr, 3);
  for (const auto& item: arr) std::cout << item << " "; // 3.3 4.4 5.5 1.1 2.2
}

TEST_CASE("Question #2.3") {
    execute_test("test_2_3.in", test_2_3);
}