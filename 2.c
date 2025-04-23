
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


typedef struct {
    char nombre[MAX];
    char apellido[MAX];
    char dni[MAX];
} Persona;


void agregarPersona() {
    FILE *archivo = fopen("personas.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }
    

    Persona p;

    printf("Ingrese nombre: ");
    scanf("%s", p.nombre);
    strtok(p.nombre, "\n");
    printf("Ingrese apellido: ");
    scanf("%s", p.apellido);
    strtok(p.apellido, "\n");
    printf("Ingrese DNI: ");
    scanf("%s", p.dni);
    strtok(p.dni, "\n");

    fprintf(archivo, "%s %s %s\n", p.nombre, p.apellido, p.dni);
    fclose(archivo);

    printf("Datos guardados exitosamente.\n");
}


void buscarPorNombreApellido() {
    FILE *archivo = fopen("personas.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo o el archivo no existe.\n");
        return;
    }

    char busquedaNombreApellido[MAX];
    Persona p;
    int encontrado = 0;

    printf("Ingrese el nombre o apellido a buscar \n");
    fgets(busquedaNombreApellido, MAX, stdin);
    strtok(busquedaNombreApellido, "\n");

    while (fscanf(archivo, "%s %s %s", p.nombre, p.apellido, p.dni) != EOF) {
        if (strstr(p.nombre, busquedaNombreApellido) != NULL || strstr(p.apellido, busquedaNombreApellido) != NULL) {
            printf("Nombre: %s\nApellido: %s\nDNI: %s\n", p.nombre, p.apellido, p.dni);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontró una persona con ese nombre o apellido.\n");
    }

    fclose(archivo);
}

void buscarPorDNI() {
    FILE *archivo = fopen("personas.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo o el archivo no existe.\n");
        return;
    }
    
    char dniBuscado[MAX];
    Persona p;
    int encontrado = 0;
    
    
    printf("Ingrese el DNI a buscar \n");
    fgets(dniBuscado, MAX, stdin);
    strtok(dniBuscado, "\n");
    
    while (fscanf(archivo, "%s %s %s", p.nombre, p.apellido, p.dni) != EOF) {
        if (strcmp(p.dni, dniBuscado) == 0) {
            printf("Nombre: %s\nApellido: %s\nDNI: %s\n", p.nombre, p.apellido, p.dni);
            encontrado = 1;
            break;
        }
    }
    
    if(!encontrado){
        printf("No se encontro el DNI");
    }
    
    fclose(archivo);
}


int main() {
    int opcion;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Ingresar datos\n");
        printf("2. Buscar por DNI \n");
        printf("3. Buscar por nombre o apellido\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);


         while (getchar() != '\n');
        switch (opcion) {
            case 1:
                agregarPersona();
                break;
            case 2:
                buscarPorDNI();
                break;
            case 3:
                buscarPorNombreApellido();
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}