#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node* novo_no(char caractere, int frequencia) {
    Node* no = (Node*)malloc(sizeof(Node));
    no->caractere = caractere;
    no->frequencia = frequencia;
    no->left = no->right = NULL;
    return no;
}

// Funcao para inserir um no em uma lista ordenada por frequencia
static void inserir_ordenado(Node** lista, int* tamanho, Node* novo) {
    int i = *tamanho - 1;
    while (i >= 0 && lista[i]->frequencia > novo->frequencia) {
        lista[i + 1] = lista[i];
        i--;
    }
    lista[i + 1] = novo;
    (*tamanho)++;
}

// Funcao para criar arvore huffman
Node* construir_arvore_huffman(int freq[TAM]) {
    Node* lista[TAM];
    int tamanho = 0;

    for (int i = 0; i < TAM; i++) {
        if (freq[i] > 0) {
            lista[tamanho++] = novo_no((char)i, freq[i]);
        }
    }

    if (tamanho == 0) {
        return NULL;
    }

    while (tamanho > 1) {
        Node* esquerda = lista[0];
        Node* direita = lista[1];

        for (int i = 2; i < tamanho; i++) {
            lista[i - 2] = lista[i];
        }
        tamanho -= 2;

        Node* pai = novo_no('\0', esquerda->frequencia + direita->frequencia);
        pai->left = esquerda;
        pai->right = direita;

        inserir_ordenado(lista, &tamanho, pai);
    }

    return lista[0];
}

// Gera tabela de codigos de Huffman
void gerar_codigos(Node* raiz, char* codigo, int profundidade, char* tabela[TAM]) {
    if (!raiz) return;

    if (!raiz->left && !raiz->right) {
        codigo[profundidade] = '\0';
        tabela[(unsigned char)raiz->caractere] = strdup(codigo);
        return;
    }

    codigo[profundidade] = '0';
    gerar_codigos(raiz->left, codigo, profundidade + 1, tabela);

    codigo[profundidade] = '1';
    gerar_codigos(raiz->right, codigo, profundidade + 1, tabela);
}

// libera memoria
void liberar_arvore(Node* raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->left);
    liberar_arvore(raiz->right);
    free(raiz);
}

//compactar arquivos
void compactar_arquivo(const char* entrada, const char* saida) {
    FILE* fin = fopen(entrada, "rb");
    if (!fin) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    int freq[TAM] = {0};
    int c;
    long total = 0;

    while ((c = fgetc(fin)) != EOF) {
        freq[(unsigned char)c]++;
        total++;
    }
    rewind(fin);

    FILE* fout = fopen(saida, "wb");
    if (!fout) {
        printf("Erro ao abrir o arquivo de saida.\n");
        fclose(fin);
        return;
    }

    /* Escreve o cabecalho com as frequencias */
    if (fwrite(freq, sizeof(int), TAM, fout) != TAM) {
        printf("Erro ao escrever o cabecalho no arquivo de saida.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    /* Caso especial: arquivo vazio */
    if (total == 0) {
        printf("Arquivo de entrada vazio. Nada foi compactado.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    Node* raiz = construir_arvore_huffman(freq);
    if (!raiz) {
        printf("Erro ao construir a arvore de Huffman.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    char* tabela[TAM] = {0};
    char codigo[256];
    gerar_codigos(raiz, codigo, 0, tabela);

    /* Codifica o conteudo */
    unsigned char buffer = 0;
    int bits_usados = 0;

    while ((c = fgetc(fin)) != EOF) {
        char* codigo_bin = tabela[(unsigned char)c];
        if (!codigo_bin) {
            continue;
        }
        for (int i = 0; codigo_bin[i]; i++) {
            buffer <<= 1;
            if (codigo_bin[i] == '1') buffer |= 1;
            bits_usados++;
            if (bits_usados == 8) {
                fputc(buffer, fout);
                bits_usados = 0;
                buffer = 0;
            }
        }
    }

    if (bits_usados > 0) {
        buffer <<= (8 - bits_usados);
        fputc(buffer, fout);
    }

    fclose(fin);
    fclose(fout);

    for (int i = 0; i < TAM; i++) {
        if (tabela[i]) free(tabela[i]);
    }
    liberar_arvore(raiz);

    printf("Arquivo compactado com sucesso.\n");
}

void descompactar_arquivo(const char* entrada, const char* saida) {
    FILE* fin = fopen(entrada, "rb");
    if (!fin) {
        printf("Erro ao abrir o arquivo compactado.\n");
        return;
    }

    int freq[TAM];
    if (fread(freq, sizeof(int), TAM, fin) != TAM) {
        printf("Erro ao ler o cabecalho do arquivo compactado.\n");
        fclose(fin);
        return;
    }

    long total = 0;
    for (int i = 0; i < TAM; i++) {
        total += freq[i];
    }

    FILE* fout = fopen(saida, "wb");
    if (!fout) {
        printf("Erro ao criar arquivo de saida.\n");
        fclose(fin);
        return;
    }

    /* Caso especial: nada para descompactar */
    if (total == 0) {
        printf("Arquivo compactado nao contem dados.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    Node* raiz = construir_arvore_huffman(freq);
    if (!raiz) {
        printf("Erro ao reconstruir a arvore de Huffman.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    /* Caso especial: apenas um simbolo diferente no arquivo original */
    if (!raiz->left && !raiz->right) {
        for (long i = 0; i < total; i++) {
            fputc(raiz->caractere, fout);
        }
        fclose(fin);
        fclose(fout);
        liberar_arvore(raiz);
        printf("Arquivo descompactado com sucesso.\n");
        return;
    }

    Node* atual = raiz;
    long lidos = 0;
    int byte;

    while ((byte = fgetc(fin)) != EOF && lidos < total) {
        for (int i = 7; i >= 0 && lidos < total; i--) {
            int bit = (byte >> i) & 1;
            atual = bit ? atual->right : atual->left;
            if (!atual->left && !atual->right) {
                fputc(atual->caractere, fout);
                atual = raiz;
                lidos++;
            }
        }
    }

    fclose(fin);
    fclose(fout);
    liberar_arvore(raiz);

    printf("Arquivo descompactado com sucesso.\n");
}

void comparar_tamanhos(const char* original, const char* compactado) {
    FILE* f1 = fopen(original, "rb");
    FILE* f2 = fopen(compactado, "rb");
    if (!f1 || !f2) {
        printf("Erro ao abrir os arquivos para comparacao.\n");
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return;
    }
    fseek(f1, 0, SEEK_END);
    fseek(f2, 0, SEEK_END);
    long tamanho1 = ftell(f1);
    long tamanho2 = ftell(f2);
    fclose(f1);
    fclose(f2);

    printf("Tamanho original: %ld bytes\n", tamanho1);
    printf("Tamanho compactado: %ld bytes\n", tamanho2);
    printf("Compressao: %.2f%%\n", 100.0 * (1.0 - (double)tamanho2 / tamanho1));
}
