
#include "IRC.hpp"

int setup_server(sockaddr_in *serv_addr, char *port) {

    // On cree la socket du serveur
    int serv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_socket == -1) {
        std::cerr << "Error while creating the socket" << std::endl;
        return (1);
    }

    // On initialise les valeur de la struc sockaddr_in (man socket)
    bzero(serv_addr, sizeof(*serv_addr));
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_port = htons(atoi(port));
    serv_addr->sin_addr.s_addr = INADDR_ANY;

    if (bind(serv_socket, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) == -1) {
        std::cerr << "Error while binding the socket to the address." << std::endl;
        return (1);
    }

    if (listen(serv_socket, 100) == -1) {
        std::cerr << "Error while listening." << std::endl;
        return (1);
    }
    return (serv_socket);
}

int init_fd(fd_set *readfds, int serv_socket, std::vector<Client> &clients) {
    
    int max_fd = serv_socket;

    FD_ZERO(readfds);
    FD_SET(serv_socket, readfds);
    for (std::vector<Client>::iterator it = clients.begin(); it != clients.end();) {
        FD_SET(it->get_fd(), readfds);
        if (it->get_fd() > max_fd)
            max_fd = it->get_fd();
        ++it;
    }
    return (max_fd);
}

/*
Channel *get_channel(const std::string &name)
{
    channel_iterator it_b = channel.begin();
    channel_iterator it_e = channel.begin();

    while (it_b != it_e)
    {
        if (!name.compare((*it_b)->get_name()))
            return (*it_b);

        it_b++;
    }

    return NULL;
}
*/

Channel *create_channel(const std::string &name, const std::string &key, Client *client, std::vector<Channel *> channel)
{
    Channel *chan = new Channel(name, key, client);
    if (!chan)
        return (NULL);
    channel.push_back(chan);

    return (chan);
}