#include "Estado.h"
#include "Jarro.h"
#include <iostream> 
#include <vector>
#include <map>

using namespace std; 

Estado::Estado(int qtdeJarros, int obj) {
    this->estadoFinal = false;
    this->qtdeJarros = qtdeJarros;
    Jarro* jarro = new Jarro();

    for(int i = 0; i < qtdeJarros; i++) {
        int cap;
        int cont;

        cout << "Selecione a capacidade do jarro " << i << ": ";
        cin >> cap;
        cout << endl;

        cout << "Selecione o conteudo inicial do jarro " << i << ": ";
        cin >> cont;
        cout << endl;

        jarro->setCapacidade(cap);
        jarro->setConteudo(cont);

        Jarro* aux = jarro;
        this->jarros.push_back(aux);
    }

    for(int i = 0; i < qtdeJarros; i++) {
        if(jarros[i]->getConteudo() == obj) {
            this->estadoFinal = true;
        }
    }

    delete jarro;

    this->valorHeuristica = this->calculaValorHeuristica(obj);
}

 
bool Estado::ehEstadoFinal() {
    return this->estadoFinal;
}

int Estado::getCapacidade(int n) {
    if(n < 0 || n >= this->qtdeJarros) {
        return this->jarros[n]->getCapacidade();
    }

    cout << "Selecione um jarro valido" << endl;
}

int Estado::getConteudo(int n) {
    if(n < 0 || n >= this->qtdeJarros) {
        cout << "Selecione um jarro valido" << endl;        
    }

    return this->jarros[n]->getConteudo();
}

int Estado::getMaiorCapacidade() {
    return (this->getConteudo(1) >= this->getConteudo(2) ? this->getConteudo(1) : this->getConteudo(2));
}

int Estado::getConteudoTotal() {
    int total = 0;
    for(int i = 0; i < this->jarros.size(); i++) {
        total = total + this->jarros[i]->getConteudo();
    }

    return total;
}

int Estado::getValorHeuristica() {
    return this->valorHeuristica;
}

vector<Jarro*>&Estado::getJarros() {
    return this->jarros;
}


void Estado::setValorHeuristica(int valorHeuristica) {
    this->valorHeuristica = valorHeuristica;
}

Estado* Estado::encheJarro(int n) {
    Estado* novoEstado = this; 

    if(n < 0 || n >= this->qtdeJarros) {
        cout << "Selecione um jarro valido" << endl;    
        novoEstado = NULL;    
    } else if(this->jarros[n]->cheio()) {
        cout << "Jarro ja esta cheio" << endl;
        novoEstado = NULL;
    } else {
        novoEstado->getJarros()[n]->encherJarro();
    }

    return novoEstado;
} 

Estado* Estado::esvaziaJarro(int n) {
    Estado* novoEstado = this; 

    if(n < 0 || n >= this->qtdeJarros) {
        cout << "Selecione um jarro valido" << endl;    
        novoEstado = NULL;    
    } else if(this->jarros[n]->vazio()) {
        cout << "Jarro ja esta vazio" << endl;
        novoEstado = NULL;
    } else {
        novoEstado->getJarros()[n]->esvaziarJarro();
    }

    return novoEstado;
} 

Estado* Estado::transfereJarros(int n1, int n2) {
    Estado* novoEstado = this;

    Jarro* jarro1 = novoEstado->getJarros()[n1];
    Jarro* jarro2 = novoEstado->getJarros()[n2];

    if(jarro1->vazio() || jarro2->cheio()) {
        return NULL;
    }

    int quantidadeTransferir; 

    // Se conteudo jarro 1 < espaco vazio => transferir conteudo jarro 1 
    if(jarro1->getConteudo() <= jarro2->getEspacoVazio()) {
        quantidadeTransferir = jarro1->getConteudo();
    }

    // Se conteudo jarro 1 > espaço vazio => transferir espaco vazio
    if(jarro1->getConteudo() > jarro2->getEspacoVazio()) {
        quantidadeTransferir = jarro2->getEspacoVazio();
    }

    jarro1->setConteudo(jarro1->getConteudo() - quantidadeTransferir);
    jarro2->setConteudo(jarro2->getConteudo() + quantidadeTransferir);

    return novoEstado;
}

// Estado* Estado::geraPrimeiroEstadoValido() {
//     for(int i = 0; i < qtdeJarros; i++) {
//         if(this->encheJarro(i) != NULL) {
//             return this->encheJarro(i);
//         }
//     }

//     for(int i = 0; i < qtdeJarros; i++) {
//         if(this->esvaziaJarro(i) != NULL) {
//             return this->esvaziaJarro(i);
//         }
//     }

//     for(int i = 0; i < qtdeJarros; i++) {
//         for(int j = 0; j < qtdeJarros; j++) {
//             if(i != j) {
//                 if(this->transfereJarros(i, j) != NULL) {
//                     return this->transfereJarros(i, j);
//                 }
//             }
//         }
//     }

//     return NULL; 
// }

// vector<Estado*>& Estado::gerarProximosEstados() {
//     vector<Estado*> proximosEstados;
//     Estado* e;

//     for(int i = 0; i < qtdeJarros; i++) {
//         e = this->encheJarro(i);
//         if(e != NULL) {
//             proximosEstados.push_back(e);
//         }
//     }

//     for(int i = 0; i < qtdeJarros; i++) {
//         e = this->esvaziaJarro(i);
//         if(e != NULL) {
//             proximosEstados.push_back(e);
//         }
//     }

//     for(int i = 0; i < qtdeJarros; i++) {
//         for(int j = 0; j < qtdeJarros; j++) {
//             if(i != j) {
//                 e = this->transfereJarros(i, j);
//                 if(e != NULL) {
//                     proximosEstados.push_back(e);
//                 }
//             }
//         }
//     }

//     return proximosEstados;
// }

vector<pair<Estado*, int>> Estado::gerarProximosEstadosPonderado(int obj) {
    vector<pair<Estado*, int>> proximosEstadosPonderados;
    Estado* e;

    int custo;
    int custoTotal;

    for(int i = 0; i < qtdeJarros; i++) {
        e = this->encheJarro(i);
        custo = this->calculaPesoAresta(e);

        e->setValorHeuristica(e->calculaValorHeuristica(obj));

        pair<Estado*, int> proxEstadoPonderado(e, custo);
        
        if(e != NULL) {
            proximosEstadosPonderados.push_back(proxEstadoPonderado);
        }
    }

    for(int i = 0; i < qtdeJarros; i++) {
        e = this->esvaziaJarro(i);
        custo = this->calculaPesoAresta(e);
        
        e->setValorHeuristica(e->calculaValorHeuristica(obj));

        pair<Estado*, int> proxEstadoPonderado(e, custo);

        if(e != NULL) {
            proximosEstadosPonderados.push_back(proxEstadoPonderado);
        }
    }

    for(int i = 0; i < qtdeJarros; i++) {
        for(int j = 0; j < qtdeJarros; j++) {
            if(i != j) {
                e = this->transfereJarros(i, j);
                custo = this->calculaPesoAresta(e);
                
                e->setValorHeuristica(e->calculaValorHeuristica(obj));

                pair<Estado*, int> proxEstadoPonderado(e, custo);

                if(e != NULL) {
                    proximosEstadosPonderados.push_back(proxEstadoPonderado);
                }
            }
        }
    }

    return proximosEstadosPonderados;
}

void Estado::printEstado() {
    cout << "(" << this->getJarros()[0]->getConteudo();
    for(int i = 1; i < qtdeJarros; i++) {
        cout << ", ";
        this->getJarros()[i]->getConteudo();
    }
    cout << ")" << endl;
}

int Estado::calculaValorHeuristica(int obj) {
    int valorHeuristica = INT16_MAX;
    for(int i = 0; i < qtdeJarros; i++) {
        int conteudoJarro = this->getJarros()[i]->getConteudo();
        int distanciaObjetivo = abs(conteudoJarro - obj);

        if(distanciaObjetivo < valorHeuristica) {
            valorHeuristica = distanciaObjetivo;
        }
    }
    return valorHeuristica;
}

int Estado::calculaPesoAresta(Estado* e) {
    return abs(this->getConteudoTotal() - e->getConteudoTotal());
}
