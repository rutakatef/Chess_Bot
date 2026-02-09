//
// Created by ruk on 1/17/26.
//

#ifndef SAH_TEST_INITIALIZARE_TABLA_H
#define SAH_TEST_INITIALIZARE_TABLA_H

#include <vector>
#include "Piesa.h"
#include <filesystem>


void initializare_rege(vector<shared_ptr<Piesa>>& tabla, const Texture& texRegeAlb, const Texture& texRegeNegru);
void initializare_regina(vector<shared_ptr<Piesa>>& tabla, const Texture& texReginaAlba, const Texture& texReginaNeagra);
void initializare_cal(vector<shared_ptr<Piesa>>& tabla, const Texture& texCalAlb, const Texture& texCalNegru);
void initializare_nebun(vector<shared_ptr<Piesa>>& tabla, const Texture& texNebunuAlb, const Texture& texNebunuNegru);
void initializare_tura(vector<shared_ptr<Piesa>>& tabla, const Texture& texTuraAlba, const Texture& texTuraNeagra);
void initializare_pioni(vector<shared_ptr<Piesa>>& tabla, const Texture& texPionAlb, const Texture& textPionNegru);



#endif //SAH_TEST_INITIALIZARE_TABLA_H