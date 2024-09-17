#include "GrafoEstados.h"
#include "Estado.h"
#include "Jarro.h"
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>

using namespace std; 

GrafoEstados::GrafoEstados(Estado* e) {
    if(e != NULL) {
        adicionarEstado(e);
        vector<Estado*> proxEstados = e->gerarProximosEstados();
        if(!proxEstados.empty()) {
            for(int i = 0; i < proxEstados.size(); i++) {
                e = proxEstados[i];
                GrafoEstados(e);
            }
        }
    }
}

void GrafoEstados::adicionarEstado(Estado* e) {
    if(this->listaAdjEstados.find(e) == this->listaAdjEstados.end()) {
        this->listaAdjEstados[e] = e->gerarProximosEstados();
    }    
}

