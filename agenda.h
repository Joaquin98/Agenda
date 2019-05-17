#ifndef _AGENDA_H_
#define _AGENDA_H_

#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"
#include "ttree.h"

typedef enum{NADA, ELIMINADO, AGREGADO} Accion;

typedef struct _Agenda{
	TTree raiz;
	DList lista;
	Contacto uAgregado,uEliminado;
	Contacto uAgregadoD,uEliminadoD;
	Accion accion, accionDeshecha;
	int numElems;
	int sumaEdades;
} _Agenda;

typedef _Agenda *Agenda;

Agenda agenda_crear();
int agenda_insertar(Agenda agenda,Contacto nuevo);
void agenda_buscar(Agenda agenda,char * telefono);
void agenda_modificar(Agenda agenda, char * telefono);
void agenda_eliminar(Agenda agenda,char * telefono);
void agenda_importar_contactos(Agenda agenda, char ** archivo);
void agenda_exportar_contactos(Agenda agenda, char ** archivo);
void agenda_deshacer(Agenda agenda);
void agenda_rehacer(Agenda agenda);
float agenda_promedio(Agenda agenda);

#endif
