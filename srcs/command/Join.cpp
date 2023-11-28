/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:37:34 by romain            #+#    #+#             */
/*   Updated: 2023/11/28 08:16:23 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Join::Join(Server* srv) : Command(srv) {}

Join::~Join() {}

void    Join::execute(Client* client, std::vector<std::string> args) {
    if (args.empty()) {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "JOIN"));
        return;
    }

    std::string name = args[0];
    std::string pass = args.size() > 1 ? args[1] : "";

    Channel *channel = client->get_channel();

    if (channel) {
        client->reply(ERR_TOOMANYCHANNELS(client->get_nickname(), name));
        return;
    }

    channel = _srv->get_channel(name);

    if (!channel) {
        channel = _srv->create_channel(name, pass, client);
    }

    if (channel->get_limit() > 0 && channel->get_size() => channel->get_limit()) {
        client->reply(ERR_CHANNELISFULL(client->get_nickname(), name));
        return;
    }

    if (channel->get_key() != pass) {
        client->reply(ERR_BADCHANNELKEY(client->get_nickname(), name));
        return;
    }

    client->join(channel);
}