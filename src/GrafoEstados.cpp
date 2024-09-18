#include "GrafoEstados.h"
#include "Estado.h"
#include "Jarro.h"
#include "Aresta.h"
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std; 

GrafoEstados::GrafoEstados(int qtdeJarros, int obj) {
    this->estadoInicial = new Estado(qtdeJarros, obj);

    Estado* e = this->estadoInicial;

    listaAdjEstados[e] = e->gerarProximosEstados();

    stack<Estado*> estadosAdicionar;
    estadosAdicionar.push(e);

    while(!estadosAdicionar.empty()) {
        e = estadosAdicionar.top();
        estadosAdicionar.pop();

        vector<Estado*> estadosSeguintes = e->gerarProximosEstados();
        reverse(estadosSeguintes.begin(), estadosSeguintes.end());

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i];
            if(listaAdjEstados.find(aux) == listaAdjEstados.end()) {
                listaAdjEstados[aux] = aux->gerarProximosEstados();
                estadosAdicionar.push(aux);
            } 
        }
    }

    for(auto it : listaAdjEstados) {
        Estado* e1 = it.first;
        for(int i = 0; i < it.second.size(); i++) {
            Estado* e2 = it.second[i];
            Aresta* a = new Aresta(e1, e2, e1->calculaPesoAresta(e2));
            this->listaArestas[e1].push_back(a);
        }
    }
}

void GrafoEstados::depthFirstSearch(int profundidadeMaxima) {
    Estado* e = this->estadoInicial;
    int profundidade = 0;
    bool sucesso = false;

    vector<Estado*> estadosVisitados;
    estadosVisitados.push_back(e);

    stack<Estado*> estadosVisitar;
    estadosVisitar.push(e);

    while(!estadosVisitar.empty() || profundidade <= profundidadeMaxima) {
        e = estadosVisitar.top();
        estadosVisitar.pop();

        if(e->ehEstadoFinal()) {
            cout << "Numero de estados visitados: " << estadosVisitados.size() << endl;
            cout << "Caminho: ";
            estadosVisitados[0] -> printEstado();
            for(int i = 1; i < estadosVisitados.size(); i++) {
                cout << " -> ";
                estadosVisitados[i] -> printEstado();
            }
            cout << endl;
            cout << "Profundidade: " << profundidade << endl;
            sucesso = true;
            break;
        }

        vector<Estado*> estadosSeguintes = this->listaAdjEstados[e];
        profundidade++;
        reverse(estadosSeguintes.begin(), estadosSeguintes.end());

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i];
            int cnt = count(estadosVisitados.begin(), estadosVisitados.end(), aux);
            if(cnt == 0 && aux != NULL) {
                estadosVisitados.push_back(aux);
                estadosVisitar.push(aux);
            } 
        }
    }

    if(!sucesso) {
        cout << "O algoritmo nao encontrou solucao na profundidade dada" << endl;
    }
}

void GrafoEstados::breadthFirstSearch() {
    Estado* e = this->estadoInicial;
    int profundidade = 0;
    bool sucesso = false;

    vector<Estado*> estadosVisitados;
    estadosVisitados.push_back(e);

    queue<Estado*> estadosVisitar;
    estadosVisitar.push(e);

    while(!estadosVisitar.empty()) {
        e = estadosVisitar.front();
        estadosVisitar.pop();

        if(e->ehEstadoFinal()) {
            cout << "Numero de estados visitados: " << estadosVisitados.size() << endl;
            cout << "Caminho: ";
            estadosVisitados[0] -> printEstado();
            for(int i = 1; i < estadosVisitados.size(); i++) {
                cout << " -> ";
                estadosVisitados[i] -> printEstado();
            }
            cout << endl;
            cout << "Profundidade: " << profundidade << endl;
            sucesso = true;
            break;
        }

        vector<Estado*> estadosSeguintes = this->listaAdjEstados[e];
        profundidade++;

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i];
            int cnt = count(estadosVisitados.begin(), estadosVisitados.end(), aux);
            if(cnt == 0 && aux != NULL) {
                estadosVisitados.push_back(aux);
                estadosVisitar.push(aux);
            } 
        }
    }

    if(!sucesso) {
        cout << "O algoritmo nao encontrou solucao na profundidade dada" << endl;
    }
}

void GrafoEstados::buscaOrdenada() {
    Estado* e = this->estadoInicial;
    int profundidade = 0;
    bool sucesso = false;

    vector<Estado*> estadosVisitados;
    queue<Estado*> estadosVisitar;

    estadosVisitados.push_back(e);
    estadosVisitar.push(e);

    while(!estadosVisitar.empty()) {
        e = estadosVisitar.front();
        estadosVisitar.pop();

        if(e->ehEstadoFinal()) {
            cout << "Numero de estados visitados: " << estadosVisitados.size() << endl;
            cout << "Caminho: ";
            estadosVisitados[0] -> printEstado();
            for(int i = 1; i < estadosVisitados.size(); i++) {
                cout << " -> ";
                estadosVisitados[i] -> printEstado();
            }
            cout << endl;
            cout << "Profundidade: " << profundidade << endl;
            sucesso = true;
            break;
        }

        vector<Aresta*> arestaEstadosSeguintes = this->listaArestas[e];
        sort(arestaEstadosSeguintes.begin(), arestaEstadosSeguintes.end());
        
        vector<Estado*> estadosSeguintes;

        for(int i = 0; i < arestaEstadosSeguintes.size(); i++) {
            estadosSeguintes.push_back(arestaEstadosSeguintes[i]->getEstado2());
        }   

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i];
            int cnt = count(estadosVisitados.begin(), estadosVisitados.end(), aux);
            if(cnt == 0 && aux != NULL) {
                estadosVisitados.push_back(aux);
                estadosVisitar.push(aux);
            } 

            // visitar a b c
        }

        profundidade++;
    }

    if(!sucesso) {
        cout << "O algoritmo nao encontrou solucao na profundidade dada" << endl;
    }
}