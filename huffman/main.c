#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

char ultimo_compactado[256] = "";
char ultimo_descompactado[256] = "";

int main() {
    int opcao;
    char entrada[256], saida[256];

    do {
        printf("\n==== Compactador de Arquivos - Huffman ====\n");
        printf("1. Compactar arquivo\n");
        printf("2. Descompactar arquivo\n");
        printf("3. Comparar tamanhos de arquivos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        getchar(); // limpar buffer

        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo de entrada: ");
                fgets(entrada, 256, stdin);
                entrada[strcspn(entrada, "\n")] = '\0';

                printf("Digite o nome do arquivo de saida compactado: ");
                fgets(saida, 256, stdin);
                saida[strcspn(saida, "\n")] = '\0';

                compactar_arquivo(entrada, saida);
                strncpy(ultimo_compactado, saida, 255);
                ultimo_compactado[255] = '\0';
                break;

            case 2:
                printf("Digite o nome do arquivo compactado: ");
                fgets(entrada, 256, stdin);
                entrada[strcspn(entrada, "\n")] = '\0';

                printf("Digite o nome do arquivo de saida descompactado: ");
                fgets(saida, 256, stdin);
                saida[strcspn(saida, "\n")] = '\0';

                descompactar_arquivo(entrada, saida);
                strncpy(ultimo_descompactado, saida, 255);
                ultimo_descompactado[255] = '\0';
                break;

            case 3:
                printf("Digite o nome do arquivo original: ");
                fgets(entrada, 256, stdin);
                entrada[strcspn(entrada, "\n")] = '\0';

                printf("Digite o nome do arquivo compactado: ");
                fgets(saida, 256, stdin);
                saida[strcspn(saida, "\n")] = '\0';

                comparar_tamanhos(entrada, saida);
                break;

            case 0:
                printf("Deseja remover os ultimos arquivos gerados? (s/n): ");
                {
                    char resp;
                    scanf(" %c", &resp);
                    if (resp == 's' || resp == 'S') {
                        if (strlen(ultimo_compactado) > 0 && remove(ultimo_compactado) == 0)
                            printf("Arquivo '%s' removido.\n", ultimo_compactado);
                        if (strlen(ultimo_descompactado) > 0 && remove(ultimo_descompactado) == 0)
                            printf("Arquivo '%s' removido.\n", ultimo_descompactado);
                    }
                }
                printf("\nSaindo...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
