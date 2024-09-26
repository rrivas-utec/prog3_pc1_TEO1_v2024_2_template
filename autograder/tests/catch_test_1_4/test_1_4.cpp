//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "warehouse.h"
using namespace std;

static void test_1_4() {
  storage_system::Warehouse<storage_system::BostonDynamicsRobot, 5, 3> almacen;
  
  // Colocar algunos robots
  almacen.place_robot<storage_system::BostonDynamicsRobotCarga>(0, 0, 'C', 100, 5);
  almacen.place_robot<storage_system::BostonDynamicsRobotClassification>(1, 1, 'S', 50);

  // Imprimir el estado del almacén
  std::cout << almacen << std::endl;  // Debería imprimir el almacén correctamente

}

TEST_CASE("Question #1.4") {
    execute_test("test_1_4.in", test_1_4);
}