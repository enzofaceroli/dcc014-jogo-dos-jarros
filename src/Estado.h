#ifndef ESTADO_H
#define ESTADO_H
#include "Jarro.h"
#include <iostream> 
#include <vector>
#include <string>

using namespace std; 

class Estado {
    private:
        bool estadoFinal;
        int qtdeJarros; 
        vector<Jarro*> jarros;

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
        int getValorHeuristica();
        vector<Jarro*>& getJarros();

        // Set
        void setValorHeuristica(int valorHeuristica);
        void setPesoTotal(int pesoTotal);

        // Outros
        Estado* encheJarro(int n);
        Estado* esvaziaJarro(int n);
        Estado* transfereJarros(int n1, int n2);
        vector<pair<Estado*, int>> gerarProximosEstadosPonderado(int obj);
        void printEstado();
        int calculaPesoAresta(Estado* e);
        int calculaValorHeuristica(int obj);

        bool operator < (const Estado& e) {
           return this->valorHeuristica < e.valorHeuristica;   
        }
};



#endif