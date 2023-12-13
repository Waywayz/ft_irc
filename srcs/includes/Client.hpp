/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:20:54 by romain            #+#    #+#             */
/*   Updated: 2023/12/11 13:13:45 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <sys/socket.h>
#include <sys/poll.h>
#include <string>
#include <vector>

class Client;

#include "Channel.hpp"
#include "response.hpp"

enum ClientState {

    HANDSHAKE,
    LOGIN,
    REGISTERED,
    DISCONNECTED
};

class Client {

    typedef std::vector<Channel *>::iterator channel_iterator;

    private:
        int _fd;
        int _port;

        std::string _nickname;
        std::string _username;
        std::string _realname;
        std::string _hostname;

        ClientState _state;
        std::vector<Channel *> _channel;



    public:
        Client(int fd, int port, const std::string &hostname);
        //Client(const Client &src);
        ~Client();

        int get_fd() const;
        int get_port() const;

        std::string get_nickname() const;
        std::string get_username() const;
        std::string get_realname() const;
        std::string get_hostname() const;
        std::string get_prefix() const;

        std::vector<Channel *>get_channel() const;

        void set_nickname(const std::string &nickname);
        void set_username(const std::string &username);
        void set_realname(const std::string &realname);
        void set_state(ClientState state);
        //void set_channel(Channel *channel);

        bool is_registered() const;

        void write(const std::string &message) const;
        void reply(const std::string &reply);

        void welcome();

        void join(Channel *channel);
        void leave();
};

#endif