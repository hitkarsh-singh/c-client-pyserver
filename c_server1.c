#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
//#include <uthash.h>

// Defining structure of the hash table
//typedef struct {
    //char name[50];
  //  UT_hash_handle hh;
//} NameEntry;

//NameEntry *nameMap = NULL;

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    
    // Entering the data into the hash table
    //NameEntry *newEntry = (NameEntry *)malloc(sizeof(NameEntry));
    //newEntry->name="Hitkarsh";
    //HASH_ADD_STRING(nameMap, name , newEntry);
    
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
     
    // Bind
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    // Listen
    listen(serverSocket, 5);

    // Accept connections and process data
    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);

        // Receive data
        char name[50];
        //sprintf(name,"");
        recv(clientSocket, name, sizeof(name), 0);

        // Check if name exists in the hashmap
        //NameEntry *entry;
        //HASH_FIND_STR(nameMap, name, entry);

        // Send response AS STRING
        char response[100];
        //if (entry) {
          //  snprintf(response, sizeof(response), "registered");
        //} else {
          //  snprintf(response, sizeof(response), "not_registered");
        //}
       
       
        if (strcmp(name, "JOHN") == 0) {
            snprintf(response, sizeof(response), "registered");
        } else {
            snprintf(response, sizeof(response), "not_registered");
        }
        send(clientSocket, response, strlen(response), 0);
        
        // Close
        printf("Received name: %s\n", name);
        
        close(clientSocket);
    }

    return 0;
}

