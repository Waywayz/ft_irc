/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rovillar <rovillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:39:13 by rovillar          #+#    #+#             */
/*   Updated: 2023/10/31 02:39:14 by rovillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Config.hpp"

# include <string>

class Server
{
public:

    Server(const std::string &port, const std::string &password);
    ~Server();

    Config  &get_config(void);

private:

    Server();
    Server(const Server &src);
    Server &operator=(const Server &src);

};

#endif