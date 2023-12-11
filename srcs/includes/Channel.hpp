/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 08:32:22 by romain            #+#    #+#             */
/*   Updated: 2023/12/11 13:24:20 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Channel;

#include "Server.hpp"
#include "Client.hpp"
#include "response.hpp"

class Channel
{

    typedef std::vector<Client *>::iterator client_iterator;

private:
    std::string _name;
    Client *_admin;
    std::vector<Client *> _clients;

    std::string _key;
    size_t _limit;
    bool _ext_msg;

    Channel();
    Channel(const Channel &src);

public:
    Channel(const std::string &name, const std::string &key, Client *admin);
    ~Channel();

    std::string get_name() const;
    Client *get_admin() const;

    std::string get_key() const;
    size_t get_limit() const;
    bool ext_msg() const;

    size_t get_size() const;
    std::vector<std::string> get_nicknames();

    void set_key(std::string key);
    void set_limit(size_t limit);
    void set_ext_msg(bool flag);

    void broadcast(const std::string &message);
    void broadcast(const std::string &message, Client *exclude);

    void add_client(Client *client);
    void remove_client(Client *client);

    void kick(Client *client, Client *target, const std::string &reason);
};

#endif