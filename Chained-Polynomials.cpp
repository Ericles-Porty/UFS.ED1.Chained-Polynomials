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
} TipoLista;

void inicializa(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomioSomado, tipoLista* polinomioSubtraido, tipoLista* multPolonomio1, tipoLista* multPolonomio2);
void leitura(tipoLista* polinomio);
void ordena(tipoLista* polinomio);
void trocaNo(tipoLista* polinomio, tipoNo* noA, tipoNo* noB);
tipoNo* noDoIndice(tipoLista* lista, int i);
tipoNo* maiorNo(tipoLista* polinomio, int i);
int indiceDoNo(tipoLista* lista, tipoNo* no);
void printa(tipoLista* polinomio);
void insereNo(tipoLista* polinomio3, tipoNo* temp, int newCoeficiente);
void operacao(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomioSomado, int i);
void mult(tipoLista* polinomio, int mult, tipoLista* multPolonomio);
void apagar(tipoLista* polinomio);
void menu(tipoLista* p1, tipoLista* p2, tipoLista* pSomado, tipoLista* pSubtraido, tipoLista* multP1, tipoLista* multP2);

void inicializa(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomioSomado,tipoLista* polinomioSubtraido, tipoLista* multPolonomio1, tipoLista* multPolonomio2)
{
    polinomio1->inicio = NULL;
    polinomio1->fim = NULL;
    polinomio1->quant = 0;
    polinomio2->inicio = NULL;
    polinomio2->fim = NULL;
    polinomio2->quant = 0;
    polinomioSomado->inicio = NULL;
    polinomioSomado->fim = NULL;
    polinomioSomado->quant = 0;
    polinomioSubtraido->inicio = NULL;
    polinomioSubtraido->fim = NULL;
    polinomioSubtraido->quant = 0;
    multPolonomio1->inicio = NULL;
    multPolonomio1->fim = NULL;
    multPolonomio1->quant = 0;
    multPolonomio2->inicio = NULL;
    multPolonomio2->fim = NULL;
    multPolonomio2->quant = 0;
}

void leitura(tipoLista* polinomio)
{
    tipoNo* novoNo;
    tipoNo* atual;
    int achou = 0;
    atual = polinomio->inicio;
    int expoente, coeficiente;
    int tam = 0;
    cout << "Qual o tamanho do seu polinomio: ";
    cin >> tam;
    system("cls");
    for (int cont = 1; cont <= tam; cont++)
    {
        cout << "Digite o coeficiente do " << cont << " binomio" << endl;
        cin >> coeficiente;
        cout << "Digite o expoente do  " << cont << " binomio" << endl;
        cin >> expoente;

        //rodar a lista toda procurando se ja tem algum expoente, se achar soma o coeficiente
        if(polinomio->quant > 0){
            tipoNo* temp = polinomio->inicio;
            while(temp != NULL){
                if(expoente == temp->expoente){
                    achou = 1;
                    temp->coeficiente += coeficiente;
                }
                temp = temp->proxNo;
            }
        }

        if(achou == 0){
            achou = 0;
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
        }
        
        system("cls");
    }
        //------------------------
}

void ordena(tipoLista* polinomio) {
    int i;
    for (i = 0; i < polinomio->quant - 1; i++) {
        trocaNo(polinomio, noDoIndice(polinomio, i), maiorNo(polinomio, i));
    }
}

void trocaNo(tipoLista* polinomio, tipoNo* noA, tipoNo* noB) {
    if (noA == noB) {
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

void printa(tipoLista* polinomio)
{
    tipoNo* novoNo;
    novoNo = polinomio->inicio;

    while (novoNo != NULL)
    {
        if (novoNo->coeficiente != 0) {//caso coeficiente seja 0 nem precisa printar o numero
            if (novoNo->coeficiente == 1)//se o coeficiente for 1 nao precisa printar o coeficiente
            {
                if (novoNo->expoente == 1)//se o expoente for 1 nao precisa printar a parte elevada
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
        }
        novoNo = novoNo->proxNo;
    }
    cout << endl;
}

void insereNo(tipoLista* polinomio3, tipoNo* temp, int i){
    tipoNo* novoNo = (tipoNo*)malloc(sizeof(tipoNo));
    if (polinomio3->quant == 0)
    {
        novoNo->proxNo = NULL;
        novoNo->coeficiente = i;
        novoNo->expoente = temp->expoente;
        polinomio3->inicio = novoNo;
        polinomio3->fim = novoNo;
        polinomio3->quant++;
    }
    else
    {
        novoNo->proxNo = NULL;
        novoNo->coeficiente = i;
        novoNo->expoente = temp->expoente;
        polinomio3->fim->proxNo = novoNo;
        polinomio3->fim = novoNo;
        polinomio3->quant++;
    }
}

void operacao(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomioSubtraido,int i) {
    tipoNo* temp1 = polinomio1->inicio;
    tipoNo* temp2 = polinomio2->inicio;

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->expoente == temp2->expoente) {
            insereNo(polinomioSubtraido, temp1, temp1->coeficiente + (temp2->coeficiente)*i);
            temp1 = temp1->proxNo;
            temp2 = temp2->proxNo;
        }
        else if (temp1->expoente > temp2->expoente) {
            insereNo(polinomioSubtraido, temp1, temp1->coeficiente);
            temp1 = temp1->proxNo;
        }
        else if (temp1->expoente < temp2->expoente) {
            insereNo(polinomioSubtraido, temp2, temp2->coeficiente);
            temp2 = temp2->proxNo;
        }
    }

    while (temp1 != NULL)
    {
        insereNo(polinomioSubtraido, temp1, temp1->coeficiente);
        temp1 = temp1->proxNo;
    }
    while (temp2 != NULL)
    {
        insereNo(polinomioSubtraido, temp2, temp2->coeficiente);
        temp2 = temp2->proxNo;
    }
}

void mult(tipoLista* polinomio, int mult, tipoLista* multPolonomio){
    tipoNo* atual;
    atual = polinomio->inicio;
    tipoNo* temp;
    temp = (tipoNo*)malloc(sizeof(tipoNo));

    while (atual != NULL) {
        insereNo(multPolonomio, atual, atual->coeficiente * mult);
        atual = atual->proxNo;
    }
    
}

void apagar(tipoLista* polinomio) {
    while (polinomio->inicio == NULL) {
        tipoNo* aux;
        aux = polinomio->inicio;
        polinomio->inicio = polinomio->inicio->proxNo;
        if (polinomio->quant == 1)
            polinomio->fim = NULL;
        polinomio->quant--;
        free(aux);
    }
}

void menu(tipoLista* p1, tipoLista* p2, tipoLista* pSomado, tipoLista* pSubtraido, tipoLista* multP1, tipoLista* multP2) {
    int op = 0, op2 = 0;
    int qntPoli = 0;
    int jaFoiSomado = 0, jaFoiSubtraido = 0, jaFoiMultiplicado = 0, jaFoiMultiplicado2=0;
    int aux = 1;

    do {
        system("cls");
        cout << "Vai ler <1> ou <2> polinomios: ";
        cin >> qntPoli;
        system("cls");
        if (qntPoli == 1) {
            leitura(p1);
            ordena(p1);

        }
        else if (qntPoli == 2) {
            leitura(p1);
            leitura(p2);
            ordena(p1);
            ordena(p2);
        }
        else
            qntPoli = 0;
    } while (qntPoli == 0);
    system("cls");
    do {
        cout << "Polinomio 1: ";
        printa(p1);
        if (qntPoli == 2) {
            cout << "Polinomio 2: ";
            printa(p2);
        }
        cout << "Digite a opcao que deseja: " << endl;
        cout << "1 - Soma os dois polinomios." << endl;
        cout << "2 - Subtrai os dois polinomios." << endl;
        cout << "3 - Multiplica o polinomio 1 ou 2." << endl;
        if (qntPoli == 1)
            cout << "4 - Adciona outro polinomio. Voce tem '" << qntPoli << "' polinomio" << endl;;
        cout << "0 - Encerra" << endl;
        cin >> op;
        switch (op) {
        case 1:

            if (qntPoli == 1) {
                cout << "Voce so tem 1 polinomio, deseja ler outro? " << endl << "Sim: <1>" << endl << "Nao: <2> ou <qualquer numero inteiro>" << endl;
                cin >> op2;
                if (op2 == 1) {
                    leitura(p2);
                    ordena(p2);
                    qntPoli++;
                }
            }
            if (qntPoli == 2) {
                if (jaFoiSomado == 0) {
                    operacao(p1, p2, pSomado,1);
                    jaFoiSomado++;
                }
                system("cls");
                cout << "Polinomio resultante da soma: ";
                printa(pSomado);
            }
            break;

        case 2:
            if (qntPoli == 1) {
                cout << "Voce so tem 1 polinomio, deseja ler outro? " << endl << "Sim: <1>" << endl << "Nao: <2> ou <qualquer numero inteiro>" << endl;
                cin >> op2;
                if (op2 == 1) {
                    leitura(p2);
                    ordena(p2);
                    qntPoli++;
                }
            }
            if (qntPoli == 2) {
                if (jaFoiSubtraido == 0) {
                    operacao(p1, p2, pSubtraido,-1);
                    jaFoiSubtraido++;
                }
                system("cls");
                cout << "Polinomio resultante da subtracao: ";
                printa(pSubtraido);
            }
            break;

        case 3:
            system("cls");
            if (jaFoiMultiplicado == 0) {
                cout << "Qual multiplicador que ira multiplicar escaladamente os polinomios? " << endl;
                cin >> aux;
                mult(p1, aux, multP1);
                if (qntPoli == 2) {
                    mult(p2, aux, multP2);
                    jaFoiMultiplicado2++;
                }
                jaFoiMultiplicado++;
            }
            else {
                apagar(multP1);
                if(qntPoli==2 && jaFoiMultiplicado2>0)
                    apagar(multP2);
                multP1->inicio = NULL;
                multP1->fim = NULL;
                multP1->quant = 0;
                multP2->inicio = NULL;
                multP2->fim = NULL;
                multP2->quant = 0;
                cout << "Qual multiplicador que ira multiplicar escaladamente os polinomios? " << endl;
                cin >> aux;
                mult(p1, aux, multP1);
                if (qntPoli == 2)
                    mult(p2, aux, multP2);
                jaFoiMultiplicado++;
            }
            system("cls");
            cout << "Resultado do polinomio 1 multiplicado por " << aux << ": ";
            printa(multP1);
            if (qntPoli == 2) {
                cout << "Resultado do polinomio 2 multiplicado por " << aux << ": ";
                printa(multP2);
            }
            break;
        case 4:
            system("cls");
            if (qntPoli == 1) {
                leitura(p2);
                ordena(p2);
                qntPoli++;
            }
            else {
                cout << "Voce ja tem a quantidade maxima de polinomios!" << endl;
            }
            break;
        case 0:

            return;
        default:
            cout << "Digite uma operacao valida!" << endl << endl;
        }
    } while (op != 0);
}

int main()
{
    
    tipoLista polinomio1, polinomio2, polinomioSomado, polinomioSubtraido, multPolonomio1, multPolonomio2;
    inicializa(&polinomio1, &polinomio2, &polinomioSomado, &polinomioSubtraido, &multPolonomio1, &multPolonomio2);
    menu(&polinomio1, &polinomio2, &polinomioSomado, &polinomioSubtraido, &multPolonomio1, &multPolonomio2);
    
    return 0;
}

//ler linha 72