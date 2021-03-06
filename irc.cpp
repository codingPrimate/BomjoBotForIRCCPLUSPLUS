#include "irc.hpp"
#include <stdlib.h>
#include <stdio.h>
#include "util.hpp"
IrcProtocol::IrcProtocol(){};



void IrcProtocol::PingPong(int socket,const char*buffer)
{
applog(INFO,"Ping-Pong");
long Ping = FindWhere(buffer,"PING");
if(Ping == -1) Ping = FindWhere(buffer,"nospoof");

if(Ping == -1)
{
size_t sizeString = _strlen(buffer);
char * nameServer = (char*)malloc(sizeof(char)*sizeString);
size_t i;
for(i = 0;i!=sizeString && *buffer !=' ' && *buffer;i++)
   nameServer[i] = *buffer++;
nameServer[i++]='\0';
IrcProtocol::NameHost = _copy_string(nameServer);
free(nameServer);
}else{
buffer+=Ping;
while(*buffer && *buffer != ':')
  *buffer++;
if(*buffer == ':')
 {
  *buffer++;
  size_t sizeString = _strlen(buffer);
  char * ping = (char*)malloc(sizeof(char)*sizeString);
  char * nameServer = (char*)malloc(sizeof(char)*sizeString);
  size_t i;
  for(i = 0;i!=sizeString && *buffer !='\n' && *buffer;i++)
   ping[i] = *buffer++;
  ping[i++]='\0';
  *buffer++;
  for(i = 0;i!=sizeString && *buffer !=' ';i++)
   nameServer[i] = *buffer++;
  nameServer[i++]='\0';
  IrcProtocol::NameHost = _copy_string(nameServer);
  free(nameServer);
  i=0;
  char tmp[SIZEBUFFER];  
  sprintf(tmp,"PONG %s",ping);
  free(ping);
  applog(DEBUG,"Write to server: %s\n",tmp);
  writeTo(socket,tmp);
 }
}

}

void IrcProtocol::setNameHost(const char*name)
{
IrcProtocol::NameHost=_copy_string(name);
}

bool IrcProtocol::connect(int socket,constchr name,constchr UserName,constchr RealName)
{
applog(DEBUG,"IrcProtcocol::connect");
char * buffer = (char*)malloc(sizeof(char)*SIZEBUFFER);
sprintf(buffer,"NICK %s",name);
WRITETOSOCKET(socket,buffer);
READFROMSOCKET(socket,buffer);
do{
IrcProtocol::PingPong(socket,buffer);
sprintf(buffer,"USER %s 8 * : %s",UserName,RealName);
WRITETOSOCKET(socket,buffer);
READFROMSOCKET(socket,buffer);
}while( FindWhere(buffer,"PING") != -1 ||  FindWhere(buffer,"nospoof") != -1);
free(buffer);

}

bool IrcProtocol::JoinToChannel(int socket,const char * channel)
{
char * buffer = (char*)malloc(sizeof(char)*SIZEBUFFER);
sprintf(buffer,"JOIN #%s",channel);
WRITETOSOCKET(socket,buffer);
}
