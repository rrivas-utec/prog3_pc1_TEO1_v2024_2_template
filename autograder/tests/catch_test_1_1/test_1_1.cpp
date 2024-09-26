//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "warehouse.h"
using namespace std;

static void test_1_1() {
  storage_system::Warehouse<storage_system::BostonDynamicsRobot, 5, 3> almacen;
  
  // Colocar un robot de carga en la celda (0, 0)
  almacen.place_robot<storage_system::BostonDynamicsRobotCarga>(0, 0, 'C', 100, 5);
  std::cout << std::boolalpha;
  std::cout << (almacen(0, 0) != nullptr) << std::endl;  // Verifica que la celda no esté vacía
  std::cout << (almacen(0, 0)->get_symbol() == 'C') << std::endl;  // Verifica que el robot es el correcto

  // Colocar un robot de clasificación en la celda (1, 1)
  almacen.place_robot<storage_system::BostonDynamicsRobotClassification>(1, 1, 'S', 50);
  std::cout << (almacen(1, 1) != nullptr) << std::endl;  // Verifica que la celda no esté vacía
  std::cout << (almacen(1, 1)->get_symbol() == 'S') << std::endl;  // Verifica que el robot es el correcto
}

TEST_CASE("Question #1.1") {
    execute_test("test_1_1.in", test_1_1);
}