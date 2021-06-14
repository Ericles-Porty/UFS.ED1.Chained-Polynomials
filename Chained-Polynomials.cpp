#include <iostream>
using std::cin;
using std::cout;
using std::endl;

typedef struct no
{
    struct no* proxNo;
    int coeficiente;
    int expoente;
} tipoNo;

typedef struct tipoLista
{
    tipoNo* inicio;
    tipoNo* fim;
    int quant;
    int maiorExp;
} TipoLista;

void inicializa(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomio3);
void leitura(tipoLista* polinomio);
int indiceDoNo(tipoLista* lista, tipoNo* no);
tipoNo* noDoIndice(tipoLista* lista, int i);
tipoNo* maiorNo(tipoLista* polinomio, int i);
void trocaNo(tipoLista* polinomio, tipoNo* noA, tipoNo* noB);
void ordena(tipoLista* polinomio);
void sum(tipoLista* polinomio1,tipoLista* polinomio2, tipoLista* polinomio3);
void sub(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomio3);
void mult(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomio3);
int maiorPolinomio(tipoLista* polinomio1, tipoLista* polinomio2);
void printa(tipoLista* polinomio);


void inicializa(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomio3)
{
    polinomio1->maiorExp = 0;
    polinomio2->maiorExp = 0;
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

void leitura(tipoLista* polinomio)
{
    tipoNo* novoNo;
    int expoente, coeficiente;
    int tam = 0;
    cout << "Qual o tamanho do seu polinomio: ";
    cin >> tam;
    system("cls");
    for (int cont = 1; cont <= tam; cont++)
    {
        cout << "Digite o coeficiente do " << cont << " polinomio" << endl;
        cin >> coeficiente;
        cout << "Digite o expoente do  " << cont << " polinomio" << endl;
        cin >> expoente;

        novoNo = (tipoNo*)malloc(sizeof(tipoNo));
        if (polinomio->quant == 0)
        {
            novoNo->proxNo = NULL;
            novoNo->coeficiente = coeficiente;
            novoNo->expoente = expoente;
            polinomio->inicio = novoNo;
            polinomio->fim = novoNo;
            polinomio->quant++;
        }
        else
        {
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

tipoNo* noDoIndice(tipoLista* lista, int i) { //retorna o no do indice
    if (i >= 0 && i < lista->quant) {
        tipoNo* atual= lista->inicio;
        int o;
        for (o = 0; o < i; o++)
            atual = atual->proxNo;
        return atual;
    }
    return NULL;
}

int indiceDoNo(tipoLista* lista, tipoNo* no) { // retorna indice do no
    if (no != NULL) {
        tipoNo* atual = lista->inicio;
        int i = 0;
        while (atual!= NULL && atual!=no) {
            i++;
            atual = atual->proxNo;
        }
        if(atual != NULL)
            return i;
    }
    return -1;
}

int existeExp(tipoLista* lista, int exp) { // retorna indice do no
    
    tipoNo* atual;
    atual = lista->inicio;
    int i = 0;
    while (atual != NULL && atual->expoente != exp) {
        i++;
        atual = atual->proxNo;
    }
    if (atual != NULL)
       return i;
    
    return -1;
}

tipoNo* maiorNo(tipoLista* polinomio, int i) {
    tipoNo* atual = noDoIndice(polinomio, i);

    if (atual != NULL) {
        tipoNo* maior = atual;
        while (atual != NULL) {
            if (atual->expoente > maior->expoente)
                maior = atual;
            atual = atual->proxNo;
        }
        return maior;
    }
    return NULL;
}

void trocaNo(tipoLista *polinomio,tipoNo *noA,tipoNo *noB){
    if(noA==noB){
        return;
    }
    int enderecoA = indiceDoNo(polinomio, noA);
    int enderecoB = indiceDoNo(polinomio, noB);

    if (enderecoA > enderecoB) {
        noA = noB; // troca A por B
        noB = noDoIndice(polinomio, enderecoA); // recupera a posicao do A que foi perdida e joga no B

        enderecoA = enderecoB; 
        enderecoB = indiceDoNo(polinomio, noB);
    }
    tipoNo* preB = noDoIndice(polinomio, enderecoB - 1);
    if (noA == polinomio->inicio) {
        polinomio->inicio = noB;
    }
    else {
        tipoNo* preA = noDoIndice(polinomio, enderecoA - 1);
        preA->proxNo = noB;
    }

    preB->proxNo = noA; // o anterior de b aponta
    tipoNo* temp = noA->proxNo;
    noA->proxNo = noB->proxNo;
    noB->proxNo = temp;
}

void ordena(tipoLista* polinomio) {
    int i;
    for (i = 0; i < polinomio->quant - 1;i++) {
        trocaNo(polinomio, noDoIndice(polinomio, i), maiorNo(polinomio, i));
    }
}

int maiorPolinomio(tipoLista* polinomio1, tipoLista* polinomio2) {
    if (maiorNo(polinomio1,0) >= maiorNo(polinomio2,0))
        return 1;
    if (maiorNo(polinomio2, 0) >= maiorNo(polinomio1, 0))
        return 2;
}

void escreveResul(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomio3) {
    tipoNo* atual1;
    atual1 = polinomio1->inicio;
    tipoNo* atual2;
    atual2 = polinomio2->inicio;
    tipoNo* novoNo3;
    novoNo3 = (tipoNo*)malloc(sizeof(tipoNo));
    while (atual1 != NULL) {
        cout << "Existe expoente? : "<<existeExp(polinomio3, atual1->expoente) << endl;
        if(existeExp(polinomio3, atual1->expoente)== -1){   
            cout << "TEST 1" << endl;
            novoNo3->expoente = atual1->expoente;
            novoNo3->proxNo = NULL;
            cout << "TEST 2" << endl;
            polinomio3->fim->proxNo = novoNo3;
            cout << "TEST 3" << endl;
            polinomio3->fim = novoNo3;
            atual1 = atual1->proxNo;
        }
        else {
            atual1 = atual1->proxNo;

        }
    }

}

void sum(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomio3) {
    tipoNo* atual1;
    atual1 = polinomio1->inicio;
    tipoNo* atual2;
    atual2 = polinomio2->inicio;
    int acumulador = 0;
    int decisao = maiorPolinomio(polinomio1, polinomio2);
    if (decisao ==1) {
        cout << "1: " << atual1->expoente << endl;
        cout <<"2: " <<atual1->proxNo->expoente << endl;
        acumulador = atual1->coeficiente;
        polinomio3->inicio= maiorNo(polinomio1,0);
        polinomio3->fim = NULL;
        polinomio3->inicio->proxNo = polinomio3->fim;
        polinomio3->quant =1;
        tipoNo* atual3 = polinomio3->inicio;

        while (atual1 != NULL) {//roda o polinomio 1 todo
            if (atual1->expoente == atual3->expoente) {
                atual1 = atual1->proxNo;
                cout << "Teste 1" << endl;
                cout << "EXP1: " << atual1->expoente<< endl;
                cout << "EXP2: "<<atual1->proxNo->expoente << endl;
            }
            else{
                tipoNo* novoNo = (tipoNo*)malloc(sizeof(tipoNo));
                novoNo->expoente = atual1->expoente;
                novoNo->coeficiente = 0;
                novoNo->proxNo = NULL;
                polinomio3->fim->proxNo = novoNo;
                polinomio3->fim = novoNo;
                polinomio3->quant++;
                cout << "Teste 2" << endl;

            }
        }
        while(atual1->proxNo != NULL) {//roda o polinomio 1 todo
            if (atual1->expoente == atual3->expoente) {
                atual3->coeficiente += atual1->proxNo->expoente;
            }
            else {

            }
            if (atual1->expoente == atual1->proxNo->expoente) {
                atual3->coeficiente += atual1->proxNo->expoente;
                atual1->proxNo;
            }
            else {
                atual1 = atual1->proxNo->proxNo;
                atual3->proxNo;
            }
        }
    }
    else if (decisao == 2) {
        acumulador = atual2->coeficiente;
        polinomio3->inicio = maiorNo(polinomio2, 0);
        polinomio3->fim = NULL;
        polinomio3->inicio->proxNo = polinomio3->fim;
        polinomio3->quant = 1;
        tipoNo* atual3 = polinomio3->inicio;

        while (atual2!= NULL) {//roda o polinomio 1 todo
            if (atual2->expoente == atual3->expoente) {
                atual2 = atual2->proxNo;
                cout << "Teste 1" << endl;
            }
            else {
                tipoNo* novoNo = (tipoNo*)malloc(sizeof(tipoNo));
                novoNo->expoente = atual2->expoente;
                novoNo->coeficiente = 0;
                novoNo->proxNo = NULL;
                polinomio3->fim->proxNo = novoNo;
                polinomio3->fim = novoNo;
                polinomio3->quant++;
                cout << "Teste 2" << endl;

            }
        }
    }
}

void sub(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomio3) {

}

void mult(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomio3) {

}

void printa(tipoLista* polinomio)
{
    tipoNo* novoNo;
    novoNo = polinomio->inicio;

    while (novoNo != NULL)
    {
        if (novoNo->coeficiente == 1)
        {
            if (novoNo->expoente == 1)
                cout << "X";
            else
                cout << "X^" << novoNo->expoente;
        }
        else
        {
            if (novoNo->expoente == 1)
                cout << novoNo->coeficiente << "X";
            else
                cout << novoNo->coeficiente << "X^" << novoNo->expoente;
        }

        if (novoNo->proxNo == NULL)
            cout << endl;
        else if (novoNo->proxNo->coeficiente >= 0)
            cout << "+";
        novoNo = novoNo->proxNo;
    }
    cout << endl;
}

int main()
{
    int op;
    TipoLista polinomio1, polinomio2, polinomio3;
    inicializa(&polinomio1, &polinomio2, &polinomio3);
    leitura(&polinomio1);
    leitura(&polinomio2);
    cout << "Polinomio 1: " << endl;
    ordena(&polinomio1);
    printa(&polinomio1);
    cout << "Polinomio 2: " << endl;
    ordena(&polinomio2);
    printa(&polinomio2);
    cout << "Digite a opcao que deseja: " << endl;
    cout << "1 - Soma" << endl;
    cout << "2 - Subtracao" << endl;
    cout << "3 - Multiplicao" << endl;
    cout << "0 - Encerra" << endl;
    cin >> op;
    switch (op) {
    case 1: 
        cout << "Test 0" << endl;
        escreveResul(&polinomio1, &polinomio2, &polinomio3);
        cout << "Test 3" << endl;
        printa(&polinomio3);
        cout << "Test 4" << endl;
        break;

    case 2: 
        sub(&polinomio1, &polinomio2, &polinomio3);
        printa(&polinomio3);

        break;

    case 3: 
        mult(&polinomio1, &polinomio2, &polinomio3);
        printa(&polinomio3);

        break;
    case 0:
        return 0;
    default:
        cout << "Digite uma operacao valida!" << endl << endl;
    }
    return 0;
}

//preencher o Polinomio3 usando a função escrever resul
//fazer as operacoes soma na função sum() e subtracao na sub()
//multiplicao