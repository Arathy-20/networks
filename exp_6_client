#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

int main()
{
    int sockfd;
    char buffer[MAX];

    struct sockaddr_in serverAddr;
    socklen_t serverLen = sizeof(serverAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    // Server is running on the same machine
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter a new-generation English sentence:\n");
    fgets(buffer, MAX, stdin);

    // Remove newline added by fgets()
    buffer[strcspn(buffer, "\n")] = '\0';

    sendto(sockfd, buffer, strlen(buffer) + 1, 0,
           (const struct sockaddr *)&serverAddr,
           sizeof(serverAddr));

    printf("\nSentence sent to server.\n");

    int n = recvfrom(sockfd, buffer, MAX - 1, 0,
                     (struct sockaddr *)&serverAddr,
                     &serverLen);

    if (n < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';

    printf("Formal English: %s\n", buffer);

    close(sockfd);

    return 0;
}
