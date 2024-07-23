#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 100

// Struct to pass arguments to the thread function
struct ThreadArgs {
    char ip_address[16];
    int port;
};

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

// Thread function to scan a port
void *thread_scan_port(void *args) {
    struct ThreadArgs *thread_args = (struct ThreadArgs *)args;
    int result = scan_port(thread_args->ip_address, thread_args->port);

    if (result) {
        printf("Port %d is open\n", thread_args->port);
    } else {
        printf("Port %d is closed\n", thread_args->port);
    }

    free(thread_args);
    pthread_exit(NULL);
}

int main() {
    char ip_address[16]; // Assuming IPv4 address, maximum length is 15 characters
    int port_start, port_end;
    int open_count = 0, close_count = 0;
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
    printf("\nScanning ports on %s\n", ip_address);
    printf("\nPlease wait...this may take some time...\n\n");

    // Get the current time as the start time
    start = time(NULL);

    pthread_t threads[MAX_THREADS];
    int thread_count = 0;

    for (int port = port_start; port <= port_end; port++) {
        struct ThreadArgs *args = (struct ThreadArgs *)malloc(sizeof(struct ThreadArgs));
        strcpy(args->ip_address, ip_address);
        args->port = port;

        // Create a thread to scan the port
        pthread_create(&threads[thread_count], NULL, thread_scan_port, (void *)args);
        thread_count++;

        // Limit the number of concurrent threads
        if (thread_count >= MAX_THREADS) {
            for (int i = 0; i < thread_count; i++) {
                pthread_join(threads[i], NULL);
            }
            thread_count = 0;
        }
    }

    // Join remaining threads
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
    }

    // Get the current time as the end time
    end = time(NULL);

    // Calculate the time taken in seconds
    time_taken = difftime(end, start);
    printf("\nTotal open ports: %d\n", open_count);
    printf("Total closed ports: %d\n", close_count);
    printf("Total ports scanned: %d\n", open_count + close_count);
    printf("\n%d ports are scanned in %.2f seconds\n\n", number_of_ports, time_taken);

    return 0;
}
