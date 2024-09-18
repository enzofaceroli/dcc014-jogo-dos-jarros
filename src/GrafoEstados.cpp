#include "GrafoEstados.h"
#include "Estado.h"
#include "Jarro.h"
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

    listaAdj[e] = e->gerarProximosEstadosPonderado();

    stack<Estado*> estadosAdicionar;
    estadosAdicionar.push(e);   

    while(!estadosAdicionar.empty()) {
        e = estadosAdicionar.top();
        estadosAdicionar.pop();

        vector<pair<Estado*, int>> estadosSeguintes = e->gerarProximosEstadosPonderado();
        reverse(estadosSeguintes.begin(), estadosSeguintes.end());

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i].first;
            if(listaAdj.find(aux) == listaAdj.end()) {
                listaAdj[aux] = aux->gerarProximosEstadosPonderado();
                estadosAdicionar.push(aux);
            } 
        }
    }
}

void GrafoEstados::backtracking() {
    Estado* e = this->estadoInicial;
    Estado* anterior = NULL;
    int estadosVisitados = 1;
    int profundidade = 0; 
    bool sucesso = false;
    bool fracasso = false; 

    cout << "Caminho: ";
    e->printEstado();

    while(!(sucesso || fracasso)) {
        if(e->geraPrimeiroEstadoValido() != NULL) {
            anterior = e;
            e = e->geraPrimeiroEstadoValido();
            profundidade++;
            
            cout << " -> ";
            e->printEstado();

            if (e->ehEstadoFinal()) {
               sucesso = true;
               
                cout << "Numero de estados visitados: " << estadosVisitados << endl;
                cout << "Profundidade: " << profundidade << endl;   
            }
        } else {
            if(e == estadoInicial) {
                fracasso = true;
            } else {
                e = anterior;
                profundidade--;
                cout << "Nao foi possivel encontrar solucao" << endl;
            }
        }
    }
}

void GrafoEstados::depthFirstSearch(int profundidadeMaxima) {
    Estado* e = this->estadoInicial;
    int profundidade = 0;
    bool sucesso = false;

    vector<Estado*> estadosVisitados;
    stack<Estado*> estadosVisitar;

    estadosVisitados.push_back(e);
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

        vector<pair<Estado*, int>> estadosSeguintes = this->listaAdj[e];
        profundidade++;
        reverse(estadosSeguintes.begin(), estadosSeguintes.end());

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i].first;
            if(aux != NULL) {
                int cnt = count(estadosVisitados.begin(), estadosVisitados.end(), aux);
                if(cnt == 0) {
                    estadosVisitados.push_back(aux);
                    estadosVisitar.push(aux);
                }
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

        vector<pair<Estado*, int>> estadosSeguintes = this->listaAdj[e];
        profundidade++;

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i].first;
            if(aux != NULL) {
                int cnt = count(estadosVisitados.begin(), estadosVisitados.end(), aux);
                if(cnt == 0) {
                    estadosVisitados.push_back(aux);
                    estadosVisitar.push(aux);
                }
            }
        }
    }

    if(!sucesso) {
        cout << "O algoritmo nao encontrou solucao na profundidade dada" << endl;
    }
}

void GrafoEstados::buscaOrdenada() {
    Estado* e = this->estadoInicial;
    e->setCustoRaiz(0);
    Estado* menorCaminho = NULL;
    int profundidade = 0;
    bool sucesso = false;

    vector<Estado*> estadosVisitados;
    priority_queue<Estado*> estadosVisitar;  

    estadosVisitados.push_back(e);
    estadosVisitar.push(e);

    while(!estadosVisitar.empty()) {
        e = estadosVisitar.top();
        estadosVisitar.pop();

        if(e->ehEstadoFinal()) {
            sucesso = true;

            if(menorCaminho == NULL) {
                menorCaminho = e;
            }

            if(e <= menorCaminho) { 
                menorCaminho = e;
            }
        }
        
        vector<Estado*> estadosSeguintes;
        for(int i = 0; i < this->listaAdj[e].size(); i++) {
            estadosSeguintes.push_back(this->listaAdj[e][i].first);
        }

        // for(int i = 0; i < estadosSeguintes.size(); i++) {
        // // ESSA FUNCAO TEM QUE MUDAR PARA CADA METODO DE BUSCA + USAR SO ATRIBUTO VALORHEURISTICA NO ESTADO
        //     estadosSeguintes[i]->setCustoRaiz(e->getCustoRaiz() + e->calculaPesoAresta(estadosSeguintes[i]));
        // }

        // sort(estadosSeguintes.begin(), estadosSeguintes.end());
        profundidade++;

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i];
            if(aux != NULL) {
                int cnt = count(estadosVisitados.begin(), estadosVisitados.end(), aux);
                if(cnt == 0) {
                    estadosVisitados.push_back(aux);
                    estadosVisitar.push(aux);
                }
            } 
        }
    }

    if(!sucesso) {
        cout << "O algoritmo nao encontrou solucao" << endl;
    } else {
        cout << "Estado objetivo com menor custo ";
        menorCaminho->printEstado();

        cout << "Numero de estados visitados: " << estadosVisitados.size() << endl;
        cout << "Caminho: ";
        estadosVisitados[0] -> printEstado();
        for(int i = 1; i < estadosVisitados.size(); i++) {
            cout << " -> ";
            estadosVisitados[i] -> printEstado();
        }
        cout << endl;
        cout << "Profundidade: " << profundidade << endl;
    }
}