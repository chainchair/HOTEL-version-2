#include "lista.h"
#include <fstream>

void lista:: CargarLista(Nodo *&head, string NombreArchivo){
  ifstream archivo(nombreArchivo);
  string dato; //primer dato obtenido del archivo
  int datohabitacion=0;
  if (archivo.is_open()){
  while (getline(archivo, dato)) {
    Nodo *auxiliar= new Nodo(); //creacion del nodo auxiliar  
    Nodo *auxiliar2= new Nodo();
    Nodo *nuevo= new Nodo(); //creacion del nodo nuevo

    
    nuevo->nombre= dato; //guardar nombre en NodoNuevo
    getline(archivo, dato);//obtener segundo dato
    datohabitacion=stoi(dato);
    nuevo->habitacion = datohabitacion; //guardar habitacion en NodoNuevo
    auxiliar = head; // copiar auxiliar a cabeza
    

    if (head->next == nullptr) { // se ejecuta cuando la lista está vacia
      head= nuevo;             // la cabeza apunta hacia el nodo nuevo
      nuevo->next = auxiliar;
    } else { // se ejecuta cuando la lista tiene almenos un elemento
      while(auxiliar->next!=nullptr){
        auxiliar2=auxiliar;
        auxiliar=auxiliar->next;
        
      }
      auxiliar2->next=nuevo;
      nuevo->next=auxiliar;
      
    }
  }
  }else{
    cout<<"no se pudo acceder al archivo: "<<nombreArchivo<<endl;
  }
}

void lista::ImprimirLista(Nodo *&head){
  
  actual=head;
  while(actual->next!=nullptr){
    cout<<"|"<<actual->nombre<<"|"<<actual->habitacion<<"|-->";
    actual=actual->next;
  }
  cout<<endl;
}

void lista::borrar(Nodo *&head){ 
  anterior=nullptr;
  auxiliar=head;
  while(auxiliar->next!=nullptr){
    anterior=auxiliar;
    auxiliar=auxiliar->next;
  }
  anterior->next=auxiliar->next;
  delete auxiliar; 
}