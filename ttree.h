#ifndef _TTREE_H_
#define _TTREE_H_

#include "dlist.h"

typedef struct _TTree{
  Contacto dato;
  DList ubicacion;
  struct _TTree * hijos[10];
} _TTree;
typedef _TTree * TTree;

TTree ttree_crear();
void ttree_liberar(TTree nodo);
int ttree_es_final(TTree nodo);
int ttree_es_hoja(TTree nodo);
TTree ttree_insertar(TTree raiz,Contacto dato);
void ttree_mostrar_hojas(TTree raiz);
int ttree_buscar_todos(TTree raiz,char * clave);
TTree ttree_buscar(TTree raiz,char * clave);
int ttree_eliminar_aux(TTree raiz, char * telefono, int nivel, int l, DList *nodo);
DList ttree_eliminar(TTree raiz, char * telefono);
void ttree_modificar(TTree raiz,char * telefono,DList *lista);

#endif
