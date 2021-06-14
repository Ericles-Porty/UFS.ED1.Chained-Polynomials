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

//Define os valores base das listas
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

//Atribui os nós(novoMonomio) na lista(polinomio)
void leitura(tipoLista* polinomio)
{
    tipoNo* novoMonomio;
    tipoNo* atual;
    int achouMesmoExp = 0;
    atual = polinomio->inicio;
    int expoente, coeficiente;
    int tamanhoDoPolinomio = 0;
    cout << "Qual o tamanho do seu polinomio: ";
    cin >> tamanhoDoPolinomio;
    system("cls");
    for (int cont = 1; cont <= tamanhoDoPolinomio; cont++)
    {
        cout << "Digite o coeficiente do " << cont << " monomio" << endl;
        cin >> coeficiente;
        cout << "Digite o expoente do  " << cont << " monomio" << endl;
        cin >> expoente;
        if (polinomio->quant > 0) {
            tipoNo* temp = polinomio->inicio;
            while (temp != NULL) {//Roda o polinomio ate o ultimo novoMonomio adcionado
                if (expoente == temp->expoente) {//Condição para caso ache um expoente igual, soma o coeficiente
                    achouMesmoExp = 1;
                    temp->coeficiente += coeficiente;
                }
                temp = temp->proxNo;
            }
        }

        if (achouMesmoExp == 0) {//Caso ele não ache um novo expoente, ele vai inserir um novo novoMonomio
            achouMesmoExp = 0;
            novoMonomio = (tipoNo*)malloc(sizeof(tipoNo));
            if (polinomio->quant == 0)//Condição para adcionar o primeiro novoMonomio do polinomio
            {
                novoMonomio->proxNo = NULL;
                novoMonomio->coeficiente = coeficiente;
                novoMonomio->expoente = expoente;
                polinomio->inicio = novoMonomio;
                polinomio->fim = novoMonomio;
                polinomio->quant++;
            }
            else//Condição para adcionar os monomios após ter pelo menos um
            {
                novoMonomio->proxNo = NULL;
                novoMonomio->coeficiente = coeficiente;
                novoMonomio->expoente = expoente;
                polinomio->fim->proxNo = novoMonomio;
                polinomio->fim = novoMonomio;
                polinomio->quant++;
            }
        }

        system("cls");
    }
}

//Ordena o polinomio em ordem decrescente referente ao expoente
void ordena(tipoLista* polinomio) {
    int index;
    for (index = 0; index < polinomio->quant - 1; index++) {
        trocaNo(polinomio, noDoIndice(polinomio, index), maiorNo(polinomio, index));
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

//Apresenta o polinomio completo
void printa(tipoLista* polinomio)
{
    tipoNo* monomio;
    monomio = polinomio->inicio;

    while (monomio != NULL)
    {
        if (monomio->coeficiente != 0) {    //Caso o coeficiente seja 0 não precisa printar o numero
            if (monomio->coeficiente == 1)  //Se o coeficiente for 1 não precisa printar o coeficiente
            {
                if (monomio->expoente == 1) //Se o expoente for 1 não precisa printar a parte elevada
                    cout << "X";
                else
                    cout << "X^" << monomio->expoente;
            }
            else
            {
                if (monomio->expoente == 1) //Se o expoente for 1 não precisa printar o expoente
                    cout << monomio->coeficiente << "X";
                else
                    cout << monomio->coeficiente << "X^" << monomio->expoente;
            }

            if (monomio->proxNo == NULL)                //Quando terminar de ler o polinomio tem uma quebra de linha
                cout << endl;
            else if (monomio->proxNo->coeficiente >= 0) //Entre os monomios ele confere se o proximo coeficiente é positivo caso seja printa o simbolo de "+"
                cout << "+";
        }
        monomio = monomio->proxNo;
    }
    cout << endl;
}

//Função que insere um novo novoMonomio para realizar operações
void insereNo(tipoLista* polinomio, tipoNo* temp, int index){
    tipoNo* novoMonomio = (tipoNo*)malloc(sizeof(tipoNo));
    if (polinomio->quant == 0)  //Condição para inserir o primeiro monomio
    {
        novoMonomio->proxNo = NULL;
        novoMonomio->coeficiente = index;
        novoMonomio->expoente = temp->expoente;
        polinomio->inicio = novoMonomio;
        polinomio->fim = novoMonomio;
        polinomio->quant++;
    }
    else                        //Insere os monomios subsequentes
    {
        novoMonomio->proxNo = NULL;
        novoMonomio->coeficiente = index;
        novoMonomio->expoente = temp->expoente;
        polinomio->fim->proxNo = novoMonomio;
        polinomio->fim = novoMonomio;
        polinomio->quant++;
    }
}

//Função que realiza operação de soma ou subtração
void operacao(tipoLista* polinomio1, tipoLista* polinomio2, tipoLista* polinomioResultante,int positivoOuNegativo) {
    tipoNo* monomio1 = polinomio1->inicio;
    tipoNo* monomio2 = polinomio2->inicio;

    while (monomio1 != NULL && monomio2 != NULL)  //Enquanto existir monomios nos 2 polinomios continua a repetição
    {
        if (monomio1->expoente == monomio2->expoente) { //Caso os expoentes sejam iguais ele realiza a operação
            //Insere o monomioResultante
            insereNo(polinomioResultante, monomio1, monomio1->coeficiente + (monomio2->coeficiente)*positivoOuNegativo);
            //Avança para o proximo monomio dos 2 polinomios
            monomio1 = monomio1->proxNo;
            monomio2 = monomio2->proxNo;
        }
        else if (monomio1->expoente > monomio2->expoente) { 
            //Caso o expoente do primeiro monomio seja maior que o segundo ele insere o monomio no polinomio resultante
            insereNo(polinomioResultante, monomio1, monomio1->coeficiente);
            //Avança para o proximo monomio do polinomio1
            monomio1 = monomio1->proxNo;
        }
        else if (monomio1->expoente < monomio2->expoente) {
            //Caso o expoente do primeiro monomio seja menor que o segundo ele insere o monomio no polinomio resultante
            insereNo(polinomioResultante, monomio2, monomio2->coeficiente);
            //Avança para o proximo monomio do polinomio2
            monomio2 = monomio2->proxNo;
        }
    }
    //Caso algum polinomio já tenha chegado ao final ele verifica se o outro também chegou
    //Caso não tenha chegado ele percorre inserindo os valores do restante no polinomio resultante
    while (monomio1 != NULL)
    {
        insereNo(polinomioResultante, monomio1, monomio1->coeficiente);
        monomio1 = monomio1->proxNo;
    }
    while (monomio2 != NULL)
    {
        insereNo(polinomioResultante, monomio2, monomio2->coeficiente);
        monomio2 = monomio2->proxNo;
    }
}

//Função que realiza operação de multiplicação de um polinomio
void mult(tipoLista* polinomio, int multiplicador, tipoLista* polinomioResultante){
    tipoNo* monomio;
    monomio = polinomio->inicio;
    tipoNo* novoMonomio;
    novoMonomio = (tipoNo*)malloc(sizeof(tipoNo));

    while (monomio != NULL) {
        //Insere os monomios já multiplicados no polinomio resultante
        insereNo(polinomioResultante, monomio, monomio->coeficiente * multiplicador);
        monomio = monomio->proxNo;
    }
    
}

//Função que libera a memória dos monomios de um polinomio que vai ser apagado
void apagar(tipoLista* polinomio) {
    
    while (polinomio->inicio != NULL) { //Enquanto o monomio do inicio tiver algum valor ele continua a repetição
        tipoNo* monomio;
        monomio = polinomio->inicio;        
        polinomio->inicio = polinomio->inicio->proxNo;  //Faz o inicio apontar para o proximo monomio depois dele
        if (polinomio->quant == 1)                      //Caso tenha apenas 1 monomio ele apaga o fim
            polinomio->fim = NULL;
        polinomio->quant--;
        //Apaga o primeiro monomio do polinomio
        free(monomio);
    }
}

void menu(tipoLista* polinomio1, tipoLista* p2, tipoLista* pSomado, tipoLista* pSubtraido, tipoLista* multP1, tipoLista* multP2) {
    int opcao1 = 0, opcao2 = 0;
    int quantidadePolinomios = 0;
    int jaFoiSomado = 0, jaFoiSubtraido = 0, jaFoiMultiplicado1 = 0, jaFoiMultiplicado2=0;
    int aux = 1;

    do {
        system("cls");
        cout << "Vai ler <1> ou <2> polinomios: ";
        cin >> quantidadePolinomios;
        system("cls");
        //Condição para adcionar apenas 1 polinomio
        if (quantidadePolinomios == 1) {
            leitura(polinomio1);
            ordena(polinomio1);

        }
        //Condição para adcionar 2 polinomios
        else if (quantidadePolinomios == 2) {
            leitura(polinomio1);
            leitura(p2);
            ordena(polinomio1);
            ordena(p2);
        }
        //Caso a pessoa não tenha digitado nem 1 nem 2
        else
            quantidadePolinomios = 0;
    } while (quantidadePolinomios == 0);
    system("cls");
    do {
        cout << "Polinomio 1: ";
        printa(polinomio1);
        if (quantidadePolinomios == 2) {
            cout << "Polinomio 2: ";
            printa(p2);
        }
        cout << "Digite a opcao que deseja: " << endl;
        cout << "1 - Soma os dois polinomios." << endl;
        cout << "2 - Subtrai os dois polinomios." << endl;
        cout << "3 - Multiplica o polinomio 1 ou 2." << endl;
        if (quantidadePolinomios == 1)
            cout << "4 - Adciona outro polinomio. Voce tem '" << quantidadePolinomios << "' polinomio" << endl;;
        cout << "0 - Encerra" << endl;
        cin >> opcao1;
        switch (opcao1) {
        case 1:

            if (quantidadePolinomios == 1) {
                cout << "Voce so tem 1 polinomio, deseja ler outro? " << endl << "Sim: <1>" << endl << "Nao: <2> ou <qualquer numero inteiro>" << endl;
                cin >> opcao2;
                if (opcao2 == 1) {
                    leitura(p2);
                    ordena(p2);
                    quantidadePolinomios++;
                }
            }
            if (quantidadePolinomios == 2) {
                if (jaFoiSomado == 0) {
                    operacao(polinomio1, p2, pSomado,1);
                    jaFoiSomado++;
                }
                system("cls");
                cout << "Polinomio resultante da soma: ";
                printa(pSomado);
            }
            break;

        case 2:
            if (quantidadePolinomios == 1) {
                cout << "Voce so tem 1 polinomio, deseja ler outro? " << endl << "Sim: <1>" << endl << "Nao: <2> ou <qualquer numero inteiro>" << endl;
                cin >> opcao2;
                if (opcao2 == 1) {
                    leitura(p2);
                    ordena(p2);
                    quantidadePolinomios++;
                }
            }
            if (quantidadePolinomios == 2) {
                if (jaFoiSubtraido == 0) {
                    operacao(polinomio1, p2, pSubtraido,-1);
                    jaFoiSubtraido++;
                }
                system("cls");
                cout << "Polinomio resultante da subtracao: ";
                printa(pSubtraido);
            }
            break;

        case 3:
            system("cls");
            if (jaFoiMultiplicado1 == 0) {
                cout << "Qual multiplicador que ira multiplicar escaladamente os polinomios? " << endl;
                cin >> aux;
                mult(polinomio1, aux, multP1);
                if (quantidadePolinomios == 2) {
                    mult(p2, aux, multP2);
                    jaFoiMultiplicado2++;
                }
                jaFoiMultiplicado1++;
            }
            else {
                apagar(multP1);
                if(quantidadePolinomios==2 && jaFoiMultiplicado2>0)
                    apagar(multP2);
                multP1->inicio = NULL;
                multP1->fim = NULL;
                multP1->quant = 0;
                multP2->inicio = NULL;
                multP2->fim = NULL;
                multP2->quant = 0;
                cout << "Qual multiplicador que ira multiplicar escaladamente os polinomios? " << endl;
                cin >> aux;
                mult(polinomio1, aux, multP1);
                if (quantidadePolinomios == 2)
                    mult(p2, aux, multP2);
                jaFoiMultiplicado1++;
            }
            system("cls");
            cout << "Resultado do polinomio 1 multiplicado por " << aux << ": ";
            printa(multP1);
            if (quantidadePolinomios == 2) {
                cout << "Resultado do polinomio 2 multiplicado por " << aux << ": ";
                printa(multP2);
            }
            break;
        case 4:
            system("cls");
            if (quantidadePolinomios == 1) {
                leitura(p2);
                ordena(p2);
                quantidadePolinomios++;
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
    } while (opcao1 != 0);
}

int main()
{
    
    tipoLista polinomio1, polinomio2, polinomioSomado, polinomioSubtraido, multPolonomio1, multPolonomio2;
    inicializa(&polinomio1, &polinomio2, &polinomioSomado, &polinomioSubtraido, &multPolonomio1, &multPolonomio2);
    menu(&polinomio1, &polinomio2, &polinomioSomado, &polinomioSubtraido, &multPolonomio1, &multPolonomio2);
    
    return 0;
}

//ler linha 72