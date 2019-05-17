#include "ttree.h"

/* Crea un arbol de telefonos */
TTree ttree_crear(){
  TTree nuevo = malloc(sizeof(_TTree));
  nuevo->dato = NULL;
  nuevo->ubicacion = NULL;
  for(int i=0; i<10; i++) nuevo->hijos[i] = NULL;
  return nuevo;
}

/* Libera el nodo sin eliminar el contacto */
void ttree_liberar(TTree nodo){
  free(nodo);
}

/*
  Retorna 1 en caso que el nodo tenga un contacto
  asociado (nodo final), y 0 en caso contrario.
*/
int ttree_es_final(TTree nodo){
  return (nodo->dato!=NULL);
}

/* Retorna 1 si no tiene hijos, 0 en caso contrario */
int ttree_es_hoja(TTree nodo){
  for(int i=0; i<10; i++)
    if(nodo->hijos[i]!=NULL) return 0;
  return 1;
}

/*
  Recorre el arbol segun los digitos del telefono (si no existen
  los nodos necesarios para recorrer todo el numero los crea).
  Guarda la direccion del contacto en el ultimo nodo y retorna el
  nodo si el nodo no tenia ya un contacto, sino retorna NULL.
*/
TTree ttree_insertar(TTree raiz,Contacto dato){
  int indice,longitud = strlen(dato->telefono);
  TTree temp = raiz;
  for (int  nivel = 0; nivel < longitud ; nivel++) {
    indice = dato->telefono[nivel] - '0';
    if(temp->hijos[indice] == NULL)
      temp->hijos[indice] = ttree_crear();
    temp = temp->hijos[indice];
  }
  if(temp->dato==NULL){
    temp->dato = dato;
    return temp;
  }
  return NULL;
}

/* Muestra todos los contactos presentes en el arbol. */
void ttree_mostrar_hojas(TTree raiz){
  if(raiz==NULL) return;
  if(raiz->dato!=NULL) contacto_mostrar(raiz->dato,stdout);
  for(int i = 0; i<10; i++)
    ttree_mostrar_hojas(raiz->hijos[i]);
}

/*
  Recorre el arbol segun los digitos del telefono en caso de
  poder recorrer hasta el ultimo digito retorna el ultimo
  nodo, en caso contrario retorna NULL.
*/
TTree ttree_buscar(TTree raiz,char * telefono){
  int indice,longitud = strlen(telefono);
  TTree temp = raiz;
  for (int  nivel = 0; nivel < longitud ; nivel++) {
    indice = telefono[nivel] - '0';
    if(temp->hijos[indice] == NULL) return NULL;
    temp = temp->hijos[indice];
  }
  return temp;
}

/*
  Recorre el arbol segun los digitos del telefono y muestra
  todos los contactos presentes en el subarbol del cual es
  raiz el ultimo nodo recorrido.
*/
int ttree_buscar_todos(TTree raiz,char * telefono){
  TTree temp = ttree_buscar(raiz,telefono);
  if(temp==NULL) return 0;
  ttree_mostrar_hojas(temp);
  return 1;
}

/*
  Recorre el arbol segun los digitos del telefono.
  Si el ultimo nodo tiene un contacto, pide el nuevo atributo
  que se quiere modificar y lo modifica. Si el atributo que
  se modifico es el telefono se elimina el numero anterior
  y se inserta el contacto con el nuevo numero.
*/
void ttree_modificar(TTree raiz,char * telefono,DList *lista){
  TTree temp = ttree_buscar(raiz,telefono);
  if(temp==NULL || temp->dato==NULL) return;
  Contacto resultado = temp->dato;
  char ** aux = NULL;
  printf("Que atributo desea modificar?\n");
  printf("1 - Nombre.\n2 - Apellido.\n3 - Correo.\n4 - Genero\n");
  printf("5 - Fecha.\n6 - Telefono.\n7 - Edad.\n");
  int op=-1;
  scanf("%d",&op);
  switch (op) {
    case 1:
      aux = &(resultado->nombre);
      break;
    case 2:
      aux = &(resultado->apellido);
      break;
    case 3:
      aux = &(resultado->correo);
      break;
    case 4:
      aux = &(resultado->genero);
      break;
    case 5:
      aux = &(resultado->fecha);
      break;
    case 6:
      printf("Ingrese el nuevo dato:\n");
      char * tel = ingresar_string(stdin);
      resultado->telefono = tel;
      TTree nodo = ttree_insertar(raiz,resultado);
      if(nodo == NULL){
        resultado->telefono = telefono;
        free(tel);
        printf("Ya existe un contacto con ese numero.\n");
        getchar();getchar();
        return;
      }
      (*lista) = dlist_eliminar((*lista),ttree_eliminar(raiz,telefono));
      free(telefono);
      (*lista) = dlist_agregar_inicio((*lista),resultado);
      nodo->ubicacion = (*lista);
      return;
    case 7:
      printf("Ingrese la nueva edad:\n");
      scanf("%d",&(resultado->edad));
      break;
  }
  if(aux!=NULL){
    printf("Ingrese el nuevo dato:\n");
    free(*aux);
    *aux = ingresar_string(stdin);
  }
}

/*
  La funcion recorre desde el ultimo nodo del telefono hasta
  la raiz.
  - El caso base que es el que ocurre cuando se encuentra
  en el utimo nodo se fija si existe un contacto con ese telefono,
  si existe lo elimina del nodo, guarda la direccion donde se
  encuentra el contacto en la lista y retorna 1 en caso que sea
  una hoja (avisando asi que el nodo debe ser eliminado).
  - El caso recursivo se fija si el siguiente nodo debe ser
  eliminado, en caso positivo lo elimina y retorna 1 si el
  nodo en el que se encuentra es una hoja y no tiene un contacto
  (avisando asi que debe ser eliminado), en caso negativo retorna
  0 ya que si el siguiente nodo no puede ser eliminado este tampoco.
*/
int ttree_eliminar_aux(TTree raiz, char * telefono, int nivel, int l, DList *nodo){
  if(raiz == NULL) return 0;
  if(nivel == l){
    if(raiz->dato!=NULL){
      raiz->dato = NULL;
      *nodo = raiz->ubicacion;
      if(ttree_es_hoja(raiz)) return 1;
    }
    return 0;
  } else {
    int indice = telefono[nivel] - '0';
    if(ttree_eliminar_aux(raiz->hijos[indice],telefono,nivel+1,l,nodo)){
      ttree_liberar(raiz->hijos[indice]);
      raiz->hijos[indice] = NULL;
      return (!ttree_es_final(raiz) && ttree_es_hoja(raiz));
    }
    return 0;
  }
}

/*
  En caso que el numero de telefono se encuentre en el arbol,
  lo elimina y retorna la direccion del nodo de la lista en
  donde se encuentra el contacto.
  En caso que no este en el arbol retorna NULL.
*/
DList ttree_eliminar(TTree raiz, char * telefono){
  int longitud = strlen(telefono);
  DList aux = NULL;
  ttree_eliminar_aux(raiz,telefono,0,longitud,&aux);
  return aux;
}
