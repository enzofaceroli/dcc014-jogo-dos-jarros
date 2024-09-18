#ifndef ESTADO_H
#define ESTADO_H
#include <Jarro.h>
#include <iostream> 
#include <vector>

using namespace std; 

class Estado {
    private:
        bool estadoFinal;
        int qtdeJarros; 
        vector<Jarro*> jarros;

        int custoRaiz;
        int valorHeuristica;

    public: 
        Estado();

        Estado(int qtdeJarros, int obj);

        ~Estado(); 

        // Get
        bool ehEstadoFinal();
        int getCapacidade(int n);
        int getConteudo(int n);
        int getMaiorCapacidade();
        int getConteudoTotal();
        vector<Jarro*>& getJarros();

        // Outros
        Estado* encheJarro(int n);
        Estado* esvaziaJarro(int n);
        Estado* transfereJarros(int n1, int n2);
        vector<Estado*>& gerarProximosEstados();
        void printEstado();
        int calculaValorHeuristica(int obj);
        int calculaPesoAresta(Estado* e);
};



#endif