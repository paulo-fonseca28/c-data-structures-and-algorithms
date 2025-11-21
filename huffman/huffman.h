#ifndef HUFFMAN_H
#define HUFFMAN_H

#define TAM 256

typedef struct node {
    char caractere;
    int frequencia;
    struct node *left, *right;
} Node;

Node* construir_arvore_huffman(int freq[TAM]);
void gerar_codigos(Node* raiz, char* codigo, int profundidade, char* tabela[TAM]);
void liberar_arvore(Node* raiz);
void compactar_arquivo(const char* entrada, const char* saida);
void descompactar_arquivo(const char* entrada, const char* saida);
void comparar_tamanhos(const char* original, const char* compactado);

#endif
