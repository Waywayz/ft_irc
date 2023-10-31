/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rovillar <rovillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:39:17 by rovillar          #+#    #+#             */
/*   Updated: 2023/10/31 02:39:18 by rovillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"

#include <iostream>

int main(int ac, char **av)
{
    if (ac != 3)
    {
        std::cout << "./irc <port> <password>" << std::endl;
    }

    Server server(av[1], av[2]);

    return (0);
}