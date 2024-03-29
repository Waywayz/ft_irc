/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:32:19 by romain            #+#    #+#             */
/*   Updated: 2023/12/21 03:07:50 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const std::string &name, const std::string &key)
    : _name(name), _topic(""), _key(key), _limit(0), _invit_only(false), _op_topic(true) {}

Channel::~Channel() {}

std::string Channel::get_name() const { return _name; }

std::string Channel::get_key() const { return _key; }
size_t Channel::get_limit() const { return _limit; }
bool Channel::invit_only() const { return _invit_only; }
bool Channel::op_topic() const { return _op_topic; }

size_t Channel::get_size() const { return _clients.size(); }

void Channel::set_key(std::string key) { _key = key; }
void Channel::set_limit(size_t limit) { _limit = limit; }
void Channel::set_invit_only(bool flag) { _invit_only = flag; }
void Channel::set_topic_op(bool flag) { _op_topic = flag; }

std::vector<std::string> Channel::get_nicknames()
{
    std::vector<std::string> nicknames;

    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        Client *client = *it_b;

        std::string nick = (this->is_operator(client) ? "@" : "") + client->get_nickname();
        nicknames.push_back(nick);

        it_b++;
    }

    return nicknames;
}

void Channel::broadcast(const std::string &message)
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        (*it_b)->write(message);
        it_b++;
    }
}

void Channel::broadcast(const std::string &message, Client *exclude)
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        if (*it_b == exclude)
        {
            it_b++;
            continue;
        }

        (*it_b)->write(message);
        it_b++;
    }
}

void Channel::add_client(Client *client)
{
    _clients.push_back(client);
}


void Channel::set_operator(bool active, Client *client)
{
    if (active)
    {
        if (!is_operator(client))
        {
            _operators.push_back(client);
            return;
        }
        return;
    }

    else
    {
        client_iterator it_b = _operators.begin();
        client_iterator it_e = _operators.end();

        while (it_b != it_e)
        {
            if (*it_b == client)
            {
                _operators.erase(it_b);
                break;
            }

            it_b++;
        }
    }
}

bool Channel::is_operator(Client *client)
{
    client_iterator it_b = _operators.begin();
    client_iterator it_e = _operators.end();

    while (it_b != it_e)
    {
        if (*it_b == client)
            return (true);

        it_b++;
    }

    return (false);
}

bool Channel::has_member(Client *client)
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        if (*it_b == client)
            return (true);

        it_b++;
    }

    return (false);
}

void Channel::set_topic(const std::string &topic, Client *client)
{
    _topic = topic;

    // Broadcast le changement de topic à tous les membres du canal
    this->broadcast(RPL_TOPIC(client->get_prefix(), _name, _topic));
}

std::string Channel::get_topic() const
{
    return _topic;
}

void Channel::remove_client(Client *client)
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        if (*it_b == client)
            _clients.erase(it_b);

        it_b++;
    }
}

void Channel::kick(Client *client, Client *target, const std::string &reason)
{
    this->broadcast(RPL_KICK(client->get_prefix(), _name, target->get_nickname(), reason));
    this->remove_client(target);
    client->remove_channel(this);

    std::string message = client->get_nickname() + " kicked " + target->get_nickname() + " from channel " + _name;
    log(message);
}