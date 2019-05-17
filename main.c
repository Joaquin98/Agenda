#include "agenda.h"

void limpiar_pantalla(){
  system("cls||clear");
}

int desea_exportar(){
  char c;
  printf("Desea Guardar la lista de Contactos? (S/N)\n");
  scanf(" %c",&c);
  if(tolower(c)=='s') return 1;
  return 0;
}

/*
  Menu principal.
*/
int main(){

	Agenda agenda = agenda_crear();
  char * archivoOut = malloc(sizeof(char)*100);
  char * archivoIn = malloc(sizeof(char)*100);
  strcpy(archivoOut,"contactos.out");
  strcpy(archivoIn,"contactos.in");

  while(1){
    int op=-1;
    char * tel;
    printf("1 - Insertar Contacto.\n2 - Buscar Contacto por telefono/patron.\n");
		printf("3 - Eliminar Contacto.\n4 - Editar Contacto.\n");
		printf("5 - Importar desde Archivo.\n6 - Exportar a Archivo.\n");
    printf("7 - Salir.\n8 - Promedio de Edades.\n");
		printf("9 - Deshacer Ultima Accion.\n10 - Reahacer Ultima deshecha.\n");
    scanf("%d",&op);
    switch (op) {
      case 1:
        limpiar_pantalla();
				if(agenda_insertar(agenda,contacto_crear(stdin)))
					printf("\nContacto agregado exitosamente.\n");
				else printf("\nEl contacto ya se encuentra en la agenda.\n");
				getchar();getchar();
				limpiar_pantalla();
        break;
      case 2:
        limpiar_pantalla();
        printf("Ingrese el numero de telefono:\n");
        tel = ingresar_string(stdin);
				agenda_buscar(agenda,tel);
        getchar();getchar();
				limpiar_pantalla();
        break;
      case 3:
        limpiar_pantalla();
				printf("Ingrese el numero de telefono:\n");
        tel = ingresar_string(stdin);
				agenda_eliminar(agenda,tel);
        break;
      case 4:
        limpiar_pantalla();
        printf("Ingrese el numero de telefono:\n");
        tel = ingresar_string(stdin);
				agenda_modificar(agenda,tel);
				limpiar_pantalla();
        break;
      case 5:
        limpiar_pantalla();
        agenda_importar_contactos(agenda,&archivoIn);
				limpiar_pantalla();
        break;
      case 6:
        limpiar_pantalla();
        agenda_exportar_contactos(agenda,&archivoOut);
				limpiar_pantalla();
        break;
      case 7:
        limpiar_pantalla();
        if(desea_exportar())
          agenda_exportar_contactos(agenda,&archivoOut);
        return 0;
      case 8:
        limpiar_pantalla();
        if(agenda->numElems != 0)
        	printf("El promedio de edades de tus contactos es %.2f.\n\n",agenda_promedio(agenda));
        else printf("No tienes contactos.\n\n");
				getchar();getchar();
				limpiar_pantalla();
        break;
      case 9:
				agenda_deshacer(agenda);
				limpiar_pantalla();
        break;
      case 10:
				agenda_rehacer(agenda);
				limpiar_pantalla();
        break;
    }
  }
}
