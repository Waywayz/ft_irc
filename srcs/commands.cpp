/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:37:34 by romain            #+#    #+#             */
/*   Updated: 2023/12/15 03:45:02 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

void join(Client *client, std::vector<std::string> args)
{

    if (args.empty())
    {
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

void kick(Client *client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "KICK"));
        return;
    }

    // extract needed info
    std::string name = args[0];
    std::string target = args[1];
    std::string reason = "No reason specified!";

    // if there is a reason
    if (args.size() >= 3 && (args[2][0] != ':' || args[2].size() > 1))
    {
        reason = "";

        std::vector<std::string>::iterator it = args.begin();
        std::vector<std::string>::iterator end = args.end();

        while (it != end)
        {
            reason.append(*it + " ");
            it++;
        }
    }

    Channel *channel = get_channel(name);
    if (!channel || channel->get_name() != name)
    {
        client->reply(ERR_NOTONCHANNEL(client->get_nickname(), name));
        return;
    }

    if (channel->get_admin() != client)
    {
        client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), name));
        return;
    }

    Client *dest = get_client(target);
    if (!dest)
    {
        client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
        return;
    }

    if (!channel->has_member(dest))
    {
        client->reply(ERR_USERNOTINCHANNEL(client->get_nickname(), dest->get_nickname(), name));
        return;
    }

    // if everything is fine
    channel->kick(client, dest, reason);
}

void pass(Client *client, std::vector<std::string> args)
{
    if (args.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "PASS"));
        return;
    }

    if (client->is_registered())
    {
        client->reply(ERR_ALREADYREGISTERED(client->get_nickname()));
        return;
    }

    if (get_password() != args[0].substr(args[0][0] == ':' ? 1 : 0))
    {
        client->reply(ERR_PASSWDMISMATCH(client->get_nickname()));
        return;
    }

    client->set_state(LOGIN);
}

void user(Client *client, std::vector<std::string> args)
{
    if (client->is_registered())
    {
        client->reply(ERR_ALREADYREGISTERED(client->get_nickname()));
        return;
    }

    if (args.size() < 4)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "USER"));
        return;
    }

    client->set_username(args[0]);
    client->set_realname(args[3]);
    client->welcome();
}

void nick(Client *client, std::vector<std::string> args)
{
    if (args.empty() || args[0].empty())
    {
        client->reply(ERR_NONICKNAMEGIVEN(client->get_nickname()));
        return;
    }

    std::string nickname = args[0];

    if (get_client(nickname))
    {
        client->reply(ERR_NICKNAMEINUSE(client->get_nickname()));
        return;
    }

    client->set_nickname(nickname);
    client->welcome();
}

void mode(Client *client, std::vector<std::string> args)
{
    // hanling errors

    if (args.size() < 2)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "MODE"));
        return;
    }

    std::string target = args.at(0);

    Channel *channel = get_channel(target);
    if (!channel)
    {
        client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), target));
        return;
    }

    if (channel->get_admin() != client)
    {
        client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), target));
        return;
    }

    // changing the mode

    int i = 0, p = 2;
    char c;

    while ((c = args[1][i]))
    {
        char prev_c = i > 0 ? args[1][i - 1] : '\0';
        bool active = prev_c == '+';

        // add t
        switch (c)
        {
        case 'i':
        {
            channel->set_invit_only(active);
            channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+i" : "-i"), ""));
            break;
        }
        case 'l':
        {
            channel->set_limit(active ? atoi(args[p].c_str()) : 0);
            channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+l" : "-l"), (active ? args[p] : "")));
            p += active ? 1 : 0;
            break;
        }
        case 'k':
        {
            channel->set_key(active ? args[p] : "");
            channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+k" : "-k"), (active ? args[p] : "")));
            p += active ? 1 : 0;
            break;
        }
        case 'o':
        {
            Client *dest = get_client(args[p]);
            if (!dest)
            {
                client->reply(ERR_NOSUCHNICK(client->get_nickname(), args[p]));
                return;
            }

            if (!channel->has_member(dest))
            {
                client->reply(ERR_USERNOTINCHANNEL(client->get_nickname(), dest->get_nickname(), channel->get_name()));
                return;
            }

            channel->set_operator(active, dest);
            channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+o" : "-o"), (active ? args[p] : "")));
            // p += active ? 1 : 0;
            break;
        }
        default:
            break;
        }
        i++;
    }
}

void privMsg(Client *client, std::vector<std::string> args)
{
    if (args.size() < 2 || args[0].empty() || args[1].empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "PRIVMSG"));
        return;
    }

    // extract the target and the message

    std::string target = args.at(0);
    std::string message;

    std::vector<std::string>::iterator it = args.begin() + 1;
    std::vector<std::string>::iterator end = args.end();

    while (it != end)
    {
        message.append(*it + " ");
        it++;
    }

    if (message.at(0) == ':')
        message = message.substr(1);

    // if notice is for a channel

    if (target.at(0) == '#')
    {
        Channel *channel = get_channel(target);

        // channel not found
        if (!channel)
        {
            client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), target));
            return;
        }

        // a refaire

        // // channel is not for external messages
        // if (!channel->invit_only())
        // {
        //     std::vector<std::string> nicknames = channel->get_nicknames();

        //     std::vector<std::string>::iterator it = nicknames.begin();
        //     std::vector<std::string>::iterator end = nicknames.end();

        //     // check if client is in the channel
        //     while (it != end)
        //     {
        //         if (*it == client->get_nickname())
        //             break;

        //         it++;
        //     }

        //     // if not in channel
        //     if (it == end)
        //     {
        //         client->reply(ERR_CANNOTSENDTOCHAN(client->get_nickname(), target));
        //         return;
        //     }
        // }

        // channel->broadcast(RPL_PRIVMSG(client->get_prefix(), target, message), client);
        return;
    }

    // else if notice is for a client

    Client *dest = get_client(target);
    if (!dest)
    {
        client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
        return;
    }

    dest->write(RPL_PRIVMSG(client->get_prefix(), target, message));
}

// void op(Client *client, std::vector<std::string> args)
// {
//     // Handling errors
//     if (args.size() < 2)
//     {
//         client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "OP"));
//         return;
//     }

//     std::string channelName = args.at(0);
//     std::string nickname = args.at(1);

//     Channel *channel = get_channel(channelName);
//     if (!channel)
//     {
//         client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), channelName));
//         return;
//     }

//     // Check if the client is a channel operator
//     if (!channel->is_operator(client))
//     {
//         client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), channelName));
//         return;
//     }

//     // Set the client as an operator
//     Client *target = get_client(nickname);
//     if (!target)
//     {
//         client->reply(ERR_NOSUCHNICK(client->get_nickname(), nickname));
//         return;
//     }

//     channel->add_operator(target);
//     channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), "+o", target->get_nickname()));
// }

void topic(Client *client, std::vector<std::string> args)
{
    // Handling errors
    if (args.size() < 1)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "TOPIC"));
        return;
    }

    std::string channelName = args.at(0);

    Channel *channel = get_channel(channelName);
    if (!channel)
    {
        client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), channelName));
        return;
    }

    // Check if the client is in the channel
    if (!channel->has_member(client))
    {
        client->reply(ERR_NOTONCHANNEL(client->get_nickname(), channelName));
        return;
    }

    // Get the topic
    std::string topic;
    if (args.size() > 1)
    {
        std::vector<std::string>::iterator it = args.begin() + 1;
        std::vector<std::string>::iterator end = args.end();

        while (it != end)
        {
            topic.append(*it + " ");
            it++;
        }

        if (topic.at(0) == ':')
            topic = topic.substr(1);
    }

    // Set the topic
    channel->set_topic(topic, client);
    channel->broadcast(RPL_TOPIC(client->get_prefix(), channel->get_name(), topic));
}
