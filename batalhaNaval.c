#include <stdio.h>

/*
 * Desafio Batalha Naval - Nivel Aventureiro
 *
 * Este programa representa um tabuleiro 10x10 usando uma matriz e posiciona
 * quatro navios de tamanho fixo igual a 3: um na horizontal, um na vertical e
 * dois na diagonal. As posicoes com agua recebem o valor 0 e as partes dos
 * navios recebem o valor 3, conforme solicitado no enunciado.
 */

/* Constantes usadas para deixar o tamanho do tabuleiro e dos navios claro. */
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

/*
 * Verifica se um navio cabe no tabuleiro a partir da coordenada inicial.
 *
 * Parametros:
 * - linhaInicial e colunaInicial: coordenadas onde a primeira parte do navio
 *   sera posicionada.
 * - orientacao: indica o sentido do navio. 'H' representa horizontal, 'V'
 *   representa vertical, 'D' representa diagonal principal (linha e coluna
 *   aumentando) e 'I' representa diagonal inversa (linha aumentando e coluna
 *   diminuindo).
 *
 * Retorno:
 * - 1 quando todas as partes do navio ficam dentro do tabuleiro.
 * - 0 quando alguma parte ficaria fora dos limites.
 */
int coordenadasSaoValidas(int linhaInicial, int colunaInicial, char orientacao) {
    /* Coordenadas negativas ou maiores que o ultimo indice sao invalidas. */
    if (linhaInicial < 0 || linhaInicial >= TAMANHO_TABULEIRO ||
        colunaInicial < 0 || colunaInicial >= TAMANHO_TABULEIRO) {
        return 0;
    }

    /*
     * No navio horizontal, a linha permanece fixa e a coluna avanca.
     * Por isso, apenas a coluna final precisa ser comparada com o limite.
     */
    if (orientacao == 'H') {
        return colunaInicial + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
    }

    /*
     * No navio vertical, a coluna permanece fixa e a linha avanca.
     * Por isso, apenas a linha final precisa ser comparada com o limite.
     */
    if (orientacao == 'V') {
        return linhaInicial + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
    }

    /*
     * Na diagonal principal, linha e coluna aumentam ao mesmo tempo.
     * Portanto, a ultima linha e a ultima coluna precisam caber na matriz.
     */
    if (orientacao == 'D') {
        return linhaInicial + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
               colunaInicial + TAMANHO_NAVIO <= TAMANHO_TABULEIRO;
    }

    /*
     * Na diagonal inversa, a linha aumenta e a coluna diminui.
     * A linha final precisa caber e a coluna final nao pode ficar negativa.
     */
    if (orientacao == 'I') {
        return linhaInicial + TAMANHO_NAVIO <= TAMANHO_TABULEIRO &&
               colunaInicial - (TAMANHO_NAVIO - 1) >= 0;
    }

    /* Qualquer orientacao diferente de H, V, D ou I e considerada invalida. */
    return 0;
}

/*
 * Verifica se o navio pode ser colocado sem ocupar uma posicao ja preenchida.
 *
 * O tabuleiro e consultado antes da escrita. Se qualquer uma das posicoes ja
 * tiver o valor NAVIO, a funcao retorna 0 para impedir sobreposicao.
 */
int navioNaoSobrepoe(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linhaInicial,
                     int colunaInicial,
                     char orientacao) {
    int parte;

    /* Percorre as tres partes do navio para testar cada coordenada ocupada. */
    for (parte = 0; parte < TAMANHO_NAVIO; parte++) {
        int linha = linhaInicial;
        int coluna = colunaInicial;

        /* Ajusta a coordenada conforme a orientacao escolhida. */
        if (orientacao == 'H') {
            coluna = colunaInicial + parte;
        } else if (orientacao == 'V') {
            linha = linhaInicial + parte;
        } else if (orientacao == 'D') {
            linha = linhaInicial + parte;
            coluna = colunaInicial + parte;
        } else {
            linha = linhaInicial + parte;
            coluna = colunaInicial - parte;
        }

        /* Se a posicao ja contem navio, haveria sobreposicao. */
        if (tabuleiro[linha][coluna] == NAVIO) {
            return 0;
        }
    }

    return 1;
}

/*
 * Posiciona um navio no tabuleiro quando as validacoes forem atendidas.
 *
 * O vetor navio representa as partes do navio. Cada posicao do vetor contem o
 * valor 3 e esse valor e copiado para a matriz do tabuleiro na direcao
 * definida pela orientacao.
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                    int navio[TAMANHO_NAVIO],
                    int linhaInicial,
                    int colunaInicial,
                    char orientacao) {
    int parte;

    /* Primeiro, confirma se o navio permanece dentro dos limites da matriz. */
    if (!coordenadasSaoValidas(linhaInicial, colunaInicial, orientacao)) {
        return 0;
    }

    /* Depois, confirma se nenhuma parte do navio encosta em outro navio. */
    if (!navioNaoSobrepoe(tabuleiro, linhaInicial, colunaInicial, orientacao)) {
        return 0;
    }

    /* Copia cada parte do vetor do navio para a posicao correta da matriz. */
    for (parte = 0; parte < TAMANHO_NAVIO; parte++) {
        int linha = linhaInicial;
        int coluna = colunaInicial;

        /* Ajusta linha e coluna conforme horizontal, vertical ou diagonal. */
        if (orientacao == 'H') {
            coluna = colunaInicial + parte;
        } else if (orientacao == 'V') {
            linha = linhaInicial + parte;
        } else if (orientacao == 'D') {
            linha = linhaInicial + parte;
            coluna = colunaInicial + parte;
        } else {
            linha = linhaInicial + parte;
            coluna = colunaInicial - parte;
        }

        tabuleiro[linha][coluna] = navio[parte];
    }

    return 1;
}

/*
 * Exibe a matriz completa no console.
 *
 * O primeiro loop percorre as linhas e o segundo percorre as colunas,
 * imprimindo cada valor separado por espaco para facilitar a visualizacao.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int linha;
    int coluna;

    printf("Tabuleiro Batalha Naval - Nivel Aventureiro\n\n");

    for (linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
}

int main() {
    /*
     * Matriz que representa o tabuleiro 10x10.
     * Cada elemento sera inicializado com 0, que representa agua.
     */
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    /*
     * Vetores unidimensionais que representam os quatro navios.
     * Cada posicao possui o valor 3, usado para marcar navios no tabuleiro.
     */
    int navioHorizontal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioDiagonalPrincipal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioDiagonalInversa[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    /*
     * Coordenadas iniciais definidas diretamente no codigo, conforme a
     * simplificacao do nivel aventureiro. Os indices comecam em 0.
     */
    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 3;
    int linhaNavioVertical = 5;
    int colunaNavioVertical = 7;
    int linhaNavioDiagonalPrincipal = 0;
    int colunaNavioDiagonalPrincipal = 0;
    int linhaNavioDiagonalInversa = 0;
    int colunaNavioDiagonalInversa = 9;

    int linha;
    int coluna;

    /* Inicializa todas as posicoes da matriz com agua. */
    for (linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = AGUA;
        }
    }

    /* Tenta posicionar o navio horizontal e encerra se houver erro. */
    if (!posicionarNavio(tabuleiro, navioHorizontal, linhaNavioHorizontal,
                         colunaNavioHorizontal, 'H')) {
        printf("Erro: navio horizontal possui coordenadas invalidas ou sobreposicao.\n");
        return 1;
    }

    /* Tenta posicionar o navio vertical e encerra se houver erro. */
    if (!posicionarNavio(tabuleiro, navioVertical, linhaNavioVertical,
                         colunaNavioVertical, 'V')) {
        printf("Erro: navio vertical possui coordenadas invalidas ou sobreposicao.\n");
        return 1;
    }

    /* Tenta posicionar o navio na diagonal principal e encerra se houver erro. */
    if (!posicionarNavio(tabuleiro, navioDiagonalPrincipal,
                         linhaNavioDiagonalPrincipal,
                         colunaNavioDiagonalPrincipal, 'D')) {
        printf("Erro: navio diagonal principal possui coordenadas invalidas ou sobreposicao.\n");
        return 1;
    }

    /* Tenta posicionar o navio na diagonal inversa e encerra se houver erro. */
    if (!posicionarNavio(tabuleiro, navioDiagonalInversa,
                         linhaNavioDiagonalInversa,
                         colunaNavioDiagonalInversa, 'I')) {
        printf("Erro: navio diagonal inversa possui coordenadas invalidas ou sobreposicao.\n");
        return 1;
    }

    /* Mostra o tabuleiro final com agua representada por 0 e navios por 3. */
    exibirTabuleiro(tabuleiro);

    return 0;
}
