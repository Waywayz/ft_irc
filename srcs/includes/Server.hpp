/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:09:39 by romain            #+#    #+#             */
/*   Updated: 2023/12/11 13:24:43 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

class Server;

#include "Client.hpp"
#include "Channel.hpp"
#include "Parser.hpp"

class Server
{
    typedef std::vector<Channel *>::iterator channel_iterator;

private:
    Server();
    Server(const Server &src);

    struct sockaddr_in _servAddr;
    std::vector<int> _clientSockets;
    int _servSocket;
    int _sock;

    std::vector<Channel *> _channels;

public:
    Server(const std::string &port, const std::string &pass);
    ~Server();

    int setup(sockaddr_in *serv_addr, char *port);
    int init_fd(fd_set *readfds, int serv_socket, std::vector<int> &clientSockets);
    void receive_datas(fd_set *readfds, std::vector<int> &clientSockets);
    void start();
    Channel *get_channel(const std::string &name);
    Channel *create_channel(const std::string &name, const std::string &key, Client *client);
};

#endif
