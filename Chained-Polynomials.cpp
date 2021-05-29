#include <iostream>
using std::cout;
using std::cin;
using std::endl;

typedef struct no {
    struct no* proxNo;
    int coeficiente;
    int expoente;
}TipoNo;

typedef struct tipolista {
    TipoNo* inicio;
    TipoNo* fim;
    int quant;
}TipoLista;

void inicializa(tipolista* polinomio1, tipolista* polinomio2, tipolista* polinomio3) {
    polinomio1->inicio = NULL;
    polinomio2->inicio = NULL;
    polinomio3->inicio = NULL;
    polinomio1->fim = NULL;
    polinomio2->fim = NULL;
    polinomio3->fim = NULL;
    polinomio1->quant = 0;
    polinomio2->quant = 0;
    polinomio3->quant = 0;
}

void leitura(tipolista* polinomio) {
    TipoNo* novoNo;
    int expoente, coeficiente;
    int tam = 0;
    cout << "Qual o tamanho do seu polinomio: ";
    cin >> tam;
    system("cls");
    for (int cont = 1; cont <= tam; cont++) {
        cout << "Digite o coeficiente do " << cont << " polinomio" << endl;
        cin >> coeficiente;
        cout << "Digite o expoente do  " << cont << " polinomio" << endl;
        cin >> expoente;
        novoNo = (TipoNo*)malloc(sizeof(TipoNo));
        if (polinomio->quant == 0) {
            novoNo->proxNo = NULL;
            novoNo->coeficiente = coeficiente;
            novoNo->expoente = expoente;
            polinomio->inicio = novoNo;
            polinomio->fim = novoNo;
            polinomio->quant++;
        }
        else {
            novoNo->proxNo = NULL;
            novoNo->coeficiente = coeficiente;
            novoNo->expoente = expoente;
            polinomio->fim->proxNo = novoNo;
            polinomio->fim = novoNo;
            polinomio->quant++;
        }
        system("cls");
    }
}

void printa(tipolista* polinomio) {
    TipoNo* novoNo;
    novoNo = polinomio->inicio;
    if (novoNo->coeficiente == 1) {
        cout << "X^" << novoNo->expoente << endl;
    }
    else {
        cout << novoNo->coeficiente << "X^" << novoNo->expoente << endl;
    }
    while (novoNo->proxNo != NULL) {
        if (novoNo->proxNo->coeficiente == 1) {
            cout << "X^" << novoNo->proxNo->expoente << endl;
        }
        else {
            cout << novoNo->proxNo->coeficiente << "X^" << novoNo->proxNo->expoente << endl;
        }
        novoNo = novoNo->proxNo;
    }
}
int main()
{
    TipoLista polinomio1, polinomio2, polinomio3;
    inicializa(&polinomio1, &polinomio2, &polinomio3);
    leitura(&polinomio1);
    leitura(&polinomio2);
    cout << "Polinomio 1: " << endl;
    printa(&polinomio1);
    cout << "Polinomio 2: " << endl;
    printa(&polinomio2);
    return 0;
}
//*SE POSSÍVEL ORDENAR DO MAIOR expoenteOENTE PRO MENOR DA ESQUERDA PRA DIREITA(APENAS OPCIONAL
//*IMPLEMENTAR COMPARAÇÃO ENTRE expoenteOENTES, SE FOR IGUAIS SOMAR E POR EM UM POLIMONIO 3