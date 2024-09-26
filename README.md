# Task #PC1: Practica Calificada 1  
**course:** Programación III  
**unit:** 1 y 2  
**cmake project:** prog3_pc1_TEO1_v2024_2
## Indicaciones Específicas
- El tiempo límite para la evaluación es 100 minutos.
- Cada pregunta deberá ser respondida en un archivo cabecera (`.h`) con el número de la pregunta:
    - `warehouse.h`
    - `shift_right.h`
- Deberás subir estos archivos directamente a [www.gradescope.com](https://www.gradescope.com) o se puede crear un `.zip` que contenga todos ellos y subirlo.

## Question #1 - {Clase, Template de Clase y Polimorfismo} (13 points)

Un almacén robotizado utiliza diferentes tipos de robots para realizar tareas de carga y clasificación de productos. El almacén está dividido en secciones, y cada sección puede contener uno o más robots que realizan tareas específicas. Los robots provienen de proveedores como BostonDynamics o KUKA, y el almacén debe configurarse para utilizar robots de diferentes proveedores y tamaños de almacenamiento.

Diseña e implementa la clase template `Warehouse` dentro del namespace `storage_system`, que permita almacenar de manera dinámica diferentes tipos de robots (por ejemplo, punteros a objetos de una clase base `BostonDynamicsRobot`). El almacén debe permitir definir su tamaño utilizando dos parámetros de template no-tipo `rows` y `cols`, que representarán el número de filas y columnas del almacén respectivamente.

Los robots, además de moverse, pueden realizar tareas específicas como cargar productos o clasificar objetos. El método `move_robot` no solo debe mover el robot de una celda a otra, sino que también debe ejecutar el método `do_task` correspondiente al robot después del movimiento.

Requerimientos adicionales:
Clase `Warehouse`:
- La clase `Warehouse` debe almacenar punteros a objetos `BostonDynamicsRobot` (u otros proveedores) de manera dinámica en cada celda.
- Implementa la función template `place_robot(int i, int j, Args&&... args)` que permita crear un robot del tipo `T` en la celda `(i, j)`, pasando los parámetros necesarios al constructor del robot.
- Implementa el método `move_robot(int i1, int j1, int i2, int j2)` que permita mover robots de una posición a otra. Este método también debe invocar el método `do_task` del robot después de que se haya movido.
- Sobrecarga el operador `()` para acceder a las celdas del almacén.
- Sobrecarga el operador `<<` para facilitar la impresión del estado del almacén.
- Gestiona de manera correcta la destrucción de los robots, liberando la memoria dinámica utilizada cuando ya no se necesiten.

Diferentes proveedores de robots:
- El almacén debe ser configurable con diferentes proveedores de robots, como **BostonDynamics** y **KUKA**. Cada proveedor tiene su propio conjunto de robots, que pueden tener diferentes características y constructores.

Ejemplo de proveedores:
- **BostonDynamics**: Robots más avanzados, con mayor agilidad y adaptabilidad.
- **KUKA**: Robots industriales con gran capacidad de carga, más enfocados en precisión y fuerza.

Clases derivadas de `BostonDynamicsRobot`:
- Clase `BostonDynamicsRobotCarga`: Maneja tareas de carga y descarga de productos.
  - Constructor: `BostonDynamicsRobotCarga(char symbol, int capacity, int speed)`
  - Método: `void do_task()` que simula la tarea de carga de productos.
- Clase `BostonDynamicsRobotClassification`: Clasifica productos según sus características.
  - Constructor: `BostonDynamicsRobotClassification(char symbol, int capacity)`
  - Método: `void do_task()` que simula la tarea de clasificación de productos.


**Método `place_robot`**
```cpp
  template <typename U, typename ...Args>
  T* place_robot(int i, int j, Args... args) {
    // Completar para que crea el robot correctamente y lo ubique correctamente en el almacen
  }    
```

**Método `mover_robot`**
```cpp
    std::pair<bool, T*> move_robot(size_t i1, size_t j1, size_t i2, size_t j2) {
      if (grid[rows*i1 + j1] == nullptr) return {false, nullptr};

      if (i1 >= 0 && i1 < rows && j1 >= 0 && j1 < cols &&
          i2 >= 0 && i2 < rows && j2 >= 0 && j2 < cols) {
        swap(grid[cols*i1 + j1], grid[cols*i2 + j2]);
        delete grid[cols*i1 + j1];
        grid[cols*i1 + j1] = nullptr;
        grid[cols*i2 + j2]->do_task();
        return {true, grid[cols*i2 + j2]};
      }
      return {false, nullptr};
    }
```

**Completar la clase Base, las clases derivada, la relación de herencia, constructores, métodos gets y clone donde corresponda.** 
```cpp
  class BostonDynamicsRobotCarga  {
  private:
      int speed;
  public:
      void do_task() override {
          std::cout << "Robot de carga moviendo productos.\n";
      }
      BostonDynamicsRobot* clone() override { return new BostonDynamicsRobotCarga(symbol, capacity, speed); }
  };
  
  class BostonDynamicsRobotClassification {
  public:
      void do_task() override {
          std::cout << "Robot de clasificación clasificando productos.\n";
      }
      BostonDynamicsRobot* clone() override { return new BostonDynamicsRobotClassification(symbol, capacity); }
  };
```
**Use Case #1:**
```cpp
#include <cassert>
#include "warehouse.h"

void test_creacion_robots() {
    storage_system::Warehouse<BostonDynamicsRobot, 5, 3> almacen;

    // Colocar un robot de carga en la celda (0, 0)
    almacen.place_robot<BostonDynamicsRobotCarga>(0, 0, 'C', 100, 5);
    assert(almacen(0, 0) != nullptr);  // Verifica que la celda no esté vacía
    assert(almacen(0, 0)->get_symbol() == 'C');  // Verifica que el robot es el correcto

    // Colocar un robot de clasificación en la celda (1, 1)
    almacen.place_robot<BostonDynamicsRobotClassification>(1, 1, 'S', 50);
    assert(almacen(1, 1) != nullptr);  // Verifica que la celda no esté vacía
    assert(almacen(1, 1)->get_symbol() == 'S');  // Verifica que el robot es el correcto

    std::cout << "Prueba de creación de robots exitosa." << std::endl;
}
```

**Use Case #2:**
```cpp
#include <cassert>
#include "warehouse.h"

void test_movimiento_y_tarea() {
    storage_system::Warehouse<BostonDynamicsRobot, 5, 3> almacen;

    // Colocar un robot de carga en la celda (0, 0)
    almacen.place_robot<BostonDynamicsRobotCarga>(0, 0, 'C', 100, 5);
    assert(almacen(0, 0) != nullptr);

    // Mover el robot de carga a la celda (2, 2)
    auto resultado = almacen.move_robot(0, 0, 2, 2);
    assert(resultado.first == true);  // Verifica que el movimiento fue exitoso
    assert(almacen(0, 0) == nullptr);  // Verifica que la celda original está vacía
    assert(almacen(2, 2) != nullptr);  // Verifica que el robot está en la nueva celda

    std::cout << "Prueba de movimiento y tarea exitosa." << std::endl;
}
```

**Use Case #3:**
```cpp
#include <cassert>
#include "warehouse.h"

void test_inicializacion_almacen() {
    storage_system::Warehouse<BostonDynamicsRobot, 5, 3> almacen;

    // Verifica que todas las celdas están vacías al inicializar el almacén
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 3; ++j) {
            assert(almacen(i, j) == nullptr);
        }
    }

    std::cout << "Prueba de inicialización del almacén exitosa." << std::endl;
}
```

**Use Case #4:**
```cpp
#include <cassert>
#include "warehouse.h"

void test_impresion_almacen() {
    storage_system::Warehouse<BostonDynamicsRobot, 5, 3> almacen;

    // Colocar algunos robots
    almacen.place_robot<BostonDynamicsRobotCarga>(0, 0, 'C', 100, 5);
    almacen.place_robot<BostonDynamicsRobotClassification>(1, 1, 'S', 50);

    // Imprimir el estado del almacén
    std::cout << almacen << std::endl;  // Debería imprimir el almacén correctamente

    std::cout << "Prueba de impresión del almacén exitosa." << std::endl;
}
```

**Use Case #5:**
```cpp
#include <cassert>
#include "warehouse.h"

void test_movimiento_invalido() {
    storage_system::Warehouse<BostonDynamicsRobot, 5, 3> almacen;

    // Colocar un robot en la celda (0, 0)
    almacen.place_robot<BostonDynamicsRobotCarga>(0, 0, 'C', 100, 5);
    assert(almacen(0, 0) != nullptr);

    // Intentar mover a una celda fuera de los límites
    auto resultado1 = almacen.move_robot(0, 0, 6, 6);
    assert(resultado1.first == false);  // Verifica que el movimiento es inválido

    // Colocar otro robot en la celda (2, 2)
    almacen.place_robot<BostonDynamicsRobotClassification>(2, 2, 'S', 50);
    assert(almacen(2, 2) != nullptr);

    // Intentar mover a una celda ocupada
    auto resultado2 = almacen.move_robot(0, 0, 2, 2);
    assert(resultado2.first == false);  // Verifica que el movimiento es inválido

    std::cout << "Prueba de movimiento inválido exitosa." << std::endl;
}
```

## Question #2 - {template de funciones} (7 points)

Implementa una función plantilla llamada `shift_right` que acepte un contenedor como parámetro (puede ser un `std::array`, `std::vector` o un arreglo normal de C++). La función debe desplazar todos los elementos del contenedor hacia la derecha un número determinado de posiciones, y los elementos que sobrepasen el final deben reaparecer al inicio del contenedor.

Requisitos:
- La función debe ser genérica y funcionar con cualquier tipo de contenedor como arreglos, `std::array`, `std::vector`.
- La función debe aceptar dos parámetros:
  - El contenedor a modificar.
  - El número de posiciones a desplazar.
- Debes asegurarte de que el número de desplazamientos sea menor o igual al tamaño del contenedor (puedes utilizar el módulo).
- No uses `std::rotate` o funciones similares de la STL para resolver el problema.  

**Use Case #1:**
```cpp
#include <vector>

void test_shift_vector() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    shift_right(vec, 2);
    for (const auto& item: vec) std::cout << item << " "; // 4 5 1 2 3 
}
```

**Use Case #2:**
```cpp
#include <array>

void test_shift_array() {
    std::array<int, 4> arr = {10, 20, 30, 40};
    shift_right(arr, 1);
    for (const auto& item: arr) std::cout << item << " "; // 40 10 20 30 
}
```

**Use Case #3:**
```cpp

void test_shift_array_different_types() {
    double arr[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    shift_right(arr, 3);
    for (const auto& item: arr) std::cout << item << " "; // 3.3 4.4 5.5 1.1 2.2
}
```

**Use Case #4:**
```cpp
#include <string>

void test_shift_string() {
  std::string str = "abcdef";
  shift_right(str, 2);
  std::cout << str; // efabcd
}
```