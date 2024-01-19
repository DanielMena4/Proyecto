        }

        fprintf(temporal, "%d,%s,%.2f,%d\n", id, nombre, sueldo, horas);
    }

    fclose(archivo);
    fclose(temporal);

    remove("empleados.txt");
    rename("temporal.txt", "empleados.txt");
    archivo = fopen("empleados.txt", "a+");

    if (encontrado) {
        printf("Horas modificadas exitosamente.\n");
    } else {
        printf("Empleado no encontrado.\n");
    }
}

void consultarModificaciones(FILE *archivoBajas, FILE *archivoCambiosSueldo, FILE *archivoCambiosHoras) {
    int id;
    char nombre[50];
    float sueldo;
    int horas;

    printf("\nLista de modificaciones:\n");

    printf("\nEmpleados dados de baja:\n");
    while (fscanf(archivoBajas, "%d,%[^,],%f,%d\n", &id, nombre, &sueldo, &horas) == 4) {
        printf("\nID: %d\n", id);
        printf("Nombre: %s\n", nombre);
        printf("Sueldo: %.2f\n", sueldo);
        printf("Horas semanales: %d\n", horas);
    }

    printf("\nCambios de sueldo y horas:\n");
    while (fscanf(archivoCambiosHoras, "%d,%[^,],%f,%d\n", &id, nombre, &sueldo, &horas) == 4) {
        printf("\nID: %d\n", id);
        printf("Nombre: %s\n", nombre);
        printf("Sueldo: %.2f\n", sueldo);
        printf("Horas semanales: %d\n", horas);
    }

    printf("\nCambios de horas:\n");
    while (fscanf(archivoCambiosSueldo, "%d,%[^,],%f,%d\n", &id, nombre, &sueldo, &horas) == 4) {
        printf("\nID: %d\n", id);
        printf("Nombre: %s\n", nombre);
        printf("Sueldo: %.2f\n", sueldo);
        printf("Horas semanales: %d\n", horas);
    }
}

int main() {
    FILE *archivo;
    FILE *archivoBajas;
    FILE *archivoCambiosSueldo;
    FILE *archivoCambiosHoras;

    archivo = fopen("empleados.txt", "a+");
    archivoBajas = fopen("empleados_bajas.txt", "a+");
    archivoCambiosSueldo = fopen("empleados_cambios_sueldo.txt", "a+");
    archivoCambiosHoras = fopen("empleados_cambios_horas.txt", "a+");

    if (archivo == NULL || archivoBajas == NULL) {
        printf("Error al abrir los archivos.\n");
        return 1;
    }

    int opcion;
    int contadorId = 1;

    while (opcion != 8) {
        printf("\nMenu:\n");
        printf("1 - Alta empleado\n");
        printf("2 - Baja empleado\n");
        printf("3 - Lista de empleados\n");
        printf("4 - Consultar datos de empleado\n");
        printf("5 - Modificar salario\n");
        printf("6 - Modificar horas\n");
        printf("7 - Consultar modificaciones\n");
        printf("8 - Salir\n");

        printf("Ingrese la opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                altaEmpleado(archivo, &contadorId);
                break;
            case 2:
                bajaEmpleado(archivo, archivoBajas);
                break;
            case 3:
                listaEmpleados(archivo);
                break;
            case 4:
                consultarDatos(archivo);
                break;
            case 5:
                modificarSalario(archivo, archivoCambiosSueldo);
                break;
            case 6:
                modificarHoras(archivo, archivoCambiosHoras);
                break;
            case 7:
                 consultarModificaciones(archivoBajas, archivoCambiosSueldo, archivoCambiosHoras);
                break;
            case 8:
                break;
            default:
                printf("Opcion no valida.\n");
        }

        rewind(archivo);
        rewind(archivoBajas);
        rewind(archivoCambiosSueldo);
        rewind(archivoCambiosHoras);
    }

    fclose(archivo);
    fclose(archivoBajas);
    fclose(archivoCambiosSueldo);
    rewind(archivoCambiosHoras);

    return 0;
}
