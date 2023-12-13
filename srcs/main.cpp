
#include "IRC.hpp"

/*
        nc localhost <port>
        irssi -c localhost -p <port>

A faire:
    INVITE
    PRIVMSG
    MODE
    TOPIC
*/

// version with map
void receive_datas(fd_set *readfds, std::map<int, Client *> &clients)
{
    for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end();)
    {
        int client_fd = it->first; // obtenir la clé (client_fd) à partir de la map

        if (FD_ISSET(client_fd, readfds))
        {
            char buffer[1024];
            int bytesRead = recv(client_fd, buffer, sizeof(buffer), 0);

            if (bytesRead <= 0)
            {
                // Deconnexion du client
                close(client_fd);
                it = clients.erase(it);
                std::cout << "Client has disconnected." << std::endl;
                continue;
            }
            else
            {
                // Reception des donnees envoyes par le client
                buffer[bytesRead] = '\0';
                std::cout << "Donnees : <" << buffer << ">" << std::endl;

                // ICI on va envoyer à la fonction parsing
                // ft_parse(buffer, vectorClient, vectorChannels)
                // qui va se charger de tout traiter

                // On gere les cmds dans cet ordre :
                // Client a ses infos full (PASS / NAME / NICK)
                // => on exe commande
                // sinon
                // => exec que PASS NAME NICK
                //
                // fonctions utiles :
                // sendRPL (send(client_fd, str, strlen))
                // registerClient si infos completes qui envoie tous les RPL
                // execCmd qui parse et switch pour lancer la commande necessaire
                // parseMsg pour check erreurs et decouper la str si plusieurs lignes
                //
                // ICI CHECK PARSE CMD
            }
        }
        ++it;
    }
}

// void receive_datas(fd_set *readfds, std::map<int, Client> &clients)
// {

//     for (std::vector<Client>::iterator it = clients.begin(); it != clients.end();)
//     {

//         // int client = it;
//         if (FD_ISSET(it->get_fd(), readfds))
//         {

//             char buffer[1024];
//             int bytesRead = recv(it->get_fd(), buffer, sizeof(buffer), 0);

//             if (bytesRead <= 0)
//             { // Deconnexion du client
//                 close(it->get_fd());
//                 it = clients.erase(it);
//                 std::cout << "Client has disconnected." << std::endl;
//                 continue;
//             }
//             else
//             {
//                 // Reception des donnees envoyes par le client
//                 buffer[bytesRead] = '\0';
//                 std::cout << "Donnees : <" << buffer << ">" << std::endl;

//                 //  Ici on va envoyer a la fonction parsing
//                 //  ft_parse(buffer, vectorClient, vectorChannels)
//                 //      qui va se charger de tout traiter

//                 //      On gere les cmds dans cet ordre :
//                 //          Client a ses infos full (PASS / NAME / NICK)
//                 //              => on exe commande
//                 //          sinon
//                 //             => exec que PASS NAME NICK
//                 //
//                 //  fonctions utiles :
//                 //      sendRPL (send(client_fd, str, strlen))
//                 //      registerClient si infos completes qui envoie tous les RPL
//                 //      execCmd qui parse et switch pour lancer la commande necessaire
//                 //      parseMsg pour check erreurs et decouper la str si plusieurs lignes
//                 //
//                 // ICI CHECK PARSE CMD
//             }
//         }
//         it++;
//     }
// }

// A CHANGER
// declaration obligatoire pour eviter erreur de compilation

std::vector<Channel *> channels;
std::map<int, Client *> clients;

int main(int ac, char **av)
{

    struct sockaddr_in serv_addr;
    // std::vector<Client>     clients;
    // std::vector<Channel>    channels;
    fd_set readfds;

    if (ac != 3)
    {
        std::cerr << "./irc <port> <password>" << std::endl;
        return (1);
    }

    int serv_socket = setup_server(&serv_addr, av[1]);
    if (serv_socket == 1)
        return (1);
    std::cout << "IRC server ON. Port : " << av[1] << std::endl;

    while (true)
    {

        int max_fd = init_fd(&readfds, serv_socket, clients);
        if (select(max_fd + 1, &readfds, nullptr, nullptr, nullptr) == -1)
        {
            std::cerr << "Error using select." << std::endl;
            return (1);
        }
        if (FD_ISSET(serv_socket, &readfds))
        {
            int newCliSocket = accept(serv_socket, nullptr, nullptr);
            // Client newCli(newCliSocket, atoi(av[1]), "");
            clients.insert(std::make_pair(newCliSocket, new Client(newCliSocket, atoi(av[1]), "")));
            ;
            // clients.push_back(newCli);
            std::cout << "New connection accepted." << std::endl;
        }
        receive_datas(&readfds, clients); // On traite ici les donnees lues sur les fds des clients
    }
    return (0);
}