// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 

char *ip;
int port;
   
int main(int argc, char const *argv[]) 
{ 
    if(argc < 3){
        fprintf(stderr, "./client <ip> <port>\n");
        exit(1);
    }
    ip = argv[1];
    port = atoi(argv[2]);

    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char *close = "close";
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    valread = read( sock , buffer, 1024); 
    printf("%.*s\n", valread, buffer ); 
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%.*s\n", valread, buffer ); 
    send(sock , close , strlen(close) , 0 ); 
    printf("Close message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%.*s\n", valread, buffer ); 
    return 0; 
} 