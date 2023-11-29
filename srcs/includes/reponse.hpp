/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reponse.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:59:22 by romain            #+#    #+#             */
/*   Updated: 2023/11/29 14:09:13 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

/* ERROR */

#define ERR_NEEDMOREPARAMS(source, command) "461 " + source + " " + command + " :Not enough parameters"
#define ERR_TOOMANYCHANNELS(source, channel) "405 " + source + " " + channel + " :You have joined too many channels"
#define ERR_CHANNELISFULL(source, channel) "471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_BADCHANNELKEY(source, channel) "475 " + source + " " + channel + " :Cannot join channel (+k)"

/* COMMAND */

#define RPL_KICK(source, channel, target, reason) ":" + source + " KICK " + channel + " " + target + " :" + reason

#endif