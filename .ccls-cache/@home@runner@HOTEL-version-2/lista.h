#include "Nodo.h"
using namespace std;

class lista{
private:
string nombreArchivo="";
string nombre="";
int habitacion=-1;
Nodo* auxiliar=new Nodo();
Nodo* auxiliar2=new Nodo();
Nodo* Nuevo=new Nodo();
Nodo *actual= new Nodo();
Nodo *anterior=new Nodo();

public:
void CargarLista(Nodo *&head,string nombreArchivo);
void ImprimirLista(Nodo *&head);
void borrar(Nodo *&head);
void consultarVecinos(Nodo *&head,int habitacion)

};