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

    results.add(new Result( (float)strtol(argv[1], nullptr, 10) ));

    while (true) {
        for (Result *unchecked : results.getUnchecked()) {
            for (Result *aux : unchecked->combineSelf()) {
                if (!results.add(aux)) delete aux;
                else std::cout << *aux << " [" << aux->getResult() << "]" << std::endl;
            }

            std::vector<Result *> all = results.getAll();
            for (Result *aux2 : all) {
                for (Result *aux : unchecked->combine(aux2)) {
                    if (!results.add(aux)) delete aux;
                    else std::cout << *aux << " [" << aux->getResult() << "]" << std::endl;
                }
            }
        }
    }

    return 0;
}
