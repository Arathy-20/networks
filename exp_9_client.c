#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in server_addr;
    char filename[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    int n;

    // Create TCP socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Server running on same computer
    inet_pton(AF_INET, "127.0.0.1",
              &server_addr.sin_addr);

    // Connect to server
    connect(sock, (struct sockaddr *)&server_addr,
            sizeof(server_addr));

    printf("Enter filename: ");
    scanf("%s", filename);

    // Send filename
    send(sock, filename, strlen(filename) + 1, 0);

    printf("\nResponse from server:\n");

    // Receive PID + file contents / error message
    while ((n = recv(sock, buffer,
                     sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    close(sock);
    return 0;
}
