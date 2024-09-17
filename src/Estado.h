#ifndef ESTADO_H
#define ESTADO_H
#include <Jarro.h>
#include <iostream> 
#include <utility>

using namespace std; 

class Estado {
    private:
        bool estadoFinal;

        pair<Jarro*, Jarro*> jarros;
        
        vector<Estado*> estadosSeguintes;

    public: 
        Estado();

        Estado(int cap1, int cap2, int cont1, int cont2, int obj);

        ~Estado(); 

        // Get
        bool ehEstadoFinal();
        int getCapacidade(int n);
        int getConteudo(int n);
        int getMaiorCapacidade();

        // Outros
        Estado* encheJarro(int n);
        Estado* esvaziaJarro(int n);
        Estado* transfere12();
        Estado* transfere21();
        vector<Estado*>& gerarProximosEstados();
        void printEstado();
};



#endif