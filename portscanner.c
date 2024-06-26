#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<time.h>

// Function to scan a port on a specific IP address
int scan_port(char *ip_address, int port) {

    // Create a TCP socket
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Failed to create socket");
        return -1;
    }

    
// Set the IP address and port for the socket
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ip_address);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    
// Connect the socket to the port at the IP address
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        
    // The port is not open
        close(socket_desc);
        return 0;
    } else {
        
    // The port is open
        close(socket_desc);
        return 1;
    }
}

int main() {
    char ip_address[16]; // Assuming IPv4 address, maximum length is 15 characters
    int port_start, port_end;
    int open_count = 0,close_count = 0;
    time_t start, end;
    double time_taken;

    // Enter the IP address
    printf("\nEnter IP address: ");
    scanf("%15s", ip_address); // Limit input to prevent buffer overflow

    // Enter the starting port
    printf("\nEnter starting port: ");
    scanf("%d", &port_start);

    // Enter the ending port
    printf("\nEnter ending port: ");
    scanf("%d", &port_end);
    
    int number_of_ports = port_end - port_start + 1;
    printf("\nScanning ports on%15s",ip_address);
    printf("\n\nPlease wait...this may take some time...\n\n\n");
    
    // Get the current time as the start time
    start = time(NULL); 
    for (int port = port_start; port <= port_end; port++) {
        if (scan_port(ip_address, port)) {
            open_count++;
            printf("Port %d is open\n", port);
        }
        else{
            close_count++;
            printf("port %d is closed\n",port);
        }
    }
    
    // Get the current time as the end time
    end = time(NULL); 

    // Calculate the time taken in seconds
    time_taken = difftime(end, start); 
    printf("\nTotal open ports: %d\n", open_count);
    printf("\nTotal closed ports: %d\n", close_count);
    printf("\nTotal ports scanned: %d\n", open_count + close_count);
    printf("\n\n");
    printf("%d ports are scanned in %.2f seconds\n\n",number_of_ports,time_taken);


    return 0;
}
