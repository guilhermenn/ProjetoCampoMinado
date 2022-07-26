## ProjetoCampoMinado

## Jogo:
O jogo consiste em uma área matricial de n linhas por m colunas com um total de n*m células e k minas. Inicialmente, as células estão ocultas, ou seja, não é possível determinar se ela possui uma mina ou não. O objetivo do jogo é revelar todas as células sem revelar uma das minas.

## Regras:
- **1** Uma mina é revelada: nesse caso, jogo encerra com a derrota do usuário;
- **2** Um número é revelado: o valor indica a quantidade de minas adjacentes considerando as 8 células ao redor de uma posição (vertical, horizontal e diagonais);
- **3** Uma posição vazia é revelada: nesse caso, o jogo aplica a ação revelar sobre todas as células adjacentes a essa posição, visto que ela não possui minas adjacentes.

## Condições de Vitória:
O usuário vence o jogo ao revelar todas as células que não contêm minas. Por fim, a dificuldade do jogo irá determinar as dimensões da área do jogo e a quantidade de minas.
