using namespace std;
#include <iostream>
struct Nodo {
  string nombre = "";
  int habitacion = -1;
  Nodo *prev = nullptr;
  Nodo *next = nullptr;
};