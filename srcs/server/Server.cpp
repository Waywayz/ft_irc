/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rovillar <rovillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:39:11 by rovillar          #+#    #+#             */
/*   Updated: 2023/10/31 02:48:49 by rovillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() {}; //empty

Server::Server(const std::string &port, const std::string &password) {
    this->get_config().set("port", port);
    this->get_config().set("password", password);
    //to continue
};

Server::~Server() {
    //need to free etc
};

//need copy to surcharge operator