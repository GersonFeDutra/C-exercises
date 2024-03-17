Desenvolva um programa paralelo, com MPI, (com p processos) para verificar a paridade de um
arquivo binário (considere um vetor binário).
Ou seja, verifique o numero de 0’s e 1’s existentes no arquivo e
adicione um 0 ou um 1 ao arquivo de tal forma que o número de 1’s seja par.

> Envie apenas o link do github do arquivo desenvolvido

```C
int *gerar_vetor_binario(int n) {
  int *vetor;
  int i; 
  vetor = (int *)malloc(sizeof(int) * n);
  for (i=0;i<n;i++) {
    int num = rand() % 2;
    vetor[i] = num;
  }
  return vetor;
}
```
