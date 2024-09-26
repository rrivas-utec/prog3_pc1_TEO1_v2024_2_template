//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "warehouse.h"
using namespace std;

static void test_1_2() {
  storage_system::Warehouse<storage_system::BostonDynamicsRobot, 5, 3> almacen;
  
  // Colocar un robot de carga en la celda (0, 0)
  almacen.place_robot<storage_system::BostonDynamicsRobotCarga>(0, 0, 'C', 100, 5);
  std::cout << std::boolalpha;
  std::cout << (almacen(0, 0) != nullptr) << std::endl;
  
  // Mover el robot de carga a la celda (2, 2)
  auto [resultado, _] = almacen.move_robot(0, 0, 2, 2);
  std::cout << resultado << std::endl;  // Verifica que el movimiento fue exitoso
  std::cout << (almacen(0, 0) == nullptr) << std::endl;  // Verifica que la celda original está vacía
  std::cout << (almacen(2, 2) != nullptr) << std::endl;  // Verifica que el robot está en la nueva celda
}

TEST_CASE("Question #1.2") {
    execute_test("test_1_2.in", test_1_2);
}