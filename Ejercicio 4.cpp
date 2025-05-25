#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_PERSONAS 100

typedef struct {
    char nombre[MAX];
    char apellido[MAX];
    char dni[MAX];
} Persona;

int dniExiste(const char *dniBuscado) {
    FILE *archivo = fopen("personas.txt", "r");
    if(archivo == NULL) return 0;

    Persona p;
    while (fscanf(archivo, "%s %s %s", p.nombre, p.apellido, p.dni) != EOF) {
        if (strcmp(p.dni, dniBuscado) == 0) {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

void agregarPersona() {
    Persona p;

    printf("Ingrese nombre: ");
    scanf("%s", p.nombre);
    printf("Ingrese apellido: ");
    scanf("%s", p.apellido);
    printf("Ingrese DNI: ");
    scanf("%s", p.dni);

    if(dniExiste(p.dni)){
        printf("Error, el DNI ya está registrado.\n");
        return;
    }

    FILE *archivo = fopen("personas.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

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

    printf("Ingrese el nombre o apellido a buscar: ");
    getchar(); 
    fgets(busquedaNombreApellido, MAX, stdin);
    strtok(busquedaNombreApellido, "\n");

    while (fscanf(archivo, "%s %s %s", p.nombre, p.apellido, p.dni) != EOF) {
        if (strstr(p.nombre, busquedaNombreApellido) != NULL || strstr(p.apellido, busquedaNombreApellido) != NULL) {
            printf("Nombre: %s | Apellido: %s | DNI: %s\n", p.nombre, p.apellido, p.dni);
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

    printf("Ingrese el DNI a buscar: ");
    getchar(); 
    fgets(dniBuscado, MAX, stdin);
    strtok(dniBuscado, "\n");

    while (fscanf(archivo, "%s %s %s", p.nombre, p.apellido, p.dni) != EOF) {
        if (strcmp(p.dni, dniBuscado) == 0) {
            printf("Nombre: %s | Apellido: %s | DNI: %s\n", p.nombre, p.apellido, p.dni);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontró el DNI.\n");
    }

    fclose(archivo);
}

int compararPorNombreApellido(const void *a, const void *b) {
    const Persona *p1 = (const Persona *)a;
    const Persona *p2 = (const Persona *)b;

    int cmp = strcmp(p1->apellido, p2->apellido);
    if (cmp == 0) {
        return strcmp(p1->nombre, p2->nombre);
    }
    return cmp;
}

int compararPorDni(const void *a, const void *b) {
    const Persona *p1 = (const Persona *)a;
    const Persona *p2 = (const Persona *)b;
    return strcmp(p1->dni, p2->dni);
}

void mostrarOrdenado() {
    FILE *archivo = fopen("personas.txt", "r");
    if (archivo == NULL) {
        printf("No hay registros para mostrar.\n");
        return;
    }

    Persona personas[MAX_PERSONAS];
    int cantidad = 0;

    while (fscanf(archivo, "%s %s %s", personas[cantidad].nombre, personas[cantidad].apellido, personas[cantidad].dni) != EOF) {
        cantidad++;
        if (cantidad >= MAX_PERSONAS) break;
    }
    fclose(archivo);

    if (cantidad == 0) {
        printf("No hay registros para mostrar.\n");
        return;
    }

    int opcionOrden;
    printf("\nMostrar ordenado por: \n1- Nombre y apellido \n2- DNI\nSeleccione: ");
    scanf("%d", &opcionOrden);

    if (opcionOrden == 1) {
        qsort(personas, cantidad, sizeof(Persona), compararPorNombreApellido);
    } else if (opcionOrden == 2) {
        qsort(personas, cantidad, sizeof(Persona), compararPorDni);
    } else {
        printf("Opción inválida.\n");
        return;
    }

    printf("\n-- Lista de personas ordenada --\n");
    for (int i = 0; i < cantidad; i++) {
        printf("Nombre: %s | Apellido: %s | DNI: %s\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }
}

int main() {
    int opcion;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Ingresar datos\n");
        printf("2. Buscar por DNI\n");
        printf("3. Buscar por nombre o apellido\n");
        printf("4. Mostrar todos ordenados\n");
        printf("5. Salir\n");
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
                mostrarOrdenado();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    return 0;
}

