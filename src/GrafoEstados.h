#ifndef GRAFOESTADOS_H
#define GRAFOESTADOS_H
#include <Jarro.h>
#include <Estado.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std; 

class GrafoEstados {
    private:
        Estado* estadoInicial;
        map<Estado*, vector<Estado*>> listaAdjEstados;

    public:
        GrafoEstados();

        GrafoEstados(Estado* estadoInicial);   

        ~GrafoEstados();

        void adicionarEstado(Estado* estado);
        void removerEstado(Estado* estado);

        void backtracking();
        void depthFirstSearch();
        void breadthFirstSearch();
};

#endif