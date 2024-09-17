#include "Estado.h"
#include "Jarro.h"
#include <iostream> 
#include <vector>

using namespace std; 

Estado::Estado(int cap1, int cap2, int cont1, int cont2, int obj) {
    estadoFinal = false;

    Jarro* jarro1 = new Jarro(cap1, cont1);
    Jarro* jarro2 = new Jarro(cap2, cont2);

    if(jarro1->getConteudo() == obj || jarro2->getConteudo() == obj) {
        estadoFinal = true;
    }

    jarros = make_pair(jarro1, jarro2);
}

bool Estado::ehEstadoFinal() {
    return this->estadoFinal;
}

int Estado::getCapacidade(int n) {
    if(n == 1) {
        return this->jarros.first->getCapacidade();
    }

    if (n == 2) {
        return this->jarros.second->getCapacidade();
    }

    cout << "Selecione um jarro valido" << endl;
    exit(0);
}

int Estado::getConteudo(int n) {
    if(n == 1) {
        return this->jarros.first->getConteudo();
    }

    if (n == 2) {
        return this->jarros.second->getConteudo();
    }

    cout << "Selecione um jarro valido" << endl;
    exit(0);
}

int Estado::getMaiorCapacidade() {
    return (this->getConteudo(1) >= this->getConteudo(2) ? this->getConteudo(1) : this->getConteudo(2));
}

Estado* Estado::encheJarro(int n) {
    Estado* novoEstado = this; 

    if (n == 1) {
        Jarro* jarro = novoEstado->jarros.first;
        jarro->encherJarro();
    } else if (n == 2) {
        Jarro* jarro = novoEstado->jarros.second;
        jarro->encherJarro();
    } else {
        cout << "Selecione um jarro valido" << endl; 
        return NULL;
    }

    return novoEstado;
} 

Estado* Estado::esvaziaJarro(int n) {
    Estado* novoEstado = this; 

    if (n == 1) {
        Jarro* jarro = novoEstado->jarros.first;
        jarro->esvaziarJarro();
    } else if (n == 2) {
        Jarro* jarro = novoEstado->jarros.second;
        jarro->esvaziarJarro();
    } else {
        cout << "Selecione um jarro valido" << endl; 
        return NULL;
    }

    return novoEstado;
} 

Estado* Estado::transfere12() {
    Estado* novoEstado = this;
    Jarro* jarro1 = novoEstado->jarros.first;
    Jarro* jarro2 = novoEstado->jarros.second;

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

Estado* Estado::transfere21() {
    Estado* novoEstado = this;
    Jarro* jarro1 = novoEstado->jarros.first;
    Jarro* jarro2 = novoEstado->jarros.second;

    if(jarro2->vazio() || jarro1->cheio()) {
        return NULL;
    }

    int quantidadeTransferir; 

    // Se conteudo jarro 2 < espaco vazio => transferir conteudo jarro 2 
    if(jarro2->getConteudo() <= jarro1->getEspacoVazio()) {
        quantidadeTransferir = jarro2->getConteudo();
    }

    // Se conteudo jarro 2 > espaço vazio => transferir espaco vazio
    if(jarro2->getConteudo() > jarro1->getEspacoVazio()) {
        quantidadeTransferir = jarro1->getEspacoVazio();
    }

    jarro2->setConteudo(jarro2->getConteudo() - quantidadeTransferir);
    jarro1->setConteudo(jarro1->getConteudo() + quantidadeTransferir);

    return novoEstado;
} 

vector<Estado*>& Estado::gerarProximosEstados() {
    vector<Estado*> proximosEstados;
    Estado* e;

    Estado* e = this->encheJarro(1);
    proximosEstados.push_back(e); 

    Estado* e = this->encheJarro(2);
    proximosEstados.push_back(e); 
    
    Estado* e = this->esvaziaJarro(1);
    proximosEstados.push_back(e); 

    Estado* e = this->esvaziaJarro(2);
    proximosEstados.push_back(e);

    Estado* e = this->transfere12();
    proximosEstados.push_back(e); 

    Estado* e = this->transfere21();
    proximosEstados.push_back(e);

    return proximosEstados;
}

void Estado::printEstado() {
    cout << "(" << this->jarros.first->getConteudo() << ", " << this->jarros.second->getConteudo() << ")" << endl;
}