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
#include <sstream>
#include <signal.h>

#include "Channel.hpp"
#include "Client.hpp"
#define nullptr 0

typedef std::vector<Channel *>::iterator channel_iterator;
typedef std::map<int, Client *>::iterator client_iterator;

// a potentiellement changer pour eviter des variables globales

extern std::vector<Channel *> channels;
extern std::map<int, Client *> clients;
extern std::string password;

int setup_server(sockaddr_in *serv_addr, char *port);
int init_fd(fd_set *readfds, int serv_socket, std::map<int, Client *> &clients);

Channel *get_channel(const std::string &name);
Client *get_client(const std::string &nickname);
Channel *create_channel(const std::string &name, const std::string &key);
void set_password(std::string pass);
std::string get_password();
void parse_n_exec(char *buffer, Client *client);
void on_client_disconnect(int fd);
void remove_channel_from_serv(Channel *channel);
void free_all();

void cap(Client *client, std::vector<std::string> args);
void join(Client *client, std::vector<std::string> args);
void kick(Client *client, std::vector<std::string> args);
void nick(Client *client, std::vector<std::string> args);
void pass(Client *client, std::vector<std::string> args);
void user(Client *client, std::vector<std::string> args);
void mode(Client *client, std::vector<std::string> args);
void privMsg(Client *client, std::vector<std::string> args);
void topic(Client *client, std::vector<std::string> args);
void part(Client *client, std::vector<std::string> args);
void quit(Client *client, std::vector<std::string> args);
void invite(Client *client, std::vector<std::string> args);
void ping(Client *client, std::vector<std::string> args);
void notice(Client *client, std::vector<std::string> args);

// void display_channel_list();

#endif