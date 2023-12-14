/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:32:22 by romain            #+#    #+#             */
/*   Updated: 2023/12/14 01:28:46 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Channel;

#include "Client.hpp"
#include "response.hpp"

class Channel
{

    typedef std::vector<Client *>::iterator client_iterator;

private:
    std::string _name;
    std::string _topic;
    Client *_admin;
    std::vector<Client *> _clients;
    std::vector<Client *> _operators;

    std::string _key;
    size_t _limit;
    bool _invit_only;

    Channel();
    Channel(const Channel &src);

public:
    Channel(const std::string &name, const std::string &key, Client *admin);
    ~Channel();

    std::string get_name() const;
    Client *get_admin() const;
    bool is_operator(Client *client);
    bool has_member(Client *client);

    std::string get_key() const;
    size_t get_limit() const;
    bool invit_only() const;

    size_t get_size() const;
    std::vector<std::string> get_nicknames();
    std::string get_topic() const;

    void set_key(std::string key);
    void set_limit(size_t limit);
    void set_invit_only(bool flag);
    void set_topic(const std::string &topic, Client *client);

    void broadcast(const std::string &message);
    void broadcast(const std::string &message, Client *exclude);

    void add_client(Client *client);
    void add_operator(Client *client);
    void remove_client(Client *client);
    void remove_operator(Client *client);

    void kick(Client *client, Client *target, const std::string &reason);
};

#endif