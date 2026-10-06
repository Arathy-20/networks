#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int sockfd;
    char buffer[BUFFER_SIZE];
    char message[] = "TIME";

    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);

    if (argc != 2) {
        printf("Usage: %s <server-ip>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Create UDP socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    /* Configure server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("Invalid server address");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    /* Send time request */
    if (sendto(sockfd,
               message,
               strlen(message) + 1,
               0,
               (const struct sockaddr *)&server_addr,
               sizeof(server_addr)) < 0) {
        perror("sendto failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Time request sent to server...\n");

    /* Receive server time */
    int n = recvfrom(sockfd,
                     buffer,
                     BUFFER_SIZE - 1,
                     0,
                     (struct sockaddr *)&server_addr,
                     &server_len);

    if (n < 0) {
        perror("recvfrom failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';

    printf("Time received from server: %s", buffer);

    close(sockfd);
    return 0;
}
