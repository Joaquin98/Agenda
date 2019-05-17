#include "dlist.h"

/*
  Elimina el nodo de la lista, libera solo el nodo
  sin liberar el contacto.
*/
DList dlist_eliminar(DList lista,DList nodo){
  if(nodo->ant == NULL){
    DList siguiente = nodo->sig;
    if(nodo->sig!=NULL) nodo->sig->ant = NULL;
    free(nodo);
    return siguiente;
  }
  nodo->ant->sig = nodo->sig;
  if(nodo->sig!=NULL) nodo->sig->ant = nodo->ant;
  free(nodo);
  return lista;
}

DList dlist_agregar_inicio(DList lista, Contacto dato) {
  DList nuevoNodo = malloc(sizeof(DNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  if(lista!=NULL)
    lista->ant = nuevoNodo;
  nuevoNodo->ant = NULL;
  return nuevoNodo;
}

/*
  Pide una string, pide memoria para ella, la almacena y la
  retorna con algunas modificaciones (pone todas las letras
  en minusculas excepto la primera que la pasa a mayuscula).
*/
char * ingresar_string(FILE * fp){
  char buffer[1000];
  fscanf(fp," %s",buffer);
  int longitud = strlen(buffer);
  for(int i=0; i<longitud; i++) buffer[i] = tolower(buffer[i]);
  buffer[0] = toupper(buffer[0]);
  char * palabra = malloc(sizeof(char) * longitud + 1);
  strcpy(palabra,buffer);
  return palabra;
}

/*
  Pide una string, pide memoria para ella, la almacena y la
  retorna tal cual se ingreso.
*/
char * ingresar_string_cs(FILE * fp){
  char buffer[1000];
  fscanf(fp," %s",buffer);
  int longitud = strlen(buffer);
  char * palabra = malloc(sizeof(char) * longitud + 1);
  strcpy(palabra,buffer);
  return palabra;
}

/*
  Toma los datos por teclado o por archivo y crea un
  nuevo contacto.
*/
Contacto contacto_crear(FILE * fp){
  Contacto nuevo = malloc(sizeof(_Contacto));
  if(fp == stdin) printf("Ingrese el nombre:\n");
  nuevo->nombre = ingresar_string(fp);
  if(fp == stdin) printf("Ingrese el apellido:\n");
  nuevo->apellido = ingresar_string(fp);
  if(fp == stdin) printf("Ingrese el correo:\n");
  nuevo->correo = ingresar_string(fp);
  if(fp == stdin) printf("Ingrese la fecha:\n");
  nuevo->fecha = ingresar_string(fp);
  if(fp == stdin) printf("Ingrese el genero:\n");
  nuevo->genero = ingresar_string(fp);
  if(fp == stdin) printf("Ingrese el telefono:\n");
  nuevo->telefono = ingresar_string(fp);
  if(fp == stdin) printf("Ingrese la edad:\n");
  fscanf(fp,"%d",&(nuevo->edad));
  return nuevo;
}

/*
  Muestra los datos de un contacto en la pantalla o en
  un archivo.
*/
void contacto_mostrar(Contacto c,FILE * fp){
  if(fp == stdout) fprintf(fp,"\nContacto:\n");
  if(fp == stdout) fprintf(fp,"Nombre: ");
  fprintf(fp,"%s\n",c->nombre);
  if(fp == stdout) fprintf(fp,"Apellido: ");
  fprintf(fp,"%s\n",c->apellido);
  if(fp == stdout) fprintf(fp,"Correo: ");
  fprintf(fp,"%s\n",c->correo);
  if(fp == stdout) fprintf(fp,"Fecha de nacimiento: ");
  fprintf(fp,"%s\n", c->fecha);
  if(fp == stdout) fprintf(fp,"Genero: ");
  fprintf(fp,"%s\n",c->genero);
  if(fp == stdout) fprintf(fp,"Telefono: ");
  fprintf(fp,"%s\n",c->telefono);
  if(fp == stdout) fprintf(fp,"Edad: ");
  fprintf(fp,"%d\n",c->edad);
  if(fp == stdout) fprintf(fp,"\n");
}

void contacto_liberar(Contacto c){
  if(c==NULL) return;
  free(c->nombre);
  free(c->apellido);
  free(c->correo);
  free(c->fecha);
  free(c->genero);
  free(c->telefono);
  free(c);
}
