

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Estructura para guardar los datos de la persona
typedef struct {
    char nombre[MAX];
    char apellido[MAX];
    char dni[MAX];
} Persona;

// Función para agregar una persona al archivo
void agregarPersona() {
    FILE *archivo = fopen("personas.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Persona p;

    printf("Ingrese nombre: ");
    scanf("%s", p.nombre);
    printf("Ingrese apellido: ");
    scanf("%s", p.apellido);
    printf("Ingrese DNI: ");
    scanf("%s", p.dni);

    fprintf(archivo, "%s %s %s\n", p.nombre, p.apellido, p.dni);
    fclose(archivo);

    printf("Datos guardados exitosamente.\n");
}

// Función para buscar una persona por DNI
void buscarPorDNI() {
    FILE *archivo = fopen("personas.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo o el archivo no existe.\n");
        return;
    }

    char dniBuscado[MAX];
    Persona p;
    int encontrado = 0;

    printf("Ingrese el DNI a buscar: ");
    scanf("%s", dniBuscado);

    while (fscanf(archivo, "%s %s %s", p.nombre, p.apellido, p.dni) != EOF) {
        if (strcmp(p.dni, dniBuscado) == 0) {
            printf("Nombre: %s\nApellido: %s\n", p.nombre, p.apellido);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró una persona con ese DNI.\n");
    }

    fclose(archivo);
}

// Menú principal
int main() {
    int opcion;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Ingresar datos\n");
        printf("2. Buscar por DNI\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarPersona();
                break;
            case 2:
                buscarPorDNI();
                break;
            case 3:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 3);

    return 0;
}
		
		
		
	
		
