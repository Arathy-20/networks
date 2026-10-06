#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX 1024

struct Abbreviation {
    const char *abbr;
    const char *formal;
};

struct Abbreviation dict[] = {
    {"tbh",  "to be honest"},
    {"ig",   "I guess"},
    {"tbf",  "to be fair"},
    {"atm",  "at the moment"},
    {"irl",  "in real life"},
    {"lol",  "laughing out loud"},
    {"asap", "as soon as possible"},
    {"omg",  "oh my god"},
    {"ttyl", "talk to you later"},
    {"idk",  "I don't know"},
    {"nvm",  "never mind"}
};

#define DICT_SIZE (sizeof(dict) / sizeof(dict[0]))

int isWordChar(char c)
{
    return isalnum((unsigned char)c) || c == '_';
}

int matchAbbreviation(const char *text, int pos, const char *abbr)
{
    int len = strlen(abbr);

    // Check abbreviation itself
    for (int i = 0; i < len; i++) {
        if (tolower((unsigned char)text[pos + i]) !=
            tolower((unsigned char)abbr[i])) {
            return 0;
        }
    }

    // Make sure it is a complete word
    if (pos > 0 && isWordChar(text[pos - 1]))
        return 0;

    if (text[pos + len] != '\0' && isWordChar(text[pos + len]))
        return 0;

    return 1;
}

void translate(const char *input, char *output)
{
    int i = 0, out = 0;

    while (input[i] != '\0' && out < MAX - 1) {
        int found = 0;

        for (int j = 0; j < DICT_SIZE; j++) {
            int len = strlen(dict[j].abbr);

            if (matchAbbreviation(input, i, dict[j].abbr)) {
                int formalLen = strlen(dict[j].formal);

                if (out + formalLen >= MAX - 1)
                    break;

                strcpy(output + out, dict[j].formal);
                out += formalLen;
                i += len;
                found = 1;
                break;
            }
        }

        if (!found) {
            output[out++] = input[i++];
        }
    }

    output[out] = '\0';
}

int main()
{
    int sockfd;
    char buffer[MAX];
    char translated[MAX];

    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen = sizeof(clientAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    memset(&clientAddr, 0, sizeof(clientAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(sockfd,
             (const struct sockaddr *)&serverAddr,
             sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server is running on port %d...\n", PORT);

    while (1) {
        int n = recvfrom(sockfd, buffer, MAX - 1, 0,
                         (struct sockaddr *)&clientAddr,
                         &clientLen);

        if (n < 0) {
            perror("Receive failed");
            continue;
        }

        buffer[n] = '\0';

        printf("\nReceived: %s\n", buffer);

        translate(buffer, translated);

        printf("Translated: %s\n", translated);

        sendto(sockfd, translated, strlen(translated) + 1, 0,
               (const struct sockaddr *)&clientAddr,
               clientLen);
    }

    close(sockfd);
    return 0;
}
