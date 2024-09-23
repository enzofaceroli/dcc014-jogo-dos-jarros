#ifndef GRAFOESTADOS_H
#define GRAFOESTADOS_H
#include "Jarro.h"
#include "Estado.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std; 

class GrafoEstados {
    private:
        Estado* estadoInicial;

        // Mapa que liga estados e o custo da ligacao
        map<Estado*, vector<pair<Estado*,int>>> listaAdj;

    public:
        GrafoEstados();

        GrafoEstados(int qtdeJarros, int obj);   

        ~GrafoEstados();

        void backtracking();
        void depthFirstSearch();
        void breadthFirstSearch();
        void buscaOrdenada();
        void buscaGulosa();
        void buscaAAST();
        void buscaIDAAST();
};

#endif