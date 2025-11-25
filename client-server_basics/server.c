#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

double calculate(char operation, double op1, double op2) {
    switch (operation) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/':
            if (op2 == 0) return 0.0;  // simples tratamento de divisão por zero
            return op1 / op2;
        default:
            return 0.0;
    }
}

int main(void) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Allow reuse of address/port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 3) == -1) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Accept single client (poderia virar loop para múltiplos)
    new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (new_socket == -1) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);

        if (bytes_read <= 0) {
            printf("Client disconnected or read error.\n");
            break;
        }

        // Espera formato: "<op> <op1> <op2>"
        char operation;
        double op1, op2;
        int parsed = sscanf(buffer, "%c %lf %lf", &operation, &op1, &op2);

        if (parsed != 3) {
            const char *error_msg = "Invalid format. Use: <op> <num1> <num2>\n";
            send(new_socket, error_msg, strlen(error_msg), 0);
            continue;
        }

        double result = calculate(operation, op1, op2);

        char response[128];
        snprintf(response, sizeof(response), "%.4lf\n", result);
        send(new_socket, response, strlen(response), 0);

        printf("Received: '%c' %.4lf %.4lf -> Result: %.4lf\n",
               operation, op1, op2, result);
    }

    close(new_socket);
    close(server_fd);
    printf("Server shut down.\n");
    return 0;
}
