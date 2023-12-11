/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 04:49:56 by rovillar          #+#    #+#             */
/*   Updated: 2023/12/11 13:13:41 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(Server *srv, bool auth) : _srv(srv), _auth(auth) {}

Command::~Command() {}

bool Command::auth_required() const { return _auth; }