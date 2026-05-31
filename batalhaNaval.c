#include <stdio.h>

/*
 * Desafio Batalha Naval - Nivel Novato
 *
 * Este programa representa um tabuleiro 10x10 usando uma matriz e posiciona
 * dois navios de tamanho fixo igual a 3: um na horizontal e outro na vertical.
 * As posicoes com agua recebem o valor 0 e as partes dos navios recebem o
 * valor 3, conforme solicitado no enunciado.
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
 * - orientacao: indica o sentido do navio. 'H' representa horizontal e 'V'
 *   representa vertical.
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

    /* Qualquer orientacao diferente de H ou V e considerada invalida. */
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
        } else {
            linha = linhaInicial + parte;
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

        /* Na horizontal muda a coluna; na vertical muda a linha. */
        if (orientacao == 'H') {
            coluna = colunaInicial + parte;
        } else {
            linha = linhaInicial + parte;
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

    printf("Tabuleiro Batalha Naval - Nivel Novato\n\n");

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
     * Vetores unidimensionais que representam os dois navios.
     * Cada posicao possui o valor 3, usado para marcar navios no tabuleiro.
     */
    int navioHorizontal[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    /*
     * Coordenadas iniciais definidas diretamente no codigo, conforme a
     * simplificacao do nivel novato. Os indices comecam em 0.
     */
    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 3;
    int linhaNavioVertical = 5;
    int colunaNavioVertical = 7;

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

    /* Mostra o tabuleiro final com agua representada por 0 e navios por 3. */
    exibirTabuleiro(tabuleiro);

    return 0;
}
