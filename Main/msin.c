#include <stdio.h>
#include <stdlib.h>

// Este programa calcula el uso de memoria de diferentes tipos de datos en C
// y muestra información adicional sobre el sistema operativo y la arquitectura
// en la que se ejecuta, además de información avanzada del sistema.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <sys/utsname.h>
#include <unistd.h>
#endif

// Función para imprimir información del sistema operativo y arquitectura
void print_system_info() {
    printf("=== Información del Sistema Operativo ===\n");
#if defined(_WIN32) || defined(_WIN64)
    printf("Sistema operativo: Windows\n");
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    printf("Arquitectura: ");
    switch (sysInfo.wProcessorArchitecture) {
        case PROCESSOR_ARCHITECTURE_AMD64:
            printf("x64 (AMD o Intel)\n");
            break;
        case PROCESSOR_ARCHITECTURE_INTEL:
            printf("x86\n");
            break;
        case PROCESSOR_ARCHITECTURE_ARM:
            printf("ARM\n");
            break;
        case PROCESSOR_ARCHITECTURE_ARM64:
            printf("ARM64\n");
            break;
        default:
            printf("Desconocida\n");
    }
#elif defined(__linux__) || defined(__APPLE__)
    struct utsname unixSysInfo;
    if (uname(&unixSysInfo) == 0) {
        printf("Sistema operativo: %s\n", unixSysInfo.sysname);
        printf("Nombre del nodo: %s\n", unixSysInfo.nodename);
        printf("Versión del sistema: %s\n", unixSysInfo.version);
        printf("Arquitectura: %s\n", unixSysInfo.machine);
    } else {
        perror("Error obteniendo información del sistema");
    }
#else
    printf("Sistema operativo: Desconocido\n");
#endif
}

// Función para imprimir el tamaño de página de memoria
void print_memory_page_size() {
    printf("\n=== Información Avanzada de Memoria ===\n");
#if defined(_WIN32) || defined(_WIN64)
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    printf("Tamaño de página de memoria: %lu bytes\n", sysInfo.dwPageSize);
#elif defined(__linux__) || defined(__APPLE__)
    long pageSize = sysconf(_SC_PAGESIZE);
    if (pageSize != -1) {
        printf("Tamaño de página de memoria: %ld bytes\n", pageSize);
    } else {
        perror("Error obteniendo el tamaño de página de memoria");
    }
#else
    printf("Información de memoria no disponible en este sistema operativo.\n");
#endif
}

// Función para imprimir la hora y fecha actual
void print_current_time() {
    printf("\n=== Información de Tiempo Actual ===\n");
    time_t now = time(NULL);
    if (now != -1) {
        struct tm *localTime = localtime(&now);
        if (localTime != NULL) {
            printf("Fecha y hora local: %s", asctime(localTime));
        } else {
            perror("Error obteniendo la hora local");
        }
    } else {
        perror("Error obteniendo el tiempo actual");
    }
}

// Función para imprimir las variables de entorno
void print_environment_variables() {
    printf("\n=== Variables de Entorno ===\n");
#if defined(_WIN32) || defined(_WIN64)
    char *env = GetEnvironmentStrings();
    if (env) {
        while (*env) {
            printf("%s\n", env);
            env += strlen(env) + 1;
        }
        FreeEnvironmentStrings(env);
    } else {
        perror("Error obteniendo variables de entorno");
    }
#else
    extern char **environ;
    for (char **env = environ; *env; ++env) {
        printf("%s\n", *env);
    }
#endif
}

// Función para imprimir el uso de memoria de tipos de datos básicos
void print_data_type_sizes() {
    printf("\n=== Uso de Memoria de Tipos de Datos Básicos ===\n");
    printf("char: %zu bytes\n", sizeof(char));
    printf("int: %zu bytes\n", sizeof(int));
    printf("float: %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n", sizeof(double));

    printf("\n=== Uso de Memoria de Tipos de Datos Más Grandes ===\n");
    printf("long: %zu bytes\n", sizeof(long));
    printf("long long: %zu bytes\n", sizeof(long long));
    printf("long double: %zu bytes\n", sizeof(long double));

    printf("\n=== Uso de Memoria de Punteros ===\n");
    printf("puntero a char: %zu bytes\n", sizeof(char*));
    printf("puntero a int: %zu bytes\n", sizeof(int*));
    printf("puntero a void: %zu bytes\n", sizeof(void*));

    // Nota: El tamaño de los punteros puede variar dependiendo de la arquitectura (32 bits o 64 bits).
}

// Función principal
int main() {
    // Mostrar información del sistema operativo y arquitectura
    print_system_info();

    // Mostrar información avanzada de memoria
    print_memory_page_size();

    // Mostrar la hora actual
    print_current_time();

    // Mostrar variables de entorno
    print_environment_variables();

    // Mostrar tamaños de tipos de datos
    print_data_type_sizes();

    return 0; // Fin del programa
}