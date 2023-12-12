/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:25:40 by romain            #+#    #+#             */
/*   Updated: 2023/12/06 18:20:56 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd, int port, const std::string &hostname)
<<<<<<< HEAD:srcs/Client.cpp
    : _fd(fd), _port(port), _hostname(hostname), _state(HANDSHAKE), _channel(0) {}
=======
    : _fd(fd), _port(port), _hostname(hostname), _state(HANDSHAKE), _channel(NULL)
{
}
>>>>>>> main:srcs/server/Client.cpp

Client::~Client() {}

int Client::get_fd() const { return _fd; }
int Client::get_port() const { return _port; }

std::string Client::get_nickname() const { return _nickname; }
std::string Client::get_username() const { return _username; }
std::string Client::get_realname() const { return _realname; }
std::string Client::get_hostname() const { return _hostname; }

std::string Client::get_prefix() const
{
    std::string username = _username.empty() ? "" : "!" + _username;
    std::string hostname = _hostname.empty() ? "" : "@" + _hostname;

    return _nickname + username + hostname;
}

<<<<<<< HEAD:srcs/Client.cpp
std::vector<Channel *>Client::get_channel() const { return _channel; }
=======
Channel *Client::get_channel() const { return _channel; }
>>>>>>> main:srcs/server/Client.cpp

void Client::set_nickname(const std::string &nickname) { _nickname = nickname; }
void Client::set_username(const std::string &username) { _username = username; }
void Client::set_realname(const std::string &realname) { _realname = realname; }
void Client::set_state(ClientState state) { _state = state; }
<<<<<<< HEAD:srcs/Client.cpp
//void Client::set_channel(Channel *channel) { _channel = channel; }
=======
void Client::set_channel(Channel *channel) { _channel = channel; }
>>>>>>> main:srcs/server/Client.cpp

bool Client::is_registered() const { return _state == REGISTERED; }

void Client::write(const std::string &message) const
{
    std::string buffer = message + "\r\n";
    if (send(_fd, buffer.c_str(), buffer.length(), 0) < 0)
        throw std::runtime_error("Error while sending a message to a client!");
}

void Client::reply(const std::string &reply)
{
    this->write(":" + get_prefix() + " " + reply);
}

void Client::welcome()
{
    if (_state != LOGIN || _username.empty() || _realname.empty() || _nickname.empty())
        return;

    _state = REGISTERED;
    this->reply(RPL_WELCOME(_nickname));

    char message[100];
    sprintf(message, "%s:%d is now known as %s.", _hostname.c_str(), _port, _nickname.c_str());
    log(message);
}

void Client::join(Channel *channel)
{
    channel->add_client(this);
<<<<<<< HEAD:srcs/Client.cpp
    _channel.push_back(channel);
=======
    _channel = channel;
>>>>>>> main:srcs/server/Client.cpp

    std::string users = "";
    std::vector<std::string> nicknames = channel->get_nicknames();
    std::vector<std::string>::iterator it_b = nicknames.begin();
    std::vector<std::string>::iterator it_e = nicknames.end();
    while (it_b != it_e)
    {
        users.append(*it_b + " ");
        it_b++;
    }

    reply(RPL_NAMREPLY(_nickname, channel->get_name(), users));
    reply(RPL_ENDOFNAMES(_nickname, channel->get_name()));
    channel->broadcast(RPL_JOIN(get_prefix(), channel->get_name()));

    std::string message = _nickname + " has joined to the channel " + channel->get_name();
    log(message);
}

<<<<<<< HEAD:srcs/Client.cpp
/*
    Cette fonction n'est pas a faire je crois,
    et si jamais on doit la retouchee ca sera en iterant
    sur toute le vector _channel

void Client::leave() {

    if (!_channel)
        return;

    channel_iterator    it_b = _channel->begin();
    channel_iterator    it_e = _channel->end();

    while ()
=======
void Client::leave()
{
    if (!_channel)
        return;

>>>>>>> main:srcs/server/Client.cpp
    const std::string name = _channel->get_name();

    _channel->broadcast(RPL_PART(get_prefix(), _channel->get_name()));
    _channel->remove_client(this);

    std::string message = _nickname + " has left the channel " + name;
    log(message);
<<<<<<< HEAD:srcs/Client.cpp
}*/
=======
}
>>>>>>> main:srcs/server/Client.cpp