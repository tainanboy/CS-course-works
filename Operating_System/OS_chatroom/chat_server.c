#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>

#define MAX_CLIENTS	50
#define PORT 5000

static unsigned int cli_count = 0; /*Connected-clients count*/
static int uid = 10; /*Client unique identifier, start with 10 */

/* Client structure */
typedef struct { 
	struct sockaddr_in addr;	/* Client remote address */
	int connfd;			/* Connection file descriptor */
	int uid;			/* Client unique identifier */
	char name[32];			/* Client name */
} client_t;

client_t *clients[MAX_CLIENTS]; /* dynamic queue */

/* Add client to queue */
void client_add(client_t *cl){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i]==0){
			clients[i] = cl; 
			return;
		}
	}
}

/* Delete client from queue */
void client_delete(int uid){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i]){
			if(clients[i]->uid == uid){
				clients[i] = NULL;
				return;
			}
		}
	}
}

/* Send message to all clients except the sender */
void send_message(char *s, int uid){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i]){
			if(clients[i]->uid != uid){
				write(clients[i]->connfd, s, strlen(s));
			}
		}
	}
}

/* Send message to all clients */
void send_message_all(char *s){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i]){
			write(clients[i]->connfd, s, strlen(s));
		}
	}
}

/* Send message to sender */
void send_message_self(const char *s, int connfd){
	write(connfd, s, strlen(s));
}

/* Send message to client */
void send_message_client(char *s, int uid){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i]){
			if(clients[i]->uid == uid){
				write(clients[i]->connfd, s, strlen(s));
			}
		}
	}
}

/* Send list of active clients */
void send_active_clients(int connfd){
	int i;
	char s[64];
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i]){
			sprintf(s, "<<Client %d | %s\r\n", clients[i]->uid, clients[i]->name);
			send_message_self(s, connfd);
		}
	}
}

/* Strip CRLF */
void strip_newline(char *s){
	while(*s != '\0'){
		if(*s == '\r' || *s == '\n'){
			*s = '\0';
		}
		s++;
	}
}

/* Print ip address */
void print_client_addr(struct sockaddr_in addr){
	printf("%d.%d.%d.%d",
		addr.sin_addr.s_addr & 0xFF,
		(addr.sin_addr.s_addr & 0xFF00)>>8,
		(addr.sin_addr.s_addr & 0xFF0000)>>16,
		(addr.sin_addr.s_addr & 0xFF000000)>>24);
}

/* Handle all communication with the client */
void *handle_client(void *arg){
	char buff_out[1024];
	char buff_in[1024];
	int rlen;

	cli_count++;
	client_t *cli = (client_t *)arg;

	printf("<<Client Accept: ");
	print_client_addr(cli->addr);
	printf(" Port number %d\n", cli->uid);

	sprintf(buff_out, "<<Welcome! Hello %s\r\n", cli->name); /*content is stored as string in buff_out*/
	send_message_all(buff_out);

	/* Receive input from client */
	while((rlen = read(cli->connfd, buff_in, sizeof(buff_in)-1)) > 0){
	        buff_in[rlen] = '\0';
	        buff_out[0] = '\0';
		strip_newline(buff_in);

		/* Ignore empty buffer */
		if(strlen(buff_in)==0){
			continue;
		}
	
		/* Special options */
		if(buff_in[0] == '\\'){  /*special operations use \\ to start*/
			char *command, *param; 
			command = strtok(buff_in," "); /*split buuf_in into tokens*/
			if(strcmp(command, "\\quit")==0){ /*compare strings if same retutn 0*/
				break;
			}
			else if(strcmp(command, "\\ping")==0){
				send_message_self("<<pong\r\n", cli->connfd);
			}
			else if(strcmp(command, "\\name")==0){
				param = strtok(NULL, " ");
				if(param){
					char *old_name = strdup(cli->name);
					strcpy(cli->name, param);
					sprintf(buff_out, "<<RENAME, %s TO %s\r\n", old_name, cli->name);
					free(old_name);
					send_message_all(buff_out);
				}
				else{
					send_message_self("<<NAME CANNOT BE NULL\r\n", cli->connfd);
				}
			}
			else if(strcmp(command, "\\private")==0){
				param = strtok(NULL, " ");
				if(param){
					int uid = atoi(param);
					param = strtok(NULL, " ");
					if(param){
						sprintf(buff_out, "[Message from][%s]", cli->name);
						while(param != NULL){
							strcat(buff_out, " ");
							strcat(buff_out, param);
							param = strtok(NULL, " ");
						}
						strcat(buff_out, "\r\n");
						send_message_client(buff_out, uid);
					}else{
						send_message_self("<<MESSAGE CANNOT BE NULL\r\n", cli->connfd);
					}
				}else{
					send_message_self("<<PORT CANNOT BE NULL\r\n", cli->connfd);
				}
			}
			else if(strcmp(command, "\\active")==0){
				sprintf(buff_out, "<<CLIENTS %d\r\n", cli_count); 
				send_message_self(buff_out, cli->connfd);
				send_active_clients(cli->connfd);
			}
			else if(strcmp(command, "\\public")==0){
				param = strtok(NULL, " ");
				if(param){
					strcat(buff_out, " ");
					strcat(buff_out, param);
					//param = strtok(NULL, " ");
					strcat(buff_out, "\r\n");
					send_message_all(buff_out);
				}
			}
			else if(strcmp(command, "\\help")==0){
				strcat(buff_out, "\\QUIT     Quit chatroom\r\n");
				strcat(buff_out, "\\PING     Server test\r\n");
				strcat(buff_out, "\\NAME     <name> Change nickname\r\n");
				strcat(buff_out, "\\PRIVATE  <reference> <message> Send private message\r\n");
				strcat(buff_out, "\\PUBLIC   <message> Send public message including myself\r\n");
				strcat(buff_out, "\\ACTIVE   Show active clients\r\n");
				strcat(buff_out, "\\HELP     Show help\r\n");
				send_message_self(buff_out, cli->connfd);
			}
			else{
				send_message_self("<<UNKOWN COMMAND\r\n", cli->connfd);
			}
		}
		else{
			/* Send message */
			sprintf(buff_out, "[%s] %s\r\n", cli->name, buff_in);
			send_message(buff_out, cli->uid);
		}
	}

	/* Close connection */
	close(cli->connfd);
	sprintf(buff_out, "<<GoodBYE~~ %s\r\n", cli->name); 
	send_message_all(buff_out);

	/* Delete client from queue and yeild thread */
	client_delete(cli->uid);
	printf("<<LEAVE ");
	print_client_addr(cli->addr);
	printf(" REFERENCED BY %d\n", cli->uid);
	free(cli);
	cli_count--;
	pthread_detach(pthread_self());
	
	return NULL;
}

int main(int argc, char *argv[]){
	int sockfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;

	/* Socket settings */
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //TCP
	serv_addr.sin_family = AF_INET; //IPv4
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //any interfaces
	serv_addr.sin_port = htons(PORT); //port, using host to network short

	/* Bind */
	if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
		perror("Socket binding failed");
		return 1;
	}

	/* Listen */
	if(listen(sockfd, 10) < 0){
		perror("Socket listening failed");
		return 1;
	}

	printf("<[SERVER STARTED]>\n");

	/* main accept clients loop*/
	while(1){
		socklen_t clisize = sizeof(cli_addr); //socklen_t an unsigned opaque integral type of length at least 32 bits
		connfd = accept(sockfd, (struct sockaddr* )&cli_addr, &clisize);

		/* Check if max clients is reached */
		if((cli_count+1) == MAX_CLIENTS){
			printf("<<MAX CLIENTS REACHED\n");
			printf("<<REJECT ");
			print_client_addr(cli_addr);
			printf("\n");
			close(connfd);
			continue;
		}

		/* Client settings */
		client_t *cli = (client_t *)malloc(sizeof(client_t));
		cli->addr = cli_addr;
		cli->connfd = connfd;
		cli->uid = uid++;
		sprintf(cli->name, "%d", cli->uid);

		/* Add client to the queue and fork thread */
		client_add(cli);
		pthread_create(&tid, NULL, &handle_client, (void*)cli);

		/* Reduce CPU usage */
		sleep(1);
	}
}