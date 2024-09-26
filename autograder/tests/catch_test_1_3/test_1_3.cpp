//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "warehouse.h"
using namespace std;

static void test_1_3() {
  storage_system::Warehouse<storage_system::BostonDynamicsRobot, 5, 3> almacen;
  
  // Verifica que todas las celdas están vacías al inicializar el almacén
  std::cout << std::boolalpha;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cout << (almacen(i, j) == nullptr) << std::endl;
    }
  }
}

TEST_CASE("Question #1.3") {
    execute_test("test_1_3.in", test_1_3);
}