#ifndef IRC_HPP
#define IRC_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <map>

#include "Channel.hpp"
#include "Client.hpp"
#define nullptr 0

typedef std::vector<Channel *>::iterator channel_iterator;
typedef std::map<int, Client *>::iterator client_iterator;

std::vector<Channel *> channels;
std::map<int, Client *> clients;

int setup_server(sockaddr_in *serv_addr, char *port);
int init_fd(fd_set *readfds, int serv_socket, std::map<int, Client *> &clients);
// int init_fd(fd_set *readfds, int serv_socket, std::vector<Client> &clients);

Channel *get_channel(const std::string &name);
Client *get_client(const std::string &nickname);
Channel *create_channel(const std::string &name, const std::string &key, Client *client);

void join(Client *client, std::vector<std::string> args);
void kick(Client *client, std::vector<std::string> args);
void mode(Client *client, std::vector<std::string> args);

#endif