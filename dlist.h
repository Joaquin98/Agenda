#ifndef __SLIST_H__
#define __SLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct _Contacto{
  char * nombre, * apellido, * correo, * fecha, * genero, *telefono;
  int edad;
} _Contacto;

typedef _Contacto * Contacto;

typedef struct _DNodo {
  Contacto dato;
  struct _DNodo *sig, *ant;
} DNodo;

typedef DNodo *DList;

char * ingresar_string_cs(FILE * fp);
char * ingresar_string(FILE * fp);
Contacto contacto_crear(FILE * fp);
void contacto_mostrar(Contacto c,FILE * fp);
void contacto_liberar(Contacto c);
DList dlist_agregar_inicio(DList lista, Contacto dato);
DList dlist_eliminar(DList lista,DList nodo);

#endif
