#ifndef JARRO_H
#define JARRO_H
#include <iostream> 

using namespace std; 

class Jarro {
    private:
        int capacidade;
        int conteudo;

    public:
        Jarro();

        Jarro(int capacidade);

        Jarro(int capacidade, int conteudo);

        ~Jarro();

        // Set
        void setCapacidade(int capacidade);
        void setConteudo(int conteudo);

        // Get
        int getCapacidade();
        int getConteudo();

        // Outros métodos
        void esvaziarJarro();
        void encherJarro();
        bool vazio();
        bool cheio();
        int getEspacoVazio();
};

#endif