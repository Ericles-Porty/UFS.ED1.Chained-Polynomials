# Chained-Polynomials

***

Projeto apresentado como sistema de cálculo polinomial, como requisito para avaliação e participação da disciplina de Estrutura de Dados I no semestre letivo 2020.2.

***

Desenvolvido pelos estudantes:

  * ÉRICLES DOS SANTOS C.
  * JOANNE STEPHANY GOIS DA SILVA 
  * KENDY FERREIRA DE OLIVEIRA
  * MARIA MILENA DE OLIVEIRA SOUZA
  * THIAGO SANTOS SANTANA 

Estudantes do curso de Sistemas da Informação da Universidade Federal de Sergipe campus Itabaiana. 

*** 

## **Introdução**

Nesse projeto é apresentado um sistema desenvolvido em C++, para executar as ações de receber um ou dois polinômios e fazer operações entre entradas e saídas para apresentar o resultado.

Nosso programa realiza algumas operações matemáticas sobre polinômios. Nele cada polinômio é guardado em uma lista simplesmente encadeada de forma que em cada nó da lista deve ser guardado um termo do polinômio. Cada nó também guarda cada coeficiente e grau (expoente) do termo, bem como um ponteiro para o nó seguinte.

***

## **Conceito de Polinômios**

Conhecemos como polinômio uma expressão que indica a soma algébrica de monômios que não sejam semelhantes, ou seja, polinômio é uma expressão algébrica entre monômios. Monômio é um termo algébrico que possui coeficiente e parte literal.

Quando existem termos semelhantes entre os polinômios, é possível realizar-se a redução de seus termos na adição e ou subtração de dois polinômios. É possível também multiplicar dois polinômios por meio da propriedade distributiva. Já a divisão é realizada pelo método de chaves.

## **Funcionalidades do programa**

* Lê um ou dois polinômios.

* Soma dois polinômios, guarda o resultado em outra lista encadeada e exibe o
polinômio resultante.

* Subtrai dois polinômios, guarda o resultado em outra lista encadeada e exibe o
polinômio resultante.

* Multiplicação polinômica por escalar e exibe o polinômio resultante.

## **Manual de uso**

1. Ao iniciar o programa é apresentado ao usuário a pergunta de quantos polinômios serão inseridos, podendo variar entre 1 e 2.

2. Ao selecionar uma  das opções, o usuário é encaminhado para a tela cuja terá que inserir o tamanho do seu polinômio, caso a opção seja 2 a tela é apresentada duas vezes.

  * Após inserir o tamanho é possível adicionar os coeficientes e expoentes em sequência.
   
3. Após inserir o tamanho o programa irá apresentar um menu com 5 opções (caso tenha 1 polinômio) ou 4 opções (caso tenha 2 polinômios) , sendo elas:
   
  *  1 - Soma os dois polinômios.
  *  2 - Subtrai os dois polinômios.
  *  3 - Multiplica o polinômio.
  *  4 - Adciona outro polinômio. Voce tem '1' polinômio. (caso tenha 2 essa opção não irá aparecer).
  *  0 - encerra o código.
  
4. Caso o usuário escolha a opção 1 ou 2 e tenha os dois polinômios no sistema, o programa faz o cálculo da soma ou subtração entre os dois existentes, gerando um terceiro polinômio resultado.

5. Ao digitar a opção 3 o programa irá para uma tela perguntando qual número inteiro irá multiplicar escalonadamente o primeiro ou ambos polinômios.  

6. Ao digitar "0" o programa é encerrado.

### **Observações importantes**
* A opção 3 pode ser escolhida várias vezes.
* Caso queira criar outros polinômios é necessário reiniciar o programa. (Atualização futura corrigirá essa limitação).
* Na subtração apenas é subtraído o primeiro polinômio pelo segundo. (Atualização futura corrigirá essa limitação).
