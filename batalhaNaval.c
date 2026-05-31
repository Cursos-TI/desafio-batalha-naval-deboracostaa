#include <stdio.h>
#include <stdlib.h>

/*
 * Desafio Batalha Naval - Nivel Mestre
 *
 * Este programa representa um tabuleiro 10x10 usando uma matriz e posiciona
 * quatro navios de tamanho fixo igual a 3: um na horizontal, um na vertical e
 * dois na diagonal. Em seguida, cria matrizes de habilidades especiais em
 * formato de cone, cruz e octaedro, aplicando suas areas de efeito ao
 * tabuleiro. Agua recebe 0, navios recebem 3 e areas afetadas recebem 5.
 */

/* Constantes usadas para deixar o tamanho do tabuleiro e dos navios claro. */
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define AREA_AFETADA 5

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

    printf("Tabuleiro Batalha Naval - Nivel Mestre\n\n");

    for (linha = 0; linha < TAMANHO_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
}

/*
 * Constroi dinamicamente as matrizes das habilidades especiais.
 *
 * Cada matriz usa 1 para indicar uma posicao afetada e 0 para indicar uma
 * posicao fora da area de efeito. Os formatos sao calculados com condicionais:
 * - Cone: expande a partir do topo central em direcao a base.
 * - Cruz: marca a linha central e a coluna central.
 * - Octaedro: usa distancia em linhas e colunas para formar um losango.
 */
void criarMatrizesDeHabilidade(
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int linha;
    int coluna;
    int centro = TAMANHO_HABILIDADE / 2;

    /* Os loops aninhados percorrem cada celula das tres matrizes. */
    for (linha = 0; linha < TAMANHO_HABILIDADE; linha++) {
        for (coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++) {
            /*
             * No cone, a linha define a largura afetada. Quanto mais baixa a
             * linha, maior a distancia permitida em relacao ao centro.
             */
            if (coluna >= centro - linha && coluna <= centro + linha) {
                cone[linha][coluna] = 1;
            } else {
                cone[linha][coluna] = 0;
            }

            /*
             * Na cruz, qualquer celula na linha central ou coluna central faz
             * parte da area de efeito.
             */
            if (linha == centro || coluna == centro) {
                cruz[linha][coluna] = 1;
            } else {
                cruz[linha][coluna] = 0;
            }

            /*
             * No octaedro visto de frente, o formato e um losango. A soma das
             * distancias ate o centro define se a celula fica dentro da forma.
             */
            if (abs(linha - centro) + abs(coluna - centro) <= centro) {
                octaedro[linha][coluna] = 1;
            } else {
                octaedro[linha][coluna] = 0;
            }
        }
    }
}

/*
 * Sobrepoe uma matriz de habilidade ao tabuleiro.
 *
 * O ponto de origem recebido representa o centro da habilidade no tabuleiro.
 * Para cada celula afetada na matriz de habilidade, a funcao calcula a posicao
 * correspondente no tabuleiro. As condicionais impedem acesso fora dos limites
 * e mantem os navios com valor 3 para que eles continuem visiveis.
 */
void aplicarHabilidadeNoTabuleiro(
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
    int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
    int linhaOrigem,
    int colunaOrigem) {
    int linha;
    int coluna;
    int centro = TAMANHO_HABILIDADE / 2;

    /* Percorre a matriz da habilidade para mapear suas celulas ao tabuleiro. */
    for (linha = 0; linha < TAMANHO_HABILIDADE; linha++) {
        for (coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++) {
            int linhaTabuleiro = linhaOrigem + linha - centro;
            int colunaTabuleiro = colunaOrigem + coluna - centro;

            /*
             * A habilidade so e aplicada quando a celula vale 1 e a posicao
             * calculada esta dentro da matriz 10x10 do tabuleiro.
             */
            if (habilidade[linha][coluna] == 1 &&
                linhaTabuleiro >= 0 && linhaTabuleiro < TAMANHO_TABULEIRO &&
                colunaTabuleiro >= 0 && colunaTabuleiro < TAMANHO_TABULEIRO) {
                /*
                 * As areas afetadas sao marcadas com 5 apenas sobre agua,
                 * preservando partes de navios marcadas com 3.
                 */
                if (tabuleiro[linhaTabuleiro][colunaTabuleiro] == AGUA) {
                    tabuleiro[linhaTabuleiro][colunaTabuleiro] = AREA_AFETADA;
                }
            }
        }
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
     * Matrizes 5x5 que representam as habilidades especiais.
     * Elas serao preenchidas com 0 e 1 por meio de loops e condicionais.
     */
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    /*
     * Coordenadas iniciais definidas diretamente no codigo, conforme a
     * simplificacao do nivel mestre. Os indices comecam em 0.
     */
    int linhaNavioHorizontal = 9;
    int colunaNavioHorizontal = 0;
    int linhaNavioVertical = 5;
    int colunaNavioVertical = 9;
    int linhaNavioDiagonalPrincipal = 5;
    int colunaNavioDiagonalPrincipal = 0;
    int linhaNavioDiagonalInversa = 7;
    int colunaNavioDiagonalInversa = 8;

    /*
     * Pontos de origem das habilidades no tabuleiro.
     * Cada origem representa o centro usado para sobrepor a matriz 5x5.
     * As posicoes foram escolhidas em regioes separadas para facilitar a
     * visualizacao dos formatos no console.
     */
    int linhaOrigemCone = 2;
    int colunaOrigemCone = 2;
    int linhaOrigemCruz = 3;
    int colunaOrigemCruz = 8;
    int linhaOrigemOctaedro = 7;
    int colunaOrigemOctaedro = 5;

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

    /* Cria as areas de efeito das habilidades especiais nas matrizes 5x5. */
    criarMatrizesDeHabilidade(habilidadeCone, habilidadeCruz,
                              habilidadeOctaedro);

    /* Aplica as habilidades no tabuleiro, marcando as areas afetadas com 5. */
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeCone, linhaOrigemCone,
                                 colunaOrigemCone);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeCruz, linhaOrigemCruz,
                                 colunaOrigemCruz);
    aplicarHabilidadeNoTabuleiro(tabuleiro, habilidadeOctaedro,
                                 linhaOrigemOctaedro, colunaOrigemOctaedro);

    /* Mostra o tabuleiro final: agua 0, navios 3 e areas afetadas 5. */
    exibirTabuleiro(tabuleiro);

    return 0;
}
