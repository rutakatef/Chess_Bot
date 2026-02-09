//
// Created by ruk on 1/17/26.
//

#include "initializare_tabla.h"
#include "Piesa.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

void initializare_pioni(vector<shared_ptr<Piesa>>& tabla, const Texture& texPionAlb, const Texture& textPionNegru) {
    double dimensiune = 80.f;
    for (int i = 0; i < 8; i++) {
        int pozAlb = 48 + i;
        int pozNegru = 8 + i;

        Vector2f pozitie_alb(i * dimensiune, dimensiune * 6);
        Vector2f pozitie_negru(i * dimensiune, dimensiune * 1);


        tabla[pozAlb] = make_shared<Pion>(texPionAlb, pozitie_alb, "alb");
        tabla[pozNegru] = make_shared<Pion>(textPionNegru, pozitie_negru, "negru");

    }
}

void initializare_tura(vector<shared_ptr<Piesa>>& tabla, const Texture& texTuraAlba, const Texture& texTuraNeagra) {
    double dimensiune = 80.f;
    for (int i = 0; i < 8; i+=7) {
        int pozAlb = 56 + i;
        int pozNegru = 0 + i;

        Vector2f pozitie_alb(i * dimensiune, dimensiune * 7);
        Vector2f pozitie_negru(i * dimensiune, dimensiune * 0);


        tabla[pozAlb] = make_shared<Tura>(texTuraAlba, pozitie_alb, "alb");
        tabla[pozNegru] = make_shared<Tura>(texTuraNeagra, pozitie_negru, "negru");

    }
}

void initializare_nebun(vector<shared_ptr<Piesa>>& tabla, const Texture& texNebunuAlb, const Texture& texNebunuNegru) {
    double dimensiune = 80.f;
    for (int i = 2; i < 6; i+=3) {
        int pozAlb = 56 + i;
        int pozNegru = 0 + i;

        Vector2f pozitie_alb(i * dimensiune, dimensiune * 7);
        Vector2f pozitie_negru(i * dimensiune, dimensiune * 0);


        tabla[pozAlb] = make_shared<Nebun>(texNebunuAlb, pozitie_alb, "alb");
        tabla[pozNegru] = make_shared<Nebun>(texNebunuNegru, pozitie_negru, "negru");

    }
}

void initializare_cal(vector<shared_ptr<Piesa>>& tabla, const Texture& texCalAlb, const Texture& texCalNegru) {
    double dimensiune = 80.f;
    for (int i = 1; i < 7; i+=5) {
        int pozAlb = 56 + i;
        int pozNegru = 0 + i;

        Vector2f pozitie_alb(i * dimensiune, dimensiune * 7);
        Vector2f pozitie_negru(i * dimensiune, dimensiune * 0);


        tabla[pozAlb] = make_shared<Cal>(texCalAlb, pozitie_alb, "alb");
        tabla[pozNegru] = make_shared<Cal>(texCalNegru, pozitie_negru, "negru");

    }
}

void initializare_regina(vector<shared_ptr<Piesa>>& tabla, const Texture& texReginaAlba, const Texture& texReginaNeagra) {
    double dimensiune = 80.f;
        int pozAlb = 56 + 3;
        int pozNegru = 0 + 3;

        Vector2f pozitie_alb(3 * dimensiune, dimensiune * 7);
        Vector2f pozitie_negru(3 * dimensiune, dimensiune * 0);


        tabla[pozAlb] = make_shared<Regina>(texReginaAlba, pozitie_alb, "alb");
        tabla[pozNegru] = make_shared<Regina>(texReginaNeagra, pozitie_negru, "negru");


}

void initializare_rege(vector<shared_ptr<Piesa>>& tabla, const Texture& texRegeAlb, const Texture& texRegeNegru) {
    double dimensiune = 80.f;
    int pozAlb = 56 + 4;
    int pozNegru = 0 + 4;

    Vector2f pozitie_alb(4 * dimensiune, dimensiune * 7);
    Vector2f pozitie_negru(4 * dimensiune, dimensiune * 0);


    tabla[pozAlb] = make_shared<Rege>(texRegeAlb, pozitie_alb, "alb");
    tabla[pozNegru] = make_shared<Rege>(texRegeNegru, pozitie_negru, "negru");


}
