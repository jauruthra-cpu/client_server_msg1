#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define BUFFER_SIZE 512
void error(const char *msg)
{
perror(msg);
exit(1);
}
int main(int argc,char *argv[])
{

if (argc<2)
{
    fprintf(stderr,"The port number is not provided, program terminated!\n");
    exit(1);
}
int sockfd, newsockfd, port_no,n;
char buffer[BUFFER_SIZE];
struct sockaddr_in cli_addr, serv_addr;
socklen_t cli_len;
sockfd=socket(AF_INET,SOCK_STREAM,0);
if (sockfd<0)
{
    printf("error in opening socket");
}
bzero((char*) &serv_addr,sizeof(serv_addr));
port_no=atoi(argv[1]);
serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=INADDR_ANY;
serv_addr.sin_port=htons(port_no);

if(bind(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
error("Binding Failed!");

listen(sockfd,5);
cli_len=sizeof(cli_addr);

newsockfd = accept(sockfd, (struct sockaddr *)& cli_addr,&cli_len);
if(newsockfd<0)
{
    error("Error on Accept");
}
while(1)
{
    bzero(buffer,256);
    n=read(newsockfd, buffer,255);
    if(n<0)
    error("error on reading");
    printf("client : %s\n", buffer);
    bzero(buffer, 255);
    fgets(buffer,255,stdin);

    n=write(newsockfd,buffer, strlen(buffer));
    if(n<0)
    error("error on writting");

    int i= strncmp("bye",buffer,3);
    if(i==0)
    break;
}
close(newsockfd);
close(sockfd);
    return 0;
}
