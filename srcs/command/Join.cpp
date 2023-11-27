/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 16:37:34 by romain            #+#    #+#             */
/*   Updated: 2023/11/27 16:40:28 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Join::Join(Server* srv) : Command(srv) {}

Join::~Join() {}

void    Join::execute(Client* client, std::vector<std::string> args) {
    if (args.empty()) {
    }
}