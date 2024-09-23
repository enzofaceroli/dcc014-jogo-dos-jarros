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


typedef pair<Estado*, int> pd;

struct myComp {
    constexpr bool operator()(
        pair<Estado*, int> const& a,
        pair<Estado*, int> const& b)
        const noexcept
    {
        return a.second > b.second;
    }
};

GrafoEstados::GrafoEstados(int qtdeJarros, int obj) {
    this->estadoInicial = new Estado(qtdeJarros, obj);

    Estado* e = this->estadoInicial;

    listaAdj[e] = e->gerarProximosEstadosPonderado(obj);

    stack<Estado*> estadosAdicionar;
    estadosAdicionar.push(e);   

    while(!estadosAdicionar.empty()) {
        e = estadosAdicionar.top();
        estadosAdicionar.pop();

        vector<pair<Estado*, int>> estadosSeguintes = e->gerarProximosEstadosPonderado(obj);
        // reverse(estadosSeguintes.begin(), estadosSeguintes.end());

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i].first;
            // Overload no operador == permite com que dois estados diferentes sejam iguais pela sua sequencia de jarros
            if(listaAdj.find(aux) == listaAdj.end()) {
                listaAdj[aux] = aux->gerarProximosEstadosPonderado(obj);
                estadosAdicionar.push(aux);
            } 
        }
    }
}

void GrafoEstados::backtracking() {
    cout << "Iniciando backtracking" << endl;
    Estado* e = this->estadoInicial;
    Estado* anterior = NULL;

    int profundidade = 0; 
    int qtdeEstadosVisitados = 0;
    bool sucesso = false;
    bool fracasso = false; 

    map<Estado*, bool> estadosVisitados; 

    for(auto it = this->listaAdj.cbegin(); it != this->listaAdj.cend(); ++it) {
        Estado* e = it->first;
        estadosVisitados[e] = false;
    }

    estadosVisitados[e] = true;
    qtdeEstadosVisitados++;

    cout << "Caminho: ";
    e->printEstado();

    while(!(sucesso || fracasso)) {
        anterior = e;
        for(int i = 0; i < this->listaAdj[e].size(); i++) {
            Estado* aux = this->listaAdj[e][i].first;
            if(estadosVisitados[aux] != true) {
                e = aux;
                profundidade++;
                qtdeEstadosVisitados++;
                cout << " -> ";
                e->printEstado();
                break;
            }
        }

        if(e != anterior) {
            if(e == this->estadoInicial) {
                fracasso = true;
            }

            if (e->ehEstadoFinal()) {
               sucesso = true;
               
                cout << "Numero de estados visitados: " << estadosVisitados.size() << endl;
                cout << "Profundidade: " << profundidade << endl;   
            } 
        } else {
            e = anterior;
            profundidade--;
        }
    }
}

void GrafoEstados::depthFirstSearch() {
    cout << "Iniciando DFS" << endl;

    int profundidadeMaxima;
    
    cout << "Insira profundidade maxima: " << endl;
    cin >> profundidadeMaxima;

    Estado* e = this->estadoInicial;
    int profundidade = 0;
    int qtdeEstadosVisitados = 0;
    bool sucesso = false;

    map<Estado*, bool> estadosVisitados;

    for(auto it = this->listaAdj.cbegin(); it != this->listaAdj.cend(); ++it) {
        Estado* e = it->first;
        estadosVisitados[e] = false;
    }

    stack<Estado*> estadosVisitar;

    estadosVisitados[e] = true;
    qtdeEstadosVisitados++;
    estadosVisitar.push(e);

    while(!estadosVisitar.empty() || profundidade <= profundidadeMaxima) {
        e = estadosVisitar.top();
        estadosVisitar.pop();

        if(e->ehEstadoFinal()) {
            cout << "Numero de estados visitados: " << qtdeEstadosVisitados << endl;
            cout << "Caminho: ";
            for (auto it = estadosVisitados.cbegin(); it != estadosVisitados.cend(); ++it){
                if(it->second == true) {
                    it->first->printEstado();
                }
                cout << " -> ";
            }
            cout << "fim" << endl;
            cout << "Profundidade: " << profundidade << endl;
            sucesso = true;
            break;
        }

        if(profundidade < profundidadeMaxima) {
            vector<pair<Estado*, int>> estadosSeguintes = this->listaAdj[e];
            profundidade++;
            reverse(estadosSeguintes.begin(), estadosSeguintes.end());

            for(int i = 0; i < estadosSeguintes.size(); i++) {
                Estado* aux = estadosSeguintes[i].first;
                if(estadosVisitados[aux] != true) {
                    estadosVisitados[aux] = true;
                    qtdeEstadosVisitados++;
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
    cout << "Iniciando BFS" << endl;

    Estado* e = this->estadoInicial;
    int profundidade = 0;
    int qtdeEstadosVisitados = 0;
    bool sucesso = false;

    map<Estado*, bool> estadosVisitados;

    for(auto it = this->listaAdj.cbegin(); it != this->listaAdj.cend(); ++it) {
        Estado* e = it->first;
        estadosVisitados[e] = false;
    }

    queue<Estado*> estadosVisitar;

    estadosVisitados[e] = true;
    qtdeEstadosVisitados++;
    estadosVisitar.push(e);

    while(!estadosVisitar.empty()) {
        e = estadosVisitar.front();
        estadosVisitar.pop();

        if(e->ehEstadoFinal()) {    
            cout << "Numero de estados visitados: " << qtdeEstadosVisitados << endl;
            cout << "Caminho: ";
            for (auto it = estadosVisitados.cbegin(); it != estadosVisitados.cend(); ++it){
                if(it->second == true) {
                    it->first->printEstado();
                }
                cout << " -> ";
            }
            cout << "fim" << endl;
            cout << "Profundidade: " << profundidade << endl;
            sucesso = true;
            break;
        }

        vector<pair<Estado*, int>> estadosSeguintes = this->listaAdj[e];
        profundidade++;

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i].first;
            if(estadosVisitados[aux] != true) {
                estadosVisitados[aux] = true;
                qtdeEstadosVisitados++;
                estadosVisitar.push(aux);
            }
        }
    }

    if(!sucesso) {
        cout << "O algoritmo nao encontrou solucao" << endl;
    }
}

void GrafoEstados::buscaOrdenada() {
        cout << "Iniciando ordenada" << endl;

    Estado* e = this->estadoInicial;
    Estado* objetivoMenorCusto = NULL;
    int qtdeEstadosVisitados = 0;

    // Mapa de estados visitados e o custo para visita-los
    map<Estado*, int> estadosVisitados;

    for(auto it = listaAdj.cbegin(); it != listaAdj.cend(); it++) {
        Estado* e = it->first;
        estadosVisitados[e] = INT16_MAX;
    }

    priority_queue<pd, vector<pd>, myComp> estadosVisitar; 

    estadosVisitados[e] = 0;
    qtdeEstadosVisitados++;

    estadosVisitar.push(make_pair(e, 0));

    while(!estadosVisitar.empty()) {
        e = estadosVisitar.top().first;
        estadosVisitar.pop();

        if(e->ehEstadoFinal()) {
            if(objetivoMenorCusto == NULL) {
                objetivoMenorCusto = e;
            } else {
                if(estadosVisitados[e] < estadosVisitados[objetivoMenorCusto]) {
                    objetivoMenorCusto = e;
                }
            }
        }

        vector<pair<Estado*, int>> estadosSeguintes = this->listaAdj[e];

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i].first;
            int custo = estadosVisitados[e] + estadosSeguintes[i].second;

            if(custo < estadosVisitados[aux] ) {
                estadosVisitados[aux] = custo;
                pair<Estado*, int> p = make_pair(aux, custo);
                estadosVisitar.push(p);
            }
        }
    }
    
    if(objetivoMenorCusto == NULL) {
        cout << "O algoritmo nao encontrou solucao" << endl;
    }
}

void GrafoEstados::buscaGulosa() {
    cout << "Iniciando gulosa" << endl;

    Estado* e = this->estadoInicial;
    int profundidade = 0;
    int qtdeEstadosVisitados = 0;
    bool sucesso = false;

    map<Estado*, bool> estadosVisitados;

    for(auto it = this->listaAdj.cbegin(); it != this->listaAdj.cend(); ++it) {
        Estado* e = it->first;
        estadosVisitados[e] = false;
    }

    priority_queue<Estado*> estadosVisitar; 

    estadosVisitados[e] = true;
    qtdeEstadosVisitados++;
    estadosVisitar.push(e);

    while(!estadosVisitar.empty()) {
        e = estadosVisitar.top();
        estadosVisitar.pop();

        if(e->ehEstadoFinal()) {
            cout << "Numero de estados visitados: " << qtdeEstadosVisitados << endl;
            cout << "Caminho: ";
            for (auto it = estadosVisitados.cbegin(); it != estadosVisitados.cend(); ++it){
                if(it->second == true) {
                    it->first->printEstado();
                }
                cout << " -> ";
            }
            cout << "fim" << endl;
            cout << "Profundidade: " << profundidade << endl;
            sucesso = true;
            break;
        }        
    }

    vector<pair<Estado*, int>> estadosSeguintes = this->listaAdj[e];
    profundidade++;

    for(int i = 0; i < estadosSeguintes.size(); i++) {
        Estado* aux = estadosSeguintes[i].first;
        if(estadosVisitados[aux] != true) {
            estadosVisitados[aux] = true;
            estadosVisitar.push(aux);
        }
    }

    if(!sucesso) {
        cout << "O algoritmo nao encontrou solucao" << endl;
    }
}

void GrafoEstados::buscaAAST() {
    cout << "Iniciando A*" << endl;

    Estado* e = this->estadoInicial;
    Estado* objetivoMenorCusto = NULL;
    int qtdeEstadosVisitados = 0;

    // Mapa de estados visitados e o custo para visita-los
    map<Estado*, int> estadosVisitados;

    for(auto it = listaAdj.cbegin(); it != listaAdj.cend(); it++) {
        Estado* e = it->first;
        estadosVisitados[e] = INT16_MAX;
    }

    priority_queue<pd, vector<pd>, myComp> estadosVisitar; 

    estadosVisitados[e] = 0;
    qtdeEstadosVisitados++;

    estadosVisitar.push(make_pair(e, 0));

    while(!estadosVisitar.empty()) {
        e = estadosVisitar.top().first;
        estadosVisitar.pop();

        if(e->ehEstadoFinal()) {
            if(objetivoMenorCusto == NULL) {
                objetivoMenorCusto = e;
            } else {
                if(estadosVisitados[e] < estadosVisitados[objetivoMenorCusto]) {
                    objetivoMenorCusto = e;
                }
            }
        }

        vector<pair<Estado*, int>> estadosSeguintes = this->listaAdj[e];

        for(int i = 0; i < estadosSeguintes.size(); i++) {
            Estado* aux = estadosSeguintes[i].first;
            int custo = estadosVisitados[e] + estadosSeguintes[i].second + aux->getValorHeuristica();

            if(custo < estadosVisitados[aux] ) {
                estadosVisitados[aux] = custo;
                pair<Estado*, int> p = make_pair(aux, custo);
                estadosVisitar.push(p);
            }
        }
    }
    
    if(objetivoMenorCusto == NULL) {
        cout << "O algoritmo nao encontrou solucao" << endl;
    }
}
