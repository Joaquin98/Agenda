#include "agenda.h"

Agenda agenda_crear(){
	Agenda nueva = malloc(sizeof(_Agenda));
	nueva->raiz = ttree_crear();
	nueva->lista = NULL;
	nueva->uAgregado = NULL;
  nueva->uEliminado = NULL;
	nueva->uAgregadoD = NULL;
  nueva->uEliminadoD = NULL;
  nueva->accion = NADA;
	nueva->accionDeshecha = NADA;
	nueva->numElems = 0;
}

/*
	Intenta insertar un contacto en el arbol, en caso de poderse
	lo inserta tambien en la lista enlazada y retorna 1.
	En caso contrario retorna 0.
*/
int agenda_insertar(Agenda agenda,Contacto nuevo){

	TTree nodo = ttree_insertar(agenda->raiz,nuevo);
  if(nodo!=NULL){
		agenda->numElems++;
	  agenda->accion = AGREGADO;
	  agenda->uAgregado = nuevo;
		agenda->lista = dlist_agregar_inicio(agenda->lista,nuevo);
		nodo->ubicacion = agenda->lista;
		return 1;
	}
	return 0;

}

/*
	Toma una string si la string termina en * quiere decir
	que la busqueda es por patrones por lo tanto elimina el *
	y llama a la busqueda. En caso contrario busca la string
	tal cual esta.
*/
void agenda_buscar(Agenda agenda,char * telefono){
	if(telefono[strlen(telefono)-1]=='*'){
		telefono[strlen(telefono)-1] = '\0';
		if(!ttree_buscar_todos(agenda->raiz,telefono))
			printf("No se encontro ningun contacto con ese patron.\n");
	} else {
		TTree nodo = ttree_buscar(agenda->raiz,telefono);
		if(nodo == NULL || nodo->dato == NULL)
			printf("No se encontro ningun contacto con ese numero.\n");
		else contacto_mostrar(nodo->dato,stdout);
	}
}

void agenda_modificar(Agenda agenda, char * telefono){
  ttree_modificar(agenda->raiz,telefono,&(agenda->lista));
}

/*
	Intenta eliminar un contacto del arbol, en caso de poderse
	lo elimina tambien de la lista.
*/
void agenda_eliminar(Agenda agenda,char * telefono){

	DList nodo = ttree_eliminar(agenda->raiz,telefono);
  if(nodo!=NULL){
    agenda->numElems--;
		if(agenda->uEliminado!=NULL && agenda->uEliminado != agenda->uEliminadoD)
			contacto_liberar(agenda->uEliminado);
    agenda->accion = ELIMINADO;
    agenda->uEliminado = nodo->dato;
    agenda->lista = dlist_eliminar(agenda->lista,nodo);
  } else printf("El contacto no se encuentra en la agenda.\n");

}

/*
	Inserta los contactos desde un archivo en caso de que
	exista el archivo sino avisa que no es posible.
*/
void agenda_importar_contactos(Agenda agenda, char ** archivo){
  int n;
  char c;
  printf("El archivo por defecto de donde se importaran los Contactos es '%s' desea cambiarlo? (S/N)\n", *archivo);
  scanf(" %c",&c);
  if(tolower(c)=='s'){
    free(*archivo);
    printf("Ingrese el nombre del nuevo archivo:\n");
    (*archivo) = ingresar_string_cs(stdin);
  }
  FILE * fp = fopen(*archivo,"r");
	if(fp==NULL){
		printf("Archivo no encontrado\n");
		getchar();getchar();
		return;
	}
  fscanf(fp,"%d",&n);
  while(n--)
		agenda_insertar(agenda,contacto_crear(fp));
  fclose(fp);
}

/*
	Escribe en un archivo la cantidad de contactos en la agenda,
	y luego escribe contacto por contacto sus atributos separados
	por "\n". Si el archivo no existe lo crea.
*/
void agenda_exportar_contactos(Agenda agenda, char ** archivo){
  char c;
  printf("El archivo por defecto donde se guardan sus Contactos es '%s' desea cambiarlo? (S/N)\n", *archivo);
  scanf(" %c",&c);
  if(tolower(c)=='s'){
    free(*archivo);
    printf("Ingrese el nombre del nuevo archivo:\n");
    (*archivo) = ingresar_string_cs(stdin);
  }
  FILE * fp = fopen(*archivo,"w+");
  if(agenda->numElems>0){
    fprintf(fp,"%d\n",agenda->numElems);
    DList lista = agenda->lista;
    for(;lista!=NULL; lista=lista->sig)
      contacto_mostrar(lista->dato,fp);
  } else fprintf(fp,"0\nNo hay contactos.\n");
  fclose(fp);
}

float agenda_promedio(Agenda agenda){
	int sumaEdades = 0;
	DList lista = agenda->lista;
	for(;lista!=NULL; lista=lista->sig) sumaEdades+=lista->dato->edad;
	return sumaEdades / (agenda->numElems * 1.0);
}

/*
	Deshace la ultima accion de insercion o eliminacion (solo
	la ultima accion).
*/
void agenda_deshacer(Agenda agenda){
	if(agenda->accion != NADA && agenda->uEliminadoD!=NULL){
		contacto_liberar(agenda->uEliminadoD);
		if(agenda->uEliminado == agenda->uEliminadoD)
			agenda->uEliminado = NULL;
		agenda->uEliminadoD = NULL;
	}
  if(agenda->accion==ELIMINADO){
    agenda_insertar(agenda,agenda->uEliminado);
    agenda->accion = NADA;
		agenda->accionDeshecha = AGREGADO;
		agenda->uAgregadoD = agenda->uEliminado;
    agenda->uEliminado = NULL;
    return;
  }
  if(agenda->accion==AGREGADO){
    agenda_eliminar(agenda,agenda->uAgregado->telefono);
    agenda->accion = NADA;
		agenda->accionDeshecha = ELIMINADO;
		agenda->uEliminadoD = agenda->uAgregado;
    agenda->uAgregado = NULL;
    return;
  }
}

/*
	Rehace la ultima accion deshecha sin importar si se hicieron
	otras acciones intermedias.
*/
void agenda_rehacer(Agenda agenda){
	if(agenda->accionDeshecha==ELIMINADO){
		agenda_insertar(agenda,agenda->uEliminadoD);
		if(agenda->uEliminado == agenda->uEliminadoD)
			agenda->uEliminado = NULL;
		agenda->uEliminadoD = NULL;
		agenda->accionDeshecha = NADA;
		return;
	}
	if(agenda->accionDeshecha==AGREGADO){
		agenda_eliminar(agenda,agenda->uAgregadoD->telefono);
		agenda->accionDeshecha = NADA;
		return;
	}
}
