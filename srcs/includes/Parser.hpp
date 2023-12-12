/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <romain@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
<<<<<<<< HEAD:srcs/includes/Parser.hpp
/*   Created: 2023/12/11 13:10:25 by romain            #+#    #+#             */
/*   Updated: 2023/12/11 13:13:27 by romain           ###   ########.fr       */
========
/*   Created: 2023/11/08 04:49:56 by rovillar          #+#    #+#             */
/*   Updated: 2023/12/11 13:13:41 by romain           ###   ########.fr       */
>>>>>>>> main:srcs/command/Command.cpp
=======
/*   Created: 2023/12/11 13:10:25 by romain            #+#    #+#             */
/*   Updated: 2023/12/11 13:13:27 by romain           ###   ########.fr       */
>>>>>>> main
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

<<<<<<< HEAD
=======
#include "Command.hpp"
>>>>>>> main

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