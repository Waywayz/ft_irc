/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rovillar <rovillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 04:49:56 by rovillar          #+#    #+#             */
/*   Updated: 2023/11/27 16:17:18 by rovillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(Server* srv, bool auth) :_srv(srv), _auth(auth) {}

Command::~Command() {}

bool    Command::auth_required() const { return _auth; }