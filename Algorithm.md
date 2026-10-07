6. Client–Server Communication using UDP — Abbreviation Translator
Server Algorithm
1. Start the server.
2. Create a UDP socket using socket().
3. Initialize the server address with IP address and port number.
4. Bind the socket to the server address using bind().
5. Receive the sentence from the client using recvfrom().
6. Search the received sentence for the specified abbreviations (tbh, ig, tbf, atm, irl, lol, asap, omg, ttyl, idk, nvm).
7. Replace each abbreviation with its corresponding formal English phrase.
8. Send the translated sentence back to the client using sendto().
9. Close the socket.
10. Stop.
Client Algorithm
1. Start the client.
2. Create a UDP socket using socket().
3. Initialize the server address with server IP address and port number.
4. Read the new-generation English sentence from the user.
5. Send the sentence to the server using sendto().
6. Receive the translated sentence from the server using recvfrom().
7. Display the translated sentence.
8. Close the socket.
9. Stop.



8. Concurrent Time Server using UDP
Server Algorithm
1. Start the server.
2. Create a UDP socket using socket().
3. Initialize the server address with IP address and port number.
4. Bind the socket using bind().
5. Wait for a time request from a client using recvfrom().
6. On receiving a request, create a child process/thread to handle the client.
7. Obtain the current system time.
8. Convert the system time into a readable format.
9. Send the current time to the client using sendto().
10. Continue waiting for requests from other clients.
11. Close the socket when the server terminates.
Client Algorithm
1. Start the client.
2. Create a UDP socket.
3. Initialize the server address with server IP address and port number.
4. Send a time request to the server using sendto().
5. Receive the system time from the server using recvfrom().
6. Display the received time.
7. Close the socket.
8. Stop.


9. Concurrent File Server
Server Algorithm
1. Start the server.
2. Create a server socket.
3. Initialize the server address with IP address and port number.
4. Bind the socket to the server address.
5. Listen for client connections.
6. Accept a client connection.
7. Create a child process to handle the connected client.
8. Receive the requested filename from the client.
9. Obtain the PID of the process using getpid().
10. Check whether the requested file exists.
11. If the file exists, open it and read its contents.
12. Send the PID and file contents to the client.
13. If the file does not exist, send the PID and an appropriate “File not found” message.
14. Close the file and client socket.
15. The server continues accepting other client connections.
16. Close the server socket when terminated.
Client Algorithm
1. Start the client.
2. Create a socket.
3. Initialize the server address.
4. Connect to the server.
5. Read the filename from the user.
6. Send the filename to the server.
7. Receive the server PID and response.
8. Display the PID.
9. Display the file contents if the file exists; otherwise display the error message.
10. Close the socket.
11. Stop.
