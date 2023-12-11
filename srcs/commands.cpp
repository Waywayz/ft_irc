/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:37:34 by romain            #+#    #+#             */
/*   Updated: 2023/12/11 13:22:44 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

void join(Client *client, std::vector<std::string> args) {

    if (args.empty()) {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "JOIN"));
        return;
    }
/*
    std::string name = args[0];
    std::string pass = args.size() > 1 ? args[1] : "";

Recuperer le vector channel via les arguments et get dessus pour
recuperer le channel si il existe ou non. 
    ||
    \/
    Channel *channel = get_channel(name);

    if (!channel) {
        channel = create_channel(name, pass, client);
    }
    if (channel->get_limit() > 0 && channel->get_size() >= channel->get_limit()) {
        client->reply(ERR_CHANNELISFULL(client->get_nickname(), name));
        return;
    }
    if (channel->get_key() != pass) {
        client->reply(ERR_BADCHANNELKEY(client->get_nickname(), name));
        return;
    }
    client->join(channel);
*/
}