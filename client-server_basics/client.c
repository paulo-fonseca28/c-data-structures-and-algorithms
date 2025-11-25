#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(void) {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[1024];

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation error");
        return EXIT_FAILURE;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        close(sock);
        return EXIT_FAILURE;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return EXIT_FAILURE;
    }

    printf("Connected to server on 127.0.0.1:%d\n", PORT);
    printf("Operations: +  -  *  /\n");
    printf("Type 'q' as operation to quit.\n");

    while (1) {
        char operation;
        double op1, op2;

        printf("\nEnter operation and two numbers (e.g. + 2 3): ");
        // Espaço antes de %c ignora newline residual
        if (scanf(" %c", &operation) != 1) {
            printf("Input error.\n");
            break;
        }

        if (operation == 'q' || operation == 'Q') {
            printf("Exiting client.\n");
            break;
        }

        if (scanf("%lf %lf", &op1, &op2) != 2) {
            printf("Invalid numbers.\n");
            // Limpa stdin
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        snprintf(buffer, sizeof(buffer), "%c %lf %lf", operation, op1, op2);
        send(sock, buffer, strlen(buffer), 0);

        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(sock, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0) {
            printf("Server closed connection.\n");
            break;
        }

        printf("Result from server: %s", buffer);
    }

    close(sock);
    return 0;
}
