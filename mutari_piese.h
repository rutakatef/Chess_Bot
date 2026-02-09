//
// Created by ruk on 1/17/26.
//

#ifndef SAH_MUTARI_PIESE_H
#define SAH_MUTARI_PIESE_H

#include "Piesa.h"
#include <filesystem>
#include <vector>


vector<int> mutariRege(int index, shared_ptr<Piesa> rege);
vector<int> mutariCal(int index, shared_ptr<Piesa> cal);
vector<int> mutariRegina(int index, shared_ptr<Piesa> regina);
vector<int> mutariNebun(int index, shared_ptr<Piesa> nebun);
vector<int> mutariTura(int index, shared_ptr<Piesa> tura);
vector<int> mutariPion(int index, shared_ptr<Piesa> pion);


#endif //SAH_MUTARI_PIESE_H