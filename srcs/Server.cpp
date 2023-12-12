/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 13:08:30 by romain            #+#    #+#             */
/*   Updated: 2023/12/11 13:24:53 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::setup(sockaddr_in *serv_addr, char *port)
{

    // On cree la socket du serveur
    int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_socket == -1)
    {
        std::cerr << "Error while creating the socket" << std::endl;
        return (1);
    }

    // On initialise les valeur de la struc sockaddr_in (man socket)
    bzero(serv_addr, sizeof(*serv_addr));
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(atoi(port));
    serv_addr->sin_addr.s_addr = INADDR_ANY;

    if (bind(serv_socket, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) == -1)
    {
        std::cerr << "Error while binding the socket to the address." << std::endl;
        return (1);
    }

    if (listen(serv_socket, 100) == -1)
    {
        std::cerr << "Error while listening." << std::endl;
        return (1);
    }
    return (serv_socket);
}

int Server::init_fd(fd_set *readfds, int serv_socket, std::vector<int> &clientSockets)
{

    int max_fd = serv_socket;

    FD_ZERO(readfds);
    FD_SET(serv_socket, readfds);
    for (std::vector<int>::iterator it = clientSockets.begin(); it != clientSockets.end();)
    {
        FD_SET(*it, readfds);
        if (*it > max_fd)
            max_fd = *it;
        ++it;
    }
    return (max_fd);
}

void Server::receive_datas(fd_set *readfds, std::vector<int> &clientSockets)
{

    for (std::vector<int>::iterator it = clientSockets.begin(); it != clientSockets.end();)
    {

        int clientSocket = *it;
        if (FD_ISSET(clientSocket, readfds))
        {

            char buffer[1024];
            int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

            if (bytesRead <= 0)
            { // Deconnexion du client
                close(clientSocket);
                it = clientSockets.erase(it);
                std::cout << "Client has disconnected." << std::endl;
                continue;
            }
            else
            {
                // Reception des donnees envoyes par le client
                buffer[bytesRead] = '\0';
                std::cout << "Donnees : <" << buffer << ">" << std::endl;

                // ICI CHECK PARSE CMD
            }
        }
        it++;
    }
}

void Server::start()
{
    int serv_socket = setup(&serv_addr, av[1]);
    if (serv_socket == 1)
        return (1);
    std::cout << "IRC server ON. Port : " << av[1] << std::endl;

    // On recolte un socket de client a chaque nouvelle connexion,
    // et on surveille les fd que l'on doit lire (man select / man FD_SET)
    while (true)
    {

        int max_fd = init_fd(&readfds, serv_socket, clientSockets);
        if (select(max_fd + 1, &readfds, nullptr, nullptr, nullptr) == -1)
        {
            std::cerr << "Error using select." << std::endl;
            return (1);
        }

        // Si une connexion arrive : On stocke le socket du client
        if (FD_ISSET(serv_socket, &readfds))
        {
            int newCliSocket = accept(serv_socket, nullptr, nullptr);
            clientSockets.push_back(newCliSocket); //
            std::cout << "New connection accepted." << std::endl;
        }
        receive_datas(&readfds, clientSockets); // On traite ici les donnees lues sur les fds des clients
    }
}

Channel *Server::get_channel(const std::string &name)
{
    channel_iterator it_b = _channels.begin();
    channel_iterator it_e = _channels.begin();

    while (it_b != it_e)
    {
        if (!name.compare((*it_b)->get_name()))
            return (*it_b);

        it_b++;
    }

    return NULL;
}

Channel *Server::create_channel(const std::string &name, const std::string &key, Client *client)
{
    Channel *channel = new Channel(name, key, client);
    _channels.push_back(channel);

    return channel;
}