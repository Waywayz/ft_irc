/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:25:40 by romain            #+#    #+#             */
/*   Updated: 2023/12/21 15:35:23 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd, int port, const std::string &hostname)
    : _fd(fd), _port(port), _hostname(hostname), _state(HANDSHAKE), _channel(0) {}

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

std::vector<Channel *> Client::get_channel() const { return _channel; }

void Client::set_nickname(const std::string &nickname) { _nickname = nickname; }
void Client::set_username(const std::string &username) { _username = username; }
void Client::set_realname(const std::string &realname) { _realname = realname; }
void Client::set_state(ClientState state) { _state = state; }
// void Client::set_channel(Channel *channel) { _channel = channel; }

bool Client::is_registered() const { return _state == REGISTERED; }

void Client::write(const std::string &message) const
{
    std::string buffer = message + "\r\n";
    if (send(_fd, buffer.c_str(), buffer.length(), MSG_NOSIGNAL) < 0)
        throw std::runtime_error("Error while sending a message to a client!");
}

void Client::reply(const std::string &reply)
{
    this->write(":" + get_prefix() + " " + reply);
}

bool Client::has_invit(Channel *channel)
{
    channel_iterator it_b = _channel_invit.begin();
    channel_iterator it_e = _channel_invit.end();

    while (it_b != it_e)
    {
        if (*it_b == channel)
            return true;

        it_b++;
    }

    return false;
}

void Client::set_invit_channel(Channel *channel)
{
    _channel_invit.push_back(channel);
    this->write(":" + _nickname + " " + channel->get_name() + " :You have been invited to join " + channel->get_name());
}

void Client::welcome()
{
    if (_state != LOGIN || _username.empty() || _realname.empty() || _nickname.empty())
        return;

    _state = REGISTERED;
    this->reply(RPL_WELCOME(_nickname));

    char message[100];
    snprintf(message, sizeof(message), "%s:%d is now known as %s.", _hostname.c_str(), _port, _nickname.c_str());
    log(message);
}

void Client::join(Channel *channel)
{
    channel->add_client(this);
    _channel.push_back(channel);

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

    if (channel->get_topic() != "")
    {
        log(channel->get_topic());
    }

    std::string message = _nickname + " has joined to the channel " + channel->get_name();
    log(message);
}

void Client::leave(Channel *channel)
{
    const std::string name = channel->get_name();

    channel->broadcast(RPL_PART(get_prefix(), channel->get_name()));
    channel->remove_client(this);
    this->remove_channel(channel);

    std::string message = _nickname + " has left the channel " + name;
    log(message);
}

void Client::leave_all_channels()
{
    channel_iterator it_b = _channel.begin();
    channel_iterator it_e = _channel.end();

    while (it_b != it_e)
    {
        this->leave(*it_b);
        it_b++;
    }
}

void Client::remove_channel(Channel *channel)
{
    channel_iterator it_b = _channel.begin();
    channel_iterator it_e = _channel.end();

    while (it_b != it_e)
    {
        if (*it_b == channel)
            _channel.erase(it_b);

        it_b++;
    }
}