//
// Created by ruk on 1/17/26.
//

#ifndef SAH_TEST_PIESA_H
#define SAH_TEST_PIESA_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class Piesa {
protected:
    Sprite sprite;
    bool viata;
    string tip, culoare;
    bool prima_mutare = true, dupa_prima_mutare = false;
public:
    Piesa(const Texture& tex, const Vector2f& position, string mtip, string mculoare)  {
        sprite.setTexture(tex);
        sprite.setPosition(position);
        culoare = mculoare;
        tip = mtip;
    }

    virtual ~Piesa() {}

    bool isClicked(Vector2f mousePos) {
        return sprite.getGlobalBounds().contains(mousePos);
    }

    void setPosition(Vector2f pos) {
        sprite.setPosition(pos);
    }

    Vector2f getPosition() const {
        return sprite.getPosition();
    }
    string getCuloare() const {
        return culoare;
    }


    void draw(RenderWindow& window) {
        window.draw(sprite);
    }

    void setTexture(const Texture& tex) {
        sprite.setTexture(tex);
    }
    string getTip() const{
        return tip;
    }
    void setPrimaMutare() {
        prima_mutare = false;
    }
    bool getPrimaMutare() const {
        return prima_mutare;
    }
    void setDupaPrimaMutare(bool x) {
        if (x)
            dupa_prima_mutare = false;
        else
            dupa_prima_mutare = true;
    }
    bool getDupaPrimaMutare() const {
        return dupa_prima_mutare;
    }
};

class Pion : public Piesa {
private:
    bool prima_mutare = true;
public:
    Pion(const Texture& tex, const Vector2f& position, string culoare) : Piesa(tex, position, "pion", culoare) {}
};

class Tura : public Piesa {
private:
    bool prima_mutare = true;
public:
    Tura(const Texture& tex, const Vector2f& position, string culoare) : Piesa(tex, position, "tura", culoare) {}
};

class Nebun : public Piesa {
public:
    Nebun(const Texture& tex, const Vector2f& position, string culoare) : Piesa(tex, position, "nebun", culoare) {}
};

class Cal : public Piesa {
public:
    Cal(const Texture& tex, const Vector2f& position, string culoare) : Piesa(tex, position, "cal", culoare) {}
};

class Regina : public Piesa {
public:
    Regina(const Texture& tex, const Vector2f& position, string culoare) : Piesa(tex, position, "regina", culoare) {}
};

class Rege : public Piesa {
public:
    Rege(const Texture& tex, const Vector2f& position, string culoare) : Piesa(tex, position, "rege", culoare) {}
};


#endif //SAH_TEST_PIESA_H