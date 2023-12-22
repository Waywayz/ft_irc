
#include "IRC.hpp"

void receive_datas(fd_set *readfds, std::map<int, Client *> &clients)
{
    for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end();)
    {
        int client_fd = it->first;// obtenir la clé (client_fd) à partir de la map
        if (FD_ISSET(client_fd, readfds))
        {
            char buffer[1024];
            int bytesRead = recv(client_fd, buffer, sizeof(buffer), 0);

            if (bytesRead <= 0)
            {
                // Deconnexion du client
                close(client_fd);
                clients.erase(it);
                it = clients.begin();
                std::cout << "Client has disconnected." << std::endl;
                continue;
            }
            else
            {
                // Reception des donnees envoyes par le client
                buffer[bytesRead] = '\0';
                std::cout << "Donnees : <" << buffer << ">" << std::endl;
                parse_n_exec(buffer, it->second);
            }
        }
        ++it;
    }
}

// std::vector<Channel *> channels;
// std::map<int, Client *> clients;
// std::string password;

int main(int ac, char **av)
{
    struct sockaddr_in serv_addr;
    fd_set readfds;

    if (ac != 3)
    {
        std::cerr << "./irc <port> <password>" << std::endl;
        return (1);
    }
    set_password(av[2]);

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
            clients.insert(std::make_pair(newCliSocket, new Client(newCliSocket, atoi(av[1]), "")));
            std::cout << "New connection accepted." << std::endl;
        }
        receive_datas(&readfds, clients);
    }
    return (0);
}