#include <iostream> 
#include "src/Jarro.h"
#include "src/Estado.h"
#include "src/GrafoEstados.h"

using namespace std;

int main () {
    int qtdeJarros;
    int obj;
    
    cout << "Insira quantidade de Jarros: " << endl;
    cin >> qtdeJarros;

    cout << "Insira o objetivo: " << endl; 
    cin >> qtdeJarros;

    GrafoEstados* g = new GrafoEstados(qtdeJarros, obj);

    g->backtracking();
    g->breadthFirstSearch();
    g->depthFirstSearch();
    g->buscaOrdenada();
    g->buscaGulosa();
    g->buscaAAST();

    return 0;
}