#include <iostream>
#include "combinatoria.h"
#include "results.h"

/**
 * Ejecutad "./combinaciones P M N"
 * P: el número a usar
 * M: las veces que se va a usar el número
 * N: el resultado esperado
 *
 * Ej: obtener el 5 (N) usando tres (M) cuatros (P)
 */
int main(int argc, char *argv[]) {
    if (argc != 4) return EXIT_FAILURE;

    Results results( strtol(argv[2], nullptr, 10) );
    Result *a = new Result( strtol(argv[1], nullptr, 10) );

    results.add(a);

    for(Result* aux : a->combineSelf()) {
        if (!results.add(aux)) delete aux;
        else std::cout << *aux << " [" << aux->getResult() << "]" << std::endl;
    }

    return 0;
}
