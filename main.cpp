#include <iostream>
#include <filesystem>
#include <string>
#include <random>
#include <vector>
#include <deque>
#include <unordered_map>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "Piesa.h"
#include "mutari_piese.h"
#include "initializare_tabla.h"

using namespace std;
using namespace sf;



vector<shared_ptr<Piesa>> tabla(64);
vector<int> mutari_legale;



struct Pozitii {
    int poz_initiala, poz_finala;
};

unordered_map<string, Pozitii> book_moves;

void Mutari_Manual() {
    ifstream fin("/home/ruk/CLionProjects/sah/cmake-build-debug/deschideri.txt");


    int initial, final;
    string cptabla;
    while (fin >> cptabla >> initial >> final) {
        book_moves.insert({cptabla, {initial, final}});
        cout << "Cartea de deschideri contine " << cptabla << " pozitii." << endl;
        fin.get();
    }
}


string Transformare_tabla_string(vector<shared_ptr<Piesa>> tabla_string) {
    string cptabla;
    for (int i = 0; i < 64; i++) {
        if (tabla_string[i]== nullptr) {
            cptabla += '.';
            continue;
        }
        if (tabla_string[i]->getTip() == "pion" && tabla_string[i]->getCuloare() == "negru") {
            cptabla += 'p';
        }
        else if (tabla_string[i]->getTip() == "tura" && tabla_string[i]->getCuloare() == "negru") {
            cptabla += 't';
        }
        else if (tabla_string[i]->getTip() == "nebun" && tabla_string[i]->getCuloare() == "negru") {
            cptabla += 'n';
        }
        else if (tabla_string[i]->getTip() == "cal" && tabla_string[i]->getCuloare() == "negru") {
            cptabla += 'c';
        }
        else if (tabla_string[i]->getTip() == "regina" && tabla_string[i]->getCuloare() == "negru") {
            cptabla += 'i';
        }
        else if (tabla_string[i]->getTip() == "rege" && tabla_string[i]->getCuloare() == "negru") {
            cptabla += 'b';
        }
        else if (tabla_string[i]->getTip() == "tura" && tabla_string[i]->getCuloare() == "alb") {
            cptabla += 'T';
        }
        else if (tabla_string[i]->getTip() == "nebun" && tabla_string[i]->getCuloare() == "alb") {
            cptabla += 'N';
        }
        else if (tabla_string[i]->getTip() == "cal" && tabla_string[i]->getCuloare() == "alb") {
            cptabla += 'C';
        }
        else if (tabla_string[i]->getTip() == "regina" && tabla_string[i]->getCuloare() == "alb") {
            cptabla += 'I';
        }
        else if (tabla_string[i]->getTip() == "rege" && tabla_string[i]->getCuloare() == "alb") {
            cptabla += 'B';
        }
        else if (tabla_string[i]->getTip() == "pion" && tabla_string[i]->getCuloare() == "alb") {
            cptabla += 'P';
        }
    }
    return cptabla;
}

int pozToIndex(Vector2f poz) {
    int col = poz.x / 80.f;
    int row = poz.y / 80.f;

    if (col < 0 || col > 7 || row < 0 || row > 7) return -1;

    return row * 8 + col;
}



class TablaSah {
private:
    bool esteJucatorulAlbul;
    vector<shared_ptr<Piesa>>& tabla;
public:
    TablaSah(vector<shared_ptr<Piesa>>& t) : tabla(t) {}


    shared_ptr<Piesa> getPiesa(int index) {
        return tabla[index];
    }

    vector<int> getMutariLegale(int index) {
        shared_ptr<Piesa> piesa = tabla[index];

        if (dynamic_cast<Pion*>(piesa.get())) {
            return mutariPion(index, piesa);
        }
        if (dynamic_cast<Tura*>(piesa.get())) {
            return mutariTura(index, piesa);
        }
        if (dynamic_cast<Nebun*>(piesa.get())) {
            return mutariNebun(index, piesa);
        }
        if (dynamic_cast<Cal*>(piesa.get())) {
            return mutariCal(index, piesa);
        }
        if (dynamic_cast<Regina*>(piesa.get())) {
            return mutariRegina(index, piesa);
        }
        if (dynamic_cast<Rege*>(piesa.get())) {
            return mutariRege(index, piesa);
        }
        return {};
    }

    struct Mutare {
        int indexInitial;
        int indexNou;
        shared_ptr<Piesa> piesaMutata;
        shared_ptr<Piesa> piesaCapturata;
    };


    Mutare aplicaMutare(int indexInitial, int indexNou) {
        Mutare mut;
        mut.indexInitial = indexInitial;
        mut.indexNou = indexNou;
        mut.piesaMutata = tabla[indexInitial];
        mut.piesaCapturata = tabla[indexNou];

        tabla[indexNou] = tabla[indexInitial];
        tabla[indexInitial] = nullptr;

        //if (tabla[indexNou]->getDupaPrimaMutare())
          //  tabla[indexNou]->setDupaPrimaMutare(tabla[indexNou]->getPrimaMutare());

       // if (tabla[indexNou]->getPrimaMutare()) {
         //   tabla[indexNou]->setPrimaMutare();
           // tabla[indexNou]->setDupaPrimaMutare(tabla[indexNou]->getPrimaMutare());
        //}

        float x = (indexNou % 8) * 80.f;
        float y = (indexNou / 8) * 80.f;
        tabla[indexNou]->setPosition({x, y});

        return mut;
    }


    void undoMutare(const Mutare& mut) {
        tabla[mut.indexInitial] = mut.piesaMutata;
        tabla[mut.indexNou] = mut.piesaCapturata;

        float xInit = (mut.indexInitial % 8) * 80.f;
        float yInit = (mut.indexInitial / 8) * 80.f;
        mut.piesaMutata->setPosition({xInit, yInit});

        if (mut.piesaCapturata) {
            float xCap = (mut.indexNou % 8) * 80.f;
            float yCap = (mut.indexNou / 8) * 80.f;
            mut.piesaCapturata->setPosition({xCap, yCap});
        }
    }



    int evaluarePozitie() {
        int scor = 0;
        for (int i = 0; i < 64; i++) {
            if (tabla[i]) {
                if (tabla[i]->getCuloare() == "alb") {
                    if (dynamic_cast<Pion*>(tabla[i].get())) scor += 1;
                    else if (dynamic_cast<Cal*>(tabla[i].get())) scor += 3;
                    else if (dynamic_cast<Nebun*>(tabla[i].get())) scor += 3;
                    else if (dynamic_cast<Tura*>(tabla[i].get())) scor += 5;
                    else if (dynamic_cast<Regina*>(tabla[i].get())) scor += 9;
                    else if (dynamic_cast<Rege*>(tabla[i].get())) scor += 1000;
                }
                else {
                    if (dynamic_cast<Pion*>(tabla[i].get())) scor -= 1;
                    else if (dynamic_cast<Cal*>(tabla[i].get())) scor -= 3;
                    else if (dynamic_cast<Nebun*>(tabla[i].get())) scor -= 3;
                    else if (dynamic_cast<Tura*>(tabla[i].get())) scor -= 5;
                    else if (dynamic_cast<Regina*>(tabla[i].get())) scor -= 9;
                    else if (dynamic_cast<Rege*>(tabla[i].get())) scor -= 1000;
                }
            }
        }
        return scor;
    }

    int minimax(int adancime, bool esteBot, int alfa, int beta) {
        if (adancime == 0) {
           // cout << "apelat" << endl;
            return evaluarePozitie();
        }

        int bestScor;

       // cout << "adancime " << adancime << endl;
        if (esteBot) {
            bestScor = -10000;
            for (int i = 0; i < 64; i++) {
                if (tabla[i] && tabla[i]->getCuloare() == "alb") {
                    vector<int> mutariPosibile = getMutariLegale(i);
               /*     cout << tabla[i]->getTip() << " " << tabla[i]->getCuloare() << " ";
                    for (auto it = mutariPosibile.begin(); it != mutariPosibile.end(); it++) {
                        cout <<  *it << " ";
                    }
                    cout << endl;*/
                    for (int mutare : mutariPosibile) {
                        Mutare mut = aplicaMutare(i, mutare);
                        //   cout << "1 " << alfa << " " << beta << endl
                        int scor = minimax(adancime - 1, !esteBot, alfa, beta);
                        bestScor = max(bestScor, scor);
                        alfa = max(alfa, bestScor);
                        undoMutare(mut);
                        if (beta <= alfa) {
                            break;
                        }
                    }
                }
            }
        } else {
            bestScor = 10000;
            for (int i = 0; i < 64; i++) {
                if (tabla[i] && tabla[i]->getCuloare() == "negru") {
                    vector<int> mutariPosibile = getMutariLegale(i);
               /*     cout << tabla[i]->getTip() << " " << tabla[i]->getCuloare() << " ";
                    for (auto it = mutariPosibile.begin(); it != mutariPosibile.end(); it++) {
                        cout <<  *it << " ";
                    }
                    cout << endl;*/
                  //  cout << "mutari posibile : " << mutariPosibile.size() << endl;
                    for (int mutare : mutariPosibile) {
                        Mutare mut = aplicaMutare(i, mutare);
                    //    cout << "2 " << alfa << " " << beta << endl;
                        int scor = minimax(adancime - 1, true, alfa, beta);
                        bestScor = min(bestScor, scor);
                      //  cout << "best scores = " << bestScor << endl;
                        beta = min(beta, bestScor);
                        undoMutare(mut);
                        if (beta <= alfa) {
                            break;
                        }
                    }
                }
            }
        }
       // cout << "best scor = " << bestScor << endl;
        return bestScor;
    }

    void mutareBot() {
        int bestScor = 10000;
        int bestMutare = -1;
        int mutareAleasa = -1;

        for (int i = 0; i < 64; i++) {
            if (tabla[i] && tabla[i]->getCuloare() == "negru") {
                vector<int> mutariPosibile = getMutariLegale(i);
                for (int mutare : mutariPosibile) {
                    Mutare m = aplicaMutare(i, mutare);
                    int scor = minimax(2, true, -10000, 10000);
                    if (scor < bestScor) {
                        bestScor = scor;
                        bestMutare = i;
                        mutareAleasa = mutare;
                    }
                    undoMutare(m);
                }
            }
        }

        if (mutareAleasa != -1) {
            cout << "Botul muta de la " << bestMutare << " la " << mutareAleasa << endl;
            aplicaMutare(bestMutare, mutareAleasa);
        }
    }
};




void GameLoop(RenderWindow& window) {
    Texture texTabla;
    Texture texPionAlb, texPionNegru, texTuraAlba, texTuraNeagra, texNebunuAlb, texNebunuNegru, texCalNegru, texCalAlb, texReginaAlba, texReginaNeagra, texRegeAlb, texRegeNegru;

    std::vector<std::string> possible_paths;
    possible_paths.push_back("../assets/");
    possible_paths.push_back("assets/");

    for (std::string possible_path : possible_paths) {
        if (false == texTabla.loadFromFile(possible_path + "tabla_de_sah.png")) continue;
        if (false == texPionAlb.loadFromFile(possible_path + "pion_alb.png")) continue;
        if (false == texPionNegru.loadFromFile(possible_path + "pion_negru.png")) continue;
        if (false == texTuraAlba.loadFromFile(possible_path + "tura_alba.png")) continue;
        if (false == texTuraNeagra.loadFromFile(possible_path + "tura_neagra.png")) continue;
        if (false == texNebunuAlb.loadFromFile(possible_path + "nebunu_alb.png")) continue;
        if (false == texNebunuNegru.loadFromFile(possible_path + "nebunu_negru.png")) continue;
        if (false == texCalAlb.loadFromFile(possible_path + "cal_alb.png")) continue;
        if (false == texCalNegru.loadFromFile(possible_path + "cal_negru.png")) continue;
        if (false == texReginaAlba.loadFromFile(possible_path + "regina_alba.png")) continue;
        if (false == texReginaNeagra.loadFromFile(possible_path + "regina_neagra.png")) continue;
        if (false == texRegeAlb.loadFromFile(possible_path + "rege_alb.png")) continue;
        if (false == texRegeNegru.loadFromFile(possible_path + "rege_negru.png")) continue;
        break;
    }
    Sprite spriteTabla(texTabla);

    initializare_pioni(tabla, texPionAlb, texPionNegru);
    initializare_tura(tabla, texTuraAlba, texTuraNeagra);
    initializare_nebun(tabla, texNebunuAlb, texNebunuNegru);
    initializare_cal(tabla, texCalAlb, texCalNegru);
    initializare_regina(tabla, texReginaAlba, texReginaNeagra);
    initializare_rege(tabla, texRegeAlb, texRegeNegru);


    TablaSah tablaSah(tabla);

    shared_ptr<Piesa> piesa_selectata = nullptr;
    int index_selectat = -1;
    Vector2f pozitie_initiala;
    Vector2f offset;
    bool esteJucatorulAlb = true;

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                for (int i = 0; i < 64; i++) {
                    if (tabla[i] && tabla[i]->isClicked(mousePos)) {
                        mutari_legale.clear();
                        Pion* pion = dynamic_cast<Pion*>(tabla[i].get());
                        Tura* tura = dynamic_cast<Tura*>(tabla[i].get());
                        Nebun* nebun = dynamic_cast<Nebun*>(tabla[i].get());
                        Cal* cal = dynamic_cast<Cal*>(tabla[i].get());
                        Regina* regina = dynamic_cast<Regina*>(tabla[i].get());
                        Rege* rege = dynamic_cast<Rege*>(tabla[i].get());
                        if (pion && pion->getCuloare() == "alb") {
                            mutari_legale = mutariPion(i, tabla[i]);
                        }
                        else if (tura && tura->getCuloare() == "alb") {
                            mutari_legale = mutariTura(i, tabla[i]);
                        }
                        else if (nebun && nebun->getCuloare() == "alb") {
                            mutari_legale = mutariNebun(i, tabla[i]);
                        }
                        else if (cal && cal->getCuloare() == "alb") {
                            mutari_legale = mutariCal(i, tabla[i]);
                        }
                        else if (regina && regina->getCuloare() == "alb") {
                            mutari_legale = mutariRegina(i, tabla[i]);
                        }
                        else if (rege && rege->getCuloare() == "alb") {
                            mutari_legale = mutariRege(i, tabla[i]);
                        }

                        piesa_selectata = tabla[i];
                        index_selectat = i;
                        pozitie_initiala = tabla[i]->getPosition();
                        offset = tabla[i]->getPosition() - mousePos;
                        break;
                    }
                }
            }

            if (event.type == Event::MouseMoved) {
                if (piesa_selectata) {
                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    piesa_selectata->setPosition(mousePos + offset);
                }
            }

            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                if (piesa_selectata) {
                    Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
                    int newIndex = pozToIndex(mousePos);
                    if (newIndex == -1) {
                        piesa_selectata->setPosition(pozitie_initiala);
                    }
                    else if (index_selectat != newIndex) {
                        float finalX = (newIndex % 8) * 80.f;
                        float finalY = (newIndex / 8) * 80.f;
                        if (tabla[newIndex])
                            tabla[newIndex] = nullptr;

                    //    if (tabla[index_selectat]->getDupaPrimaMutare()) {
                      //      tabla[index_selectat]->setDupaPrimaMutare(tabla[index_selectat]->getDupaPrimaMutare());
                       // }

                       // if (tabla[index_selectat]->getPrimaMutare()) {
                         //   tabla[index_selectat]->setPrimaMutare();
                           // tabla[index_selectat]->setDupaPrimaMutare(tabla[index_selectat]->getDupaPrimaMutare());
                        //}

                        tabla[index_selectat] = nullptr;
                        tabla[newIndex] = piesa_selectata;

                        piesa_selectata->setPosition({finalX, finalY});
                        esteJucatorulAlb = false;
                    }

                    piesa_selectata = nullptr;
                    index_selectat = -1;
                }
                mutari_legale.clear();
            }
        }

        window.clear();
        window.draw(spriteTabla);

        for (auto& p : tabla)
            if (p) p->draw(window);
        for (int idx : mutari_legale) {
            float x = (idx % 8) * 80.f + 40.f;
            float y = (idx / 8) * 80.f + 40.f;

            CircleShape circle(15.f);
            circle.setFillColor(Color(0, 255, 0, 120));
            circle.setOrigin(15.f, 15.f);
            circle.setPosition(x, y);

            window.draw(circle);
        }
        if (!esteJucatorulAlb) {
            string copie_tabla;
            copie_tabla = Transformare_tabla_string(tabla);
            cout << copie_tabla << " " << copie_tabla.length() << endl;
            if (auto it  = book_moves.find(copie_tabla); it != book_moves.end()) {
                tablaSah.aplicaMutare(it->second.poz_initiala, it->second.poz_finala);
            }
            else
                tablaSah.mutareBot();
            for (int i = 0; i < 64; i++)
                tabla[i] = tablaSah.getPiesa(i);
            esteJucatorulAlb = true;
        }

        window.display();

    }
}



int main() {
    Mutari_Manual();
    RenderWindow window(VideoMode(640, 640), "Sah SFML");

    GameLoop(window);

    return 0;
}