//
// Created by ruk on 1/17/26.
//
#include "mutari_piese.h"
#include "Piesa.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <memory>


using namespace std;

extern std::vector<std::shared_ptr<Piesa>> tabla;

vector<int> mutariPion(int index, shared_ptr<Piesa> pion) {

    vector<int> rez;
    string culoare = pion->getCuloare();
    int direction = (culoare == "alb" ? -8 : 8);

    int linie = index / 8;
    int coloana = index % 8;

    int oneStep = index + direction;
    if (oneStep >= 0 && oneStep < 64 && !tabla[oneStep])
        rez.push_back(oneStep);

    int twoStep = index + 2 * direction;
    if ((culoare == "alb" && linie == 6) || (culoare == "negru" && linie == 1)) {
        if (!tabla[oneStep] && !tabla[twoStep]) {
            rez.push_back(twoStep);
        }
    }

    int enPasant1 = index - 1;
    int enPasant2 = index + 1;

    int diag1 = index + direction - 1;
    int diag2 = index + direction + 1;

    if (coloana > 0 && diag1 >= 0 && diag1 < 64 && tabla[diag1] && tabla[diag1]->getCuloare()!= culoare)
        rez.push_back(diag1);

    if (coloana < 7 && diag2 >= 0 && diag2 < 64 && tabla[diag2] && tabla[diag2]->getCuloare() != culoare)
        rez.push_back(diag2);

   /* if (coloana < 7 && enPasant1 >= 0 && enPasant1 < 64 && tabla[enPasant1] && tabla[enPasant1]->getCuloare() != culoare && tabla[enPasant1]->getDupaPrimaMutare()) {
        rez.push_back(enPasant1 + direction);
        cout << "enpasant + directie = " << enPasant1 + direction  << " tabla[enPasant1 + direction]->getDupaPrimaMutare() ==" << tabla[enPasant1 + direction]->getDupaPrimaMutare() << endl;
    }

    if (coloana < 7 && enPasant2 >= 0 && enPasant2 < 64 && tabla[enPasant2 + direction] && tabla[enPasant2 + direction]->getCuloare() != culoare && tabla[enPasant2 + direction]->getDupaPrimaMutare())
        rez.push_back(enPasant2 + direction);*/

    return rez;
}

vector<int> mutariTura(int index, shared_ptr<Piesa> tura)
{
    vector<int> rez;
    string culoare = tura->getCuloare();

    int linie = index / 8;

    for (int i = index - 1; i >= linie * 8; i--) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
    }

    for (int i = index + 1; i <= linie * 8 + 7; i++) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
    }
    for (int i = index - 8; i >= 0; i -= 8) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
    }

    for (int i = index + 8; i < 64; i += 8) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
    }
    return rez;
}

vector<int> mutariNebun(int index, shared_ptr<Piesa> nebun)
{
    vector<int> rez;
    string culoare = nebun->getCuloare();

    int coloana = index % 8;

    int i = index - 9;
    int c = coloana - 1;
    while (i >= 0 && c >= 0) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
        i -= 9;
        c--;
    }

    i = index - 7;
    c = coloana + 1;
    while (i >= 0 && c <= 7) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
        i -= 7;
        c++;
    }

    i = index + 7;
    c = coloana - 1;
    while (i < 64 && c >= 0) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
        i += 7;
        c--;
    }

    i = index + 9;
    c = coloana + 1;
    while (i < 64 && c <= 7) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
        i += 9;
        c++;
    }

    return rez;
}

vector<int> mutariCal(int index, shared_ptr<Piesa> cal)
{
    vector<int> rez;
    string culoare = cal->getCuloare();

    int linie = index / 8;
    int coloana = index % 8;

    int i = index - 10;
    int c = coloana - 2;
    if (i >= 0 && c >= 0) {
        if (!tabla[i] || tabla[i]->getCuloare() != culoare) {
                rez.push_back(i);
        }
    }

    i = index - 17;
    c = coloana - 1;
    if (i >= 0 && c >= 0) {
        if (!tabla[i] || tabla[i]->getCuloare() != culoare) {
                rez.push_back(i);
        }
    }

    i = index - 6;
    c = coloana + 2;
    if (i >= 0 && c <= 7) {
        if (!tabla[i] || tabla[i]->getCuloare() != culoare) {
                rez.push_back(i);
        }

    }

    i = index - 15;
    c = coloana + 1;
    if (i >= 0 && c <= 7) {
        if (!tabla[i] || tabla[i]->getCuloare() != culoare) {
                rez.push_back(i);
        }

    }

    i = index + 6;
    c = coloana - 2;
    if (i < 64 && c >= 0) {
        if (!tabla[i] || tabla[i]->getCuloare() != culoare) {
                rez.push_back(i);
        }
    }

    i = index + 15;
    c = coloana - 2;
    if (i < 64 && c >= 0) {
        if (!tabla[i] || tabla[i]->getCuloare() != culoare) {
                rez.push_back(i);
        }
    }

    i = index + 10;
    c = coloana + 2;
    if (i < 64 && c <= 7) {
        if (!tabla[i] || tabla[i]->getCuloare() != culoare) {
                rez.push_back(i);
        }
    }

    i = index + 17;
    c = coloana + 2;
    if (i < 64 && c <= 7) {
        if (!tabla[i] || tabla[i]->getCuloare() != culoare) {
                rez.push_back(i);
        }
    }

    return rez;
}

vector<int> mutariRege(int index, shared_ptr<Piesa> rege)
{
    vector<int> rez;
    string culoare = rege->getCuloare();

    int linie = index / 8;
    int coloana = index % 8;

    const int dLinie[8] = { -1,-1,-1, 0, 0, 1,1,1 };
    const int dCol[8]   = { -1, 0,1, -1,1, -1, 0,1 };

    for (int k = 0; k < 8; k++) {
        int nl = linie + dLinie[k];
        int nc = coloana + dCol[k];

        if (nl < 0 || nl > 7 || nc < 0 || nc > 7) continue;

        int idx = nl * 8 + nc;

        if (!tabla[idx]) {
            rez.push_back(idx);
        }
        else if (tabla[idx]->getCuloare() != culoare) {
            rez.push_back(idx);
        }
    }

    return rez;
}



vector<int> mutariRegina(int index, shared_ptr<Piesa> regina)
{
    vector<int> rez;
    string culoare = regina->getCuloare();

    int linie = index / 8;
    int coloana = index % 8;

    for (int i = index - 1; i >= linie * 8; i--) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
    }

    for (int i = index + 1; i <= linie * 8 + 7; i++) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
    }
    for (int i = index - 8; i >= 0; i -= 8) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
    }

    for (int i = index + 8; i < 64; i += 8) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
    }

    int i = index - 9;
    int c = coloana - 1;
    while (i >= 0 && c >= 0) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
        i -= 9;
        c--;
    }

    i = index - 7;
    c = coloana + 1;
    while (i >= 0 && c <= 7) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
        i -= 7;
        c++;
    }

    i = index + 7;
    c = coloana - 1;
    while (i < 64 && c >= 0) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
        i += 7;
        c--;
    }

    i = index + 9;
    c = coloana + 1;
    while (i < 64 && c <= 7) {
        if (tabla[i]) {
            if (tabla[i]->getCuloare() != culoare)
                rez.push_back(i);
            break;
        }
        rez.push_back(i);
        i += 9;
        c++;
    }

    return rez;
}