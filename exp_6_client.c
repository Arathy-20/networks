#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sockfd, n;
    char buffer[BUFFER_SIZE];
    char message[] = "TIME";

    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send time request to server
    sendto(sockfd,
           message,
           strlen(message),
           0,
           (struct sockaddr *)&server_addr,
           sizeof(server_addr));

    printf("Time request sent to server.\n");

    // Receive time from server
    n = recvfrom(sockfd,
                 buffer,
                 BUFFER_SIZE - 1,
                 0,
                 (struct sockaddr *)&server_addr,
                 &server_len);

    buffer[n] = '\0';

    // Display received time
    printf("Server time: %s", buffer);

    close(sockfd);

    return 0;
}
