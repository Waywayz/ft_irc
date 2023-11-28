/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:48:54 by romain            #+#    #+#             */
/*   Updated: 2023/11/28 09:50:58 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <strings.h>
#include <vector>
#include <unistd.h>
#include <cstring>

/*

    Pour l'instant gros chantier le code mais ca fait bien un serveur auquel
    on peut se connecter via la commande :

            irssi -c localhost -p <port>

    La deconnexion est mal gere encore (segfault) mais le message s'affiche.
    Il doit manquer qquechose sur la reception de message.

*/

int main(int ac, char **av)
{

    if (ac != 3)
    {
        std::cerr << "./irc <port> <password>" << std::endl;
        return (1);
    }

    // On cree la socket du serveur
    struct sockaddr_in serv_addr;
    int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_socket == -1)
    {
        std::cerr << "Error while creating the socket" << std::endl;
        return (1);
    }
    // On initialise les valeur de la struc sockaddr_in (man socket)
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(av[1]));
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serv_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        std::cerr << "Error while binding the socket to the address." << std::endl;
        return (1);
    }

    if (listen(serv_socket, 100) == -1)
    {
        std::cerr << "Error while listening." << std::endl;
        return (1);
    }
    std::cout << "IRC server ON. Port : " << av[1] << std::endl;

    std::vector<int> clientSockets;
    fd_set readfds;
    // On recolte un socket de client a chaque nouvelle connexion,
    // et on surveille les fd que l'on doit lire (man select / man FD_SET)
    while (true)
    {

        FD_ZERO(&readfds);
        FD_SET(serv_socket, &readfds);
        int max_fd = serv_socket;

        for (std::vector<int>::iterator it = clientSockets.begin(); it != clientSockets.end();)
        {
            FD_SET(*it, &readfds);
            if (*it > max_fd)
                max_fd = *it;
            ++it;
        }

        if (select(max_fd + 1, &readfds, nullptr, nullptr, nullptr) == -1)
        {
            std::cerr << "Error using select." << std::endl;
            return (1);
        }

        // Si une connexion arrive : On stocke le socket du client
        if (FD_ISSET(serv_socket, &readfds))
        {
            int newCliSocket = accept(serv_socket, nullptr, nullptr);
            clientSockets.push_back(newCliSocket);
            std::cout << "New connection accepted." << std::endl;
        }

        for (std::vector<int>::iterator it = clientSockets.begin(); it != clientSockets.end();)
        {
            int clientSocket = *it;

            if (FD_ISSET(clientSocket, &readfds))
            {
                char buffer[1024];
                int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

                if (bytesRead <= 0)
                {
                    // Deconnexion du client
                    close(clientSocket);
                    it = clientSockets.erase(it);
                    std::cout << "Client has disconnected." << std::endl;
                }
                else
                {
                    // Reception des donnees du client
                    buffer[bytesRead] = '\0';
                    std::cout << "Message : " << buffer << std::endl;
                }
            }
            it++;
        }
    }
    return (0);
}