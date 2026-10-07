#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char filename[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    bind(server_fd, (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    // Listen for clients
    listen(server_fd, 5);

    printf("Server is waiting for clients...\n");

    while (1)
    {
        client_fd = accept(server_fd,
                           (struct sockaddr *)&client_addr,
                           &client_len);

        // Create child process for each client
        pid_t pid = fork();

        if (pid == 0)
        {
            // Child doesn't need listening socket
            close(server_fd);

            memset(filename, 0, sizeof(filename));

            // Receive requested filename
            recv(client_fd, filename, sizeof(filename), 0);

            // Child process PID
            pid_t child_pid = getpid();

            snprintf(buffer, sizeof(buffer),
                     "Server PID: %d\n", child_pid);

            send(client_fd, buffer, strlen(buffer), 0);

            // Try to open requested file
            FILE *fp = fopen(filename, "r");

            if (fp == NULL)
            {
                strcpy(buffer, "File not found.\n");
                send(client_fd, buffer, strlen(buffer), 0);
            }
            else
            {
                while (fgets(buffer, sizeof(buffer), fp) != NULL)
                {
                    send(client_fd, buffer, strlen(buffer), 0);
                }

                fclose(fp);
            }

            close(client_fd);
            exit(0);
        }
        else
        {
            // Parent doesn't need client socket
            close(client_fd);
        }
    }

    close(server_fd);
    return 0;
}
