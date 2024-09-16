#include "Jarro.h"
#include <iostream>

using namespace std; 

Jarro::Jarro() {
    this->capacidade = 0;
    this->conteudo = 0;
}

Jarro::Jarro(int capacidade) {
    this->capacidade = capacidade;
    this->conteudo = 0;
}

Jarro::Jarro(int capacidade, int conteudo) {
    this->capacidade = capacidade; 
    this->conteudo = conteudo;
}

// Métodos de set
void Jarro::setCapacidade(int capacidade) {
    if (capacidade <= 0) {
        cout << "Nao eh possivel gerar jarro com essa capacidade" << endl;
        cout << "Selecione uma capacidade maior: ";
        cin >> capacidade; 
        this->setCapacidade(capacidade);
        cout << endl; 
    } else {
        this->capacidade = capacidade;
    }

}

void Jarro::setConteudo(int conteudo) {
    if (conteudo <= 0 || conteudo + this->getConteudo() > this->getCapacidade()) {
        cout << "Operacao invalida: nao eh possivel setar esse conteudo" << endl; 
    } else {
        this->conteudo = conteudo;
    }
}
///////////////////////////////////////////////////////////////////////////

// Métodos de get
int Jarro::getCapacidade() {
    return this->capacidade;
}

int Jarro::getConteudo() {
    return this->conteudo;
}

///////////////////////////////////////////////////////////////////////////

// Outros Métodos

void Jarro::esvaziarJarro() {
    this->setConteudo(0);
}

void Jarro::encherJarro() {
    this->setConteudo(this->getCapacidade());    
}

bool Jarro::vazio() {
    if (this->getConteudo() == 0) {
        return true;
    }
    return false;
}

bool Jarro::cheio() {
    if (this->getConteudo() == this->getCapacidade()) {
        return true;
    }
    return false;
}

int Jarro::getEspacoVazio() {
    return this->getCapacidade() - this->getConteudo();
}