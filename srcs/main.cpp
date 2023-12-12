/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:06:52 by romain            #+#    #+#             */
/*   Updated: 2023/12/12 17:41:18 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

    Server server(argv[1], argv[2]);

        nc localhost <port>
        irssi -c localhost -p <port>

    La deconnexion est mal gere encore (segfault) mais le message s'affiche.
    Il doit manquer qquechose sur la reception de message.

        A faire:

    Changer la liste de clientsSocket par une liste de clients




    PASS
    USER
    NICK

    JOIN
    INVITE
    PRIVMSG
    MODE
    TOPIC

*/

#include "IRC.hpp"

void    receive_datas(fd_set *readfds, std::vector<int> &clientSockets) {

    for (std::vector<int>::iterator it = clientSockets.begin(); it != clientSockets.end();) {

        int clientSocket = *it;
        if (FD_ISSET(clientSocket, readfds)) {

            char    buffer[1024];
            int     bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

            if (bytesRead <= 0) { // Deconnexion du client
                close(clientSocket);
                it = clientSockets.erase(it);
                std::cout << "Client has disconnected." << std::endl;
                continue ;
            }
            else {
                // Reception des donnees envoyes par le client
                buffer[bytesRead] = '\0';
                std::cout << "Donnees : <" << buffer <<">" << std::endl;
                //  Ici on va envoyer a la fonction parsing
                //  ft_parse(buffer, vectorClient, vectorChannels)
                //      qui va se charger de tout traiter

                //      On gere les cmds dans cet ordre :
                //          Client a ses infos full (PASS / NAME / NICK)
                //              => on exe commande
                //          sinon
                //             => exec que PASS NAME NICK
                //
                //  fonctions utiles : 
                //      sendRPL (send(client_fd, str, strlen))
                //      registerClient si infos completes qui envoie tous les RPL
                //      execCmd qui parse et switch pour lancer la commande necessaire
                //      parseMsg pour check erreurs et decouper la str si plusieurs lignes
                //
                //
                //
                // ICI CHECK PARSE CMD

                }
            }
        it++;
    }
}

// OLD VERSION

// #include <sys/socket.h>
// #include <sys/types.h>
// #include <arpa/inet.h>
// #include <iostream>
// #include <strings.h>
// #include <vector>
// #include <unistd.h>
// #include <cstring>

// /*

//     Pour se connecter au serveur :

//         nc localhost <port>
//         irssi -c localhost -p <port>

//     La deconnexion est mal gere encore (segfault) mais le message s'affiche.
//     Il doit manquer qquechose sur la reception de message.

//         A faire:
//     PASS
//     USER
//     NICK

//     JOIN
//     INVITE
//     PRIVMSG
//     MODE
//     TOPIC

// */

// int setup_server(sockaddr_in *serv_addr, char *port) {

//     // On cree la socket du serveur
//     int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
//     if (serv_socket == -1) {
//         std::cerr << "Error while creating the socket" << std::endl;
//         return (1);
//     }

//     // On initialise les valeur de la struc sockaddr_in (man socket)
//     bzero(serv_addr, sizeof(*serv_addr));
//     serv_addr->sin_family = AF_INET;
//     serv_addr->sin_port = htons(atoi(port));
//     serv_addr->sin_addr.s_addr = INADDR_ANY;

//     if (bind(serv_socket, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) == -1) {
//         std::cerr << "Error while binding the socket to the address." << std::endl;
//         return (1);
//     }

//     if (listen(serv_socket, 100) == -1) {
//         std::cerr << "Error while listening." << std::endl;
//         return (1);
//     }
//     return (serv_socket);
// }

// int init_fd(fd_set *readfds, int serv_socket, std::vector<int> &clientSockets) {

//     int max_fd = serv_socket;

//     FD_ZERO(readfds);
//     FD_SET(serv_socket, readfds);
//     for (std::vector<int>::iterator it = clientSockets.begin(); it != clientSockets.end();) {
//         FD_SET(*it, readfds);
//         if (*it > max_fd)
//             max_fd = *it;
//         ++it;
//     }
//     return (max_fd);
// }

// void    receive_datas(fd_set *readfds, std::vector<int> &clientSockets) {

//     for (std::vector<int>::iterator it = clientSockets.begin(); it != clientSockets.end();) {

//         int clientSocket = *it;
//         if (FD_ISSET(clientSocket, readfds)) {

//             char    buffer[1024];
//             int     bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

//             if (bytesRead <= 0) { // Deconnexion du client
//                 close(clientSocket);
//                 it = clientSockets.erase(it);
//                 std::cout << "Client has disconnected." << std::endl;
//                 continue ;
//             }
//             else {
//                 // Reception des donnees envoyes par le client
//                 buffer[bytesRead] = '\0';
//                 std::cout << "Donnees : <" << buffer <<">" << std::endl;

//                 // ICI CHECK PARSE CMD

//                 }
//             }
//         it++;
//     }
// }

// int main(int ac, char **av) {

//     struct sockaddr_in  serv_addr;
//     std::vector<int>    clientSockets;
//     fd_set              readfds;

//     if (ac != 3) {
//         std::cerr << "./irc <port> <password>" << std::endl;
//         return (1);
//     }

//     int serv_socket = setup_server(&serv_addr, av[1]);
//     if (serv_socket == 1)
//         return (1);
//     std::cout << "IRC server ON. Port : " << av[1] << std::endl;

//     // On recolte un socket de client a chaque nouvelle connexion,
//     // et on surveille les fd que l'on doit lire (man select / man FD_SET)
//     while (true) {

//         int max_fd = init_fd(&readfds, serv_socket, clientSockets);
//         if (select(max_fd + 1, &readfds, nullptr, nullptr, nullptr) == -1) {
//             std::cerr << "Error using select." << std::endl;
//             return (1);
//         }

//         // Si une connexion arrive : On stocke le socket du client
//         if (FD_ISSET(serv_socket, &readfds)) {
//             int newCliSocket = accept(serv_socket, nullptr, nullptr);
//             clientSockets.push_back(newCliSocket);//
//             std::cout << "New connection accepted." << std::endl;
//         }
//         receive_datas(&readfds, clientSockets);//On traite ici les donnees lues sur les fds des clients
//     }
//     return (0);
// }