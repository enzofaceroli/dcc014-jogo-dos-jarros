#include "Jogo.h"
#include "Estado.h"
#include "Jarro.h"
#include <iostream>
#include <vector>

using namespace std; 

Jogo::Jogo(int cap1, int cap2, int obj) {
    this->estadoInicial = new Estado(cap1, cap2, 0, 0, obj);
    this->estadosVisitados = {
        {estadoInicial, true}
    };

    this->setObjetivo(obj);
}

void Jogo::setObjetivo(int obj) {
    if (obj <= 0 || obj > this->estadoInicial->getMaiorCapacidade()) {
        cout << "Selecione um objetivo valido" << endl; 
        exit(0);
    }

    this->objetivo = objetivo;
}

void Jogo::auxBacktracking(Estado* e) {
    
}

void Jogo::backtracking() {
    this->auxBacktracking(this->estadoInicial);
}

