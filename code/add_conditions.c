#include <stddef.h>
#include "cnf.h"

//
// LOGIN: <xnovott00>
//

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 1)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
// Pole streets ma velikost num_of_streets a obsahuje vsechny existujuci ulice
//    - pro 0 <= i < num_of_streets predstavuje streets[i] jednu existujici
//      ulici od krizovatky streets[i].crossroad_from ke krizovatce streets[i].crossroad_to
void at_least_one_valid_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets, const Street* streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    assert(streets != NULL);

    // ZDE PRIDAT KOD
    //CHECKS FOR A VALID STREET 
    for(unsigned i = 0; i < num_of_streets; ++i){
        Clause* cl = create_new_clause(formula);
        for(unsigned index = 0; index < num_of_streets; ++index){
            unsigned z = streets[index].crossroad_from;
            unsigned k = streets[index].crossroad_to;
                add_literal_to_clause(cl, true, i, z, k); 
        }
    }

}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 2)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void at_most_one_street_for_each_step(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // ZDE PRIDAT KOD
    //A -> NOT B
    for(unsigned i = 0; i < num_of_streets; ++i){
        for(unsigned z = 0; z < num_of_crossroads; ++z){
            for(unsigned k = 0; k < num_of_crossroads; ++k){
                for(unsigned j = 0; j < num_of_crossroads; ++j){
                    for(unsigned m = 0; m < num_of_crossroads; ++m){
                        if((z != j) || (k != m)){
                            Clause* cl = create_new_clause(formula);
                            add_literal_to_clause(cl, false, i, z, k);
                            add_literal_to_clause(cl, false, i, j, m);
                        }
                    }    
                }
            }
        }            
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 3)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_connected(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);

    // ZDE PRIDAT KOD
    //1. Z1,K1 -> 2. Z2 = K2, M2
    for(unsigned i = 0; i < num_of_streets; ++i){
        for(unsigned z = 0; z < num_of_crossroads; ++z){
            for (unsigned k = 0; k < num_of_crossroads; ++k){
                    Clause* cl = create_new_clause(formula);
                    add_literal_to_clause(cl, false, i, z, k); 
                    for(unsigned m = 0; m < num_of_crossroads; ++m){
                        add_literal_to_clause(cl, true, i + 1, k, m);
                    }
            }
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku 4)
// Křižovatky jsou reprezentovany cisly 0, 1, ..., num_of_crossroads-1
// Cislo num_of_streets predstavuje pocet ulic a proto i pocet kroku cesty
void streets_do_not_repeat(CNF* formula, unsigned num_of_crossroads, unsigned num_of_streets) {
    assert(formula != NULL);
    assert(num_of_crossroads > 0);
    assert(num_of_streets > 0);
    
   // ZDE PRIDAT KOD
   for (unsigned i = 0; i < num_of_streets; ++i) {
        // pro kazdy krok i
        for (unsigned j = 0; j < num_of_streets; ++j) {
            if (i != j) {
                // pro kazdy jiny krok j
                for (unsigned z = 0; z < num_of_crossroads; ++z) {
                    for (unsigned k = 0; k < num_of_crossroads; ++k) {
                        // pro kazdu dvojici krizovatek (z, k)
                        Clause* cl = create_new_clause(formula);
                        add_literal_to_clause(cl, false, i, z, k);
                        add_literal_to_clause(cl, false, j, z, k);
                    }
                }
            }
        }
    }
}
