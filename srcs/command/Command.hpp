/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rovillar <rovillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 04:49:59 by rovillar          #+#    #+#             */
/*   Updated: 2023/11/08 04:50:00 by rovillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <string>

class Command;

class Command
{
    protected:

        Server* _srv;
        bool    _auth;

        Command();
        Command(const Command& src);

    public:

        // Sans explicit, cela pourrait être implicite
        // Command cmd = &server; // Erreur si explicit est présent
        // Avec explicit, doit être explicite
        explicit Command(Server* srv, bool auth = true);
        virtual ~Command();

        bool auth_required() const;

        virtual void execute(Client* client, std::vector<std::string> args) = 0;
};

class Join : public Command
{
    public:

        Join(Server* srv);
        ~Join();

        void    execute(Client* client, std::vector<std::string> args);
};

#endif