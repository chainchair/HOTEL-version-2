#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Nodo {
  string nombre = "";
  int habitacion = -1;
  Nodo *prev = nullptr;
  Nodo *next = nullptr;
};
Nodo *head=new Nodo();
void cargarlista(Nodo *&head, string nombreArchivo) {
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



void imprimirlista(Nodo *head) {
  Nodo *actual= new Nodo();
  actual=head;
  while(actual->next!=nullptr){
    cout<<"|"<<actual->nombre<<"|"<<actual->habitacion<<"|-->";
    actual=actual->next;
  }
  cout<<endl;
}
void borrar(Nodo *head){
  Nodo *auxiliar=new Nodo();
  Nodo *anterior=new Nodo();
  anterior=nullptr;
  
  auxiliar=head;
  while(auxiliar->next!=nullptr){
    anterior=auxiliar;
    auxiliar=auxiliar->next;
  }
  anterior->next=auxiliar->next;
  delete auxiliar;
  
  
}





void abrirArchivo(Nodo* head) {
  ofstream archivo("Hotel.txt"); 
  Nodo* auxiliar = head;
  while(auxiliar->next != nullptr) {
    archivo << auxiliar->nombre << endl;
    archivo << auxiliar->habitacion << endl;

    auxiliar = auxiliar->next;
  }
  
  archivo.close(); 
}

bool habitaciondisponible(Nodo *&head,int n){
  Nodo *auxiliar=new Nodo();
  auxiliar=head;
  
  while(auxiliar->next!=nullptr & auxiliar->habitacion!=n){
    auxiliar=auxiliar->next;
    
  }
  if (auxiliar->habitacion==n){
    return false;
  }
  else{
    return true;
  }
  
  
}
void agregarusuario(Nodo *&head) {
  Nodo *nuevo = new Nodo(); 

  cout << "Ingrese el nombre del huesped: ";
  cin >> nuevo->nombre;
  cout << "Ingrese el numero de habitacion: ";
  cin>>nuevo->habitacion;
  int numero= nuevo->habitacion;

  Nodo *auxiliar = head; 
  Nodo *auxiliar2 = nullptr; 
  if ((habitaciondisponible(head, numero))==true){
    if (auxiliar->next == nullptr) { // se ejecuta cuando la lista está vacia
      head= nuevo;             // la cabeza apunta hacia el nodo nuevo
      nuevo->next = auxiliar;
    } 
    else 
    { // se ejecuta cuando la lista tiene almenos un elemento
      while(auxiliar->next!=nullptr){
        auxiliar2=auxiliar;
        auxiliar=auxiliar->next;
        
      }
      auxiliar2->next=nuevo;
      nuevo->next=auxiliar;
      
    }
    
  
  abrirArchivo(head); 
  }
  else{

    bool anterior= habitaciondisponible(*&head, numero-1);//habitacion anterior
    bool siguiente= habitaciondisponible(*&head, numero+1);//habitacion siguiente
    cout<<endl;
    cout<<"Habitacion solicitada no disponible, ";

    if (anterior ==false && siguiente==false){
      cout<<"habitaciones contiguas no disponibles"<<endl;
      cout<<"ingresar: "<<endl;
      cout<<"1. elegir otra habitación"<<endl;
      cout<<"2. dejar al sistema elegir una habitacion libre"<<endl;
      int opcion;
      cin>>opcion;
      switch(opcion){
        case(1):
          agregarusuario(*&head);
          break;
        case(2):
          
          cout<<"no entras aqui"<<endl;
      }
      
    }
    else{
    cout<<"¿desea ocupar una habitacion contigua?"<<endl;
    cout<<"1. habitacion anterior"<<endl;
    cout<<"2. habitacion siguiente"<<endl;
    int n;
    cin>>n;
    switch(n){
      case(1):
        
      if (anterior==true){
        nuevo->habitacion=numero-1;
        Nodo *auxiliar = head; 
        Nodo *auxiliar2 = nullptr; 
          if (head->next == nullptr) { // se ejecuta cuando la lista está vacia
            head= nuevo;             // la cabeza apunta hacia el nodo nuevo
            nuevo->next = auxiliar;
            abrirArchivo(head); 
          } else { // se ejecuta cuando la lista tiene almenos un elemento
            while(auxiliar->next!=nullptr){
              auxiliar2=auxiliar;
              auxiliar=auxiliar->next;
            }
            auxiliar->next=nuevo;
            //nuevo->next=auxiliar;   
            abrirArchivo(head); 
          }
        
    }
      else{
        cout<<"habitación no disponible"<<endl;
      }
    case(2):
      if (siguiente==true){
        nuevo->habitacion=numero+1;
        Nodo *auxiliar = head; 
        Nodo *auxiliar2 = nullptr; 
          if (head->next == nullptr) { // se ejecuta cuando la lista está vacia
            head= nuevo;             // la cabeza apunta hacia el nodo nuevo
            nuevo->next = auxiliar;
            abrirArchivo(head); 
          } else { // se ejecuta cuando la lista tiene almenos un elemento
            while(auxiliar->next!=nullptr){
              auxiliar2=auxiliar;
              auxiliar=auxiliar->next;
            }
            auxiliar->next=nuevo;
            //nuevo->next=auxiliar; 
            abrirArchivo(head); 
          }
        
    }
      else{
        cout<<"habitación no disponible"<<endl;
      }
  }
  
  
}
  }
}




void consultarVecinos(Nodo* head, int habitacion) {
  Nodo* auxiliar = head;
  Nodo *anterior=new Nodo();
  Nodo *siguiente= new Nodo();
  cout<<endl;
  // Buscar el nodo con el número de habitación buscado
  while (auxiliar != nullptr && auxiliar->habitacion != habitacion) {
    auxiliar = auxiliar->next;
  }

  
  if (auxiliar->next != nullptr) {
    auxiliar=head;
    while((auxiliar->next!=nullptr) && (auxiliar->habitacion!=habitacion-1)){
    auxiliar=auxiliar->next;
    
    }
    if (auxiliar->habitacion==habitacion-1){
      anterior=auxiliar;
      
    }
    auxiliar=head;
    while((auxiliar->next!=nullptr) && (auxiliar->habitacion!=habitacion+1)){
    auxiliar=auxiliar->next;
    
    }
    if (auxiliar->habitacion==habitacion+1){
      siguiente=auxiliar;
      
    }

    // Mostrar el nombre  del huesped de la habitación anterior
    if (anterior->nombre != "") {
      cout<<endl;
      cout << "Huésped de la habitación anterior: " << anterior->nombre<< endl;
    } else {
      cout << "No hay huésped en la habitación anterior" << endl;
    }

    // Mostrar el nombre del huésped de la habitación siguiente
    if (siguiente->nombre != "") {
      cout << "Huésped de la habitación siguiente: " << siguiente->nombre << endl;
    } 
  } else {
    cout << "No se encontró la habitación buscada" << endl;
  }

  cout<<endl;
}




string buscarUsuario(Nodo *&head){
  Nodo *auxiliar=new Nodo();
  auxiliar=head;

  
  cout<<"buscar usuario por: "<<endl;
  cout<<"1. nombre"<<endl;
  cout<<"2. habitacion"<<endl;
  int eleccion;
  string Nombre="";
  int habitacion=0;
  cin>>eleccion;
  switch(eleccion){
    case(1):
      cout<<"ingresa el nombre del usuario a buscar"<<endl;
      cin>>Nombre;
          
      while(auxiliar->next!= nullptr and auxiliar->nombre!=Nombre){
            auxiliar=auxiliar->next;
        }
        if(auxiliar->nombre==Nombre){
          cout<<"la habitacion de ese usuario es: "<<auxiliar->habitacion<<endl;
          string retorno= to_string(auxiliar->habitacion);
          return retorno;
        } 
        else{
        cout<<"usuario no encontrado"<<endl;
      }
    break;
    case(2):
    cout<<"ingresa la habitacion del usuario a buscar"<<endl;
      cin>>habitacion;
          
      while(auxiliar->next!= nullptr and auxiliar->habitacion!=habitacion){
            auxiliar=auxiliar->next;
        }
        if(auxiliar->habitacion==habitacion){
          cout<<"el nombre del usuario es: "<<auxiliar->nombre<<endl;
          return auxiliar->nombre;
        }
      else{
        cout<<"habitacion no ocupada"<<endl;
      }
    break;
 
  }  return Nombre;  
}

void ordenaralfabeticamente() {
  vector<string> palabras;

    // Leemos las palabras desde el archivo Hotel.txt
    ifstream archivo("Hotel.txt");
    string palabra;
    string a="string";
    int i=2;    
    while (archivo >> palabra) {

      
      if (i%2==0){
        palabras.push_back(palabra);
      }
      i=i+1;
        
    }
    archivo.close();

    // Ordenamos el vector alfabéticamente
    sort(palabras.begin(), palabras.end());

    // Imprimimos las palabras ordenadas
    cout << "Palabras ordenadas alfabéticamente: ";
    for (const auto& palabra : palabras) {
        cout << palabra << " ";
    }
    cout << endl;
}


void menu(Nodo *&head){
  bool programa=true;
  int opcion=-1;
  while(programa==true){
  cout<<"este es el menú interactivo del sistema automatico M.I.S.A"<<endl<<"opciones disponibles"<<endl;
  cout<<"0. salir"<<endl;
  cout<<"1. ingresar huesped"<<endl;
  cout<<"2. buscar usuario"<<endl;
  cout<<"3. mostrar lista en orden alfabetico"<<endl;
  cout<<"4. mostrar lista en orden de llegada"<<endl;
  cout<<"5. consultar vecinos"<<endl;
  cin>>opcion;
  switch(opcion){
    case(0):
    cout<<"programa cerrado"<<endl;
    programa=false;
    break;
    case(1):
    agregarusuario(*&head);
    break;
    case(2):
    buscarUsuario(*&head);
    break;
    case(3):
    ordenaralfabeticamente();
    break;
    case(4):
    imprimirlista(*&head);
    break;
    case(5):
    int habitacion;
    cout<<"ingresar habitacion"<<endl;
    cin>>habitacion;
    consultarVecinos(*&head, habitacion);
    break;
    default:
    cout<<"string no aceptado"<<endl;
  }
  }
}

int main(){
  string Hotel = "Hotel.txt";
  cargarlista(head, Hotel);
  menu(head);
}
