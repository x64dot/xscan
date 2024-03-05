#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void default_scan(char* target);
void scan_all(char* target);

int main(int argc, char* argv[]){
    char *target = NULL;
    int t_flag_found = 0; 

    if (argc < 2){
        printf("[!] No arguments were supplied.\n");
        return -1;
    }
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-t") == 0){
            target = argv[i + 1];
            
            if (target == NULL){
                printf("[!] You must supply a IP address.\n");
            }

            t_flag_found = 1;

        }
        else if (strcmp(argv[i], "-ap") == 0){
            if (target == NULL){
                printf("[!] You must supply a IP address.\n");
            }
            else{
                scan_all(target);
            }
        }
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-hh") == 0){
            printf("Usage: %s -t [target_ip] -ap\n", argv[0]);
            printf("Options:\n");
            printf("  -t [target_ip]    Specify the target IP address\n");
            printf("  -ap               Perform a port scan on the target\n");

            return 0;
        }
        else{}
    }

    if (target != NULL && t_flag_found == 1) {
        default_scan(target);
    }

    return 0;
}

void scan_all(char* target){
    struct sockaddr_in sa;

    if (inet_pton(AF_INET, target, &sa.sin_addr) == 0){
        printf("[!] Invalid IP address.");
    }
    
    sa.sin_family = AF_INET;
    for (int i = 1; i <= 65535; i++){
        sa.sin_port = htons(i);
        struct timeval timeout;

        timeout.tv_sec = 1; 
        timeout.tv_usec = 0;

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

        if (connect(sockfd, (struct sockaddr*)&sa, sizeof(sa)) == 0){
            printf("[+] Port %d is open\n", i);

            close(sockfd);
        }
        close(sockfd);
    }

}

void default_scan(char* target){
    struct sockaddr_in sa;

    if (inet_pton(AF_INET, target, &sa.sin_addr) == 0){
        printf("[!] Invalid IP address.");
    }

    sa.sin_family = AF_INET;

    for (int i = 1; i <= 1000; i++){
        sa.sin_port = htons(i);
        struct timeval timeout;

        timeout.tv_sec = 1; 
        timeout.tv_usec = 0;

        int sockfd = socket(AF_INET, SOCK_STREAM, 0);

        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

        if (connect(sockfd, (struct sockaddr*)&sa, sizeof(sa)) == 0){
            printf("[+] Port %d is open\n", i);

            close(sockfd);
        }
        close(sockfd);
    } 
}