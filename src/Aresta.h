#ifndef ARESTA_H
#define ARESTA_H
#include <Estado.h>
#include <iostream>

using namespace std;

class Aresta {
    private:
        Estado* estado1;
        Estado* estado2;
        int peso;

    public:
        Aresta();
        Aresta(Estado* e1, Estado* e2, int peso);

        ~Aresta();

        Estado* getEstado1();
        Estado* getEstado2();
        int getPeso();

        void setEstado1(Estado* e); 
        void setEstado2(Estado* e);
        void setPeso(int peso);

        bool operator<(const Aresta& a) const {
            return peso < a.peso;   
        }
};

#endif
