# Projeto:
Fazer um programa que representa uma loja em que o usuário (dono da loja) começa com uma reserva de R$100,00 de dinheiro. A loja trabalha apenas com bananas, tomates e maçãs. Ao inicializar o programa, nosso algoritmo deverá exibir a TELA INICIAL com as seguintes mensagens :

## TELA INICIAL

```
======================
Caixa: R$100,00
======================

1 - Comprar produtos.
2 - Vender produtos.
3 - Lista de produtos.
4 - Sair.
```
### CASO 3: LISTAR PRODUTOS

Ao digitar a tecla 3 na TELA INICIAL, o usuário deverá ver a TELA (3) com a descrição dos produtos da loja.
Inicialmente, a loja deverá mostrar a seguinte descrição:

#### TELA (3)

```
===== DESCRIÇÃO DOS PRODUTOS =====
1 - Tomate - qtd: 0
2 - Banana - qtd: 0
3 - Maçã - qtd: 0
==================================
```
Ou seja, inicialmente, a nossa loja não terá nenhum produto.

### CASO 1: COMPRAR PRODUTO
Ao digitar a tecla 1 na TELA INICIAL, o usuário deverá ver a TELA (1):

#### TELA (1)

```
====== COMPRAS =======
1 - Tomate:		R$2,00
2 - Banana:		R$1,50
3 - Maçã:		R$1,00
======================
```
O usuário irá selecionar um dos 3 produtos (digitar 1 para tomate, 2 para banana e 3 para maçã) e o programa irá perguntar a quantidade desejada. Após o usuário digitar a quantidade, o programa irá subtrair do caixa o preço devido e adicionar a quantidade comprada no estoque do produto. Por exemplo, no caso do usuário ter digitado 1 e colocado 20 de quantidade, nosso programa irá adicionar 20 tomates ao estoque, subtrair R$40 reais do caixa e informar que a operação foi realizada com sucesso. Após isso, nosso programa irá exibir a TELA INICIAL para o usuário. Se o preço a ser subtraído for maior do que o preço disponível no caixa, o programa deverá exibir uma mensagem de erro, não efetuar a operação e voltar para TELA INICIAL.

### CASO 2: VENDER PRODUTOS

Ao digitar a tecla 2 na TELA INICIAL, o usuário deverá ver a TELA (2):

#### TELA (2)

```
======= VENDAS =======
1 - Tomate:		R$4,00
2 - Banana:		R$3,00
3 - Maçã:		R$2,00
======================
```

O usuário irá selecionar um dos 3 produtos (digitar 1 para tomate, 2 para banana e 3 para maçã) e o programa irá perguntar a quantidade desejada. Após o usuário digitar a quantidade, o programa irá adicionar no caixa a quantidade de dinheiro obtida com a venda e remover a quantidade vendida do produto no estoque. Por exemplo, no caso do usuário ter digitado 1 e colocado 5 de quantidade, nosso programa irá remover 5 tomates do estoque, adicionar R$20 reais no caixa e informar que a operação foi realizada com sucesso. Após isso, nosso programa irá exibir a TELA INICIAL para o usuário. Se a quantidade de produtos a serem vendidos for maior do que a quantidade disponível no estoque, o programa deverá exibir uma mensagem de erro, não efetuar a operação e voltar para TELA INICIAL.

O código deve ter comentários explicando cada trecho de código relevante. Quanto mais individual o trabalho, melhor.

## PONTUAÇÃO:
UTILIZAÇÃO DA ESTRUTURA DE REPETIÇÃO DE FORMA ADEQUADA: 2 PONTOS.
LISTAR PRODUTOS: 1 PONTO.
COMPRAR PRODUTOS: 3 PONTOS.
VENDER PRODUTOS: 3 PONTOS.
COMENTÁRIOS: 1 PONTO.