#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_JUGADORES 1000

typedef struct{
    char nombre[MAX];
    int puntaje;
} Jugador;

void guardarJugador() {
    FILE *archivo = fopen("jugadores.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    Jugador j;
    printf("Ingrese el nombre del jugador: ");
    scanf("%s", j.nombre);
    printf("Ingrese el puntaje: ");
    scanf("%d", &j.puntaje);

    fprintf(archivo, "%s %d\n", j.nombre, j.puntaje);
    fclose(archivo);

    printf("Jugador guardado exitosamente!\n");
}

int compararJugadores(const void *a, const void *b) {
    Jugador *j1 = (Jugador *)a;
    Jugador *j2 = (Jugador *)b;
    return j2->puntaje - j1->puntaje;
}

void mostrarTop10() {
    FILE *archivo = fopen("jugadores.txt", "r");
    if (archivo == NULL) {
        printf("No hay registros para mostrar.\n");
        return;
    }

    Jugador jugadores[MAX_JUGADORES];
    int cantidad = 0;

    while (fscanf(archivo, "%s %d", jugadores[cantidad].nombre, &jugadores[cantidad].puntaje) != EOF) {
        cantidad++;
        if (cantidad >= MAX_JUGADORES) break;
    }

    fclose(archivo);

    qsort(jugadores, cantidad, sizeof(Jugador), compararJugadores);

    int mostrar = cantidad < 10 ? cantidad : 10;
    printf("\n-- Top %d Jugadores --\n", mostrar);
    for (int i = 0; i < mostrar; i++) {
        printf("%d. %s - %d puntos\n", i + 1, jugadores[i].nombre, jugadores[i].puntaje);
    }
}

void buscarJugador() {
    FILE *archivo = fopen("jugadores.txt", "r");
    if (archivo == NULL) {
        printf("No hay registros para buscar.\n");
        return;
    }

    char nombreBuscado[MAX];
    Jugador j;
    int encontrado = 0;

    printf("Ingrese el nombre del jugador a buscar: ");
    scanf("%s", nombreBuscado);

    printf("\nResultado de busqueda:\n");
    while (fscanf(archivo, "%s %d", j.nombre, &j.puntaje) != EOF) {
        if (strcmp(j.nombre, nombreBuscado) == 0) {
            printf("Jugador: %s - Puntaje: %d\n", j.nombre, j.puntaje);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontro ningun jugador con ese nombre.\n");
    }

    fclose(archivo);
}

int main() {
    int opcion;

    do {
        printf("\n-- MENU --\n");
        printf("1. Registrar jugador\n");
        printf("2. Ver top 10 jugadores\n");
        printf("3. Buscar jugador por nombre\n");
        printf("4. Salir\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                guardarJugador();
                break;
            case 2:
                mostrarTop10();
                break;
            case 3:
                buscarJugador();
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción invalida, intente de nuevo.\n");
        }

    } while (opcion != 4);

    return 0;
}
