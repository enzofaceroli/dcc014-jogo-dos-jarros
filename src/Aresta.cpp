#include "Aresta.h"
#include "Estado.h"
#include <iostream>

using namespace std; 

Aresta::Aresta(Estado* e1, Estado* e2, int peso) {
    this->setEstado1(e1);
    this->setEstado2(e2);
    this->setPeso(peso);
}

Estado* Aresta::getEstado1() {
    return this->estado1;
}

Estado* Aresta::getEstado2() {
    return this->estado2;
}

int Aresta::getPeso() {
    return this->peso;
}

void Aresta::setEstado1(Estado* e) {
    this->estado1 = e;
}

void Aresta::setEstado2(Estado* e) {
    this->estado2 = e;
}

void Aresta::setPeso(int peso) {
    this->peso = peso;
}