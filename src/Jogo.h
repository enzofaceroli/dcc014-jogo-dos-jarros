#ifndef JOGO_H
#define JOGO_H
#include <iostream> 
#include <Estado.h>
#include <map>

using namespace std; 

class Jogo {
    private:
        Estado* estadoInicial;
        map<Estado*, bool> estadosVisitados;
        void auxBacktracking(Estado* e);

        int objetivo; 

    public:
        Jogo();
        Jogo(int cap1, int cap2, int obj);

        void setObjetivo(int obj);

        void backtracking();
        void buscaLargura();
        void buscaProfundidade();
        void buscaOrdenada();
        void buscaGulosa();
        void buscaAAst();
        void buscaIDAAst();
};

#endif