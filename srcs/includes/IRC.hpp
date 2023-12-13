#ifndef IRC_HPP
# define IRC_HPP

# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <iostream>
# include <strings.h>
# include <vector>
# include <unistd.h>
# include <cstring>

# include "Channel.hpp"
# include "Client.hpp"
# define nullptr 0

int setup_server(sockaddr_in *serv_addr, char *port);
int init_fd(fd_set *readfds, int serv_socket, std::vector<Client> &clients);

Channel *get_channel(const std::string &name);
Channel *create_channel(const std::string &name, const std::string &key, Client *client);

void join(Client *client, std::vector<std::string> args);



#endif