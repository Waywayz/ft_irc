/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:10:25 by romain            #+#    #+#             */
/*   Updated: 2023/12/11 13:13:27 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_PARSER_HPP
#define IRC_PARSER_HPP

#include <iostream>
#include <sstream>
#include <string>

#include <vector>
#include <map>

class Parser;

#include "Command.hpp"

class Parser
{
private:
    Server *_srv;
    std::map<std::string, Command *> _commands;

    std::string trim(const std::string &str);

public:
    Parser(Server *srv);
    ~Parser();

    void invoke(Client *client, const std::string &message);
};

#endif