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

#ifndef CMD_HPP
# define CMD_HPP

# include <string>

class Client;

class Server;

class Command
{
private:

    Command();
    Command(const Command &src);
	Command	&operator=(const Command &src);
    
public:

    Command(const std::string &line, Client *sender);
    ~Command();
};

#endif