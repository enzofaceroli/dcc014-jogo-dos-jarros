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
        int getValorHeuristica();
        int getCustoRaiz();
        vector<Jarro*>& getJarros();

        // Set
        void setCustoRaiz(int custoRaiz);

        // Outros
        Estado* encheJarro(int n);
        Estado* esvaziaJarro(int n);
        Estado* transfereJarros(int n1, int n2);
        Estado* geraPrimeiroEstadoValido();
        vector<Estado*>& gerarProximosEstados();
        vector<pair<Estado*, int>>& gerarProximosEstadosPonderado();
        void printEstado();
        int calculaPesoAresta(Estado* e);
        int calculaValorHeuristica(Estado* e, int obj, bool considerarAresta, bool considerarEstado);

        bool operator<(const Estado& e) {
           return this->valorHeuristica < e.valorHeuristica;   
        }

};



#endif