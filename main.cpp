#include <iostream>
#include "combinatoria.h"
#include "results.h"
#include "float_range.h"

#define DEBUG

/**
 * Ejecutad "./combinaciones P M N"
 * P: el número a usar
 * M: las veces que se va a usar el número
 * N: el resultado esperado
 *
 * Ej: obtener el 5 (N) usando tres (M) cuatros (P)
 * ./combinaciones 4 3 5
 */
int main(int argc, char *argv[]) {
    if (argc != 4) return EXIT_FAILURE;

    float searchingFor = (float)strtol(argv[3], nullptr, 10);
    uint8_t usingNNumbers = (uint8_t)strtol(argv[2], nullptr, 10);
    Results results(usingNNumbers);

    results.add(new Result( (float)strtol(argv[1], nullptr, 10) ));

    std::vector<Result *> allUnchecked = results.getUnchecked();
    do {
        std::vector<Result *> all = results.getAll();
        for (Result *unchecked : allUnchecked) {
            for (Result *aux : unchecked->combineSelf()) {
                if (!results.add(aux)) delete aux;
                else {
#ifdef DEBUG
                    std::cout << *aux << " [" << aux->getResult() << "]" << std::endl;
#endif
                    if (aux->getUses() == usingNNumbers && nearlyEqual(aux->getResult(), searchingFor)) std::cout << "[*] " << *aux << " [" << aux->getResult() << "]" << std::endl;
                }
            }

            for (Result *aux2 : all) {
                for (Result *aux : unchecked->combine(aux2)) {
                    if (!results.add(aux)) delete aux;
                    else {
#ifdef DEBUG
                        std::cout << *aux << " [" << aux->getResult() << "]" << std::endl;
#endif
                        if (aux->getUses() == usingNNumbers && nearlyEqual(aux->getResult(), searchingFor)) std::cout << "[*] " << *aux << " [" << aux->getResult() << "]" << std::endl;
                    }
                }
            }
        }

        allUnchecked = results.getUnchecked();
    } while (!allUnchecked.empty());

    return 0;
}
