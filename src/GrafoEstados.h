#ifndef GRAFOESTADOS_H
#define GRAFOESTADOS_H
#include "Jarro.h"
#include "Estado.h"
#include "Aresta.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std; 

class GrafoEstados {
    private:
        Estado* estadoInicial;
        map<Estado*, vector<Estado*>> listaAdjEstados;
        map<Estado*, vector<Aresta*>> listaArestas;

    public:
        GrafoEstados();

        GrafoEstados(int qtdeJarros, int obj);   

        ~GrafoEstados();

        void backtracking();
        void depthFirstSearch(int profundidadeMaxima);
        void breadthFirstSearch();
        void buscaOrdenada();
};

#endif