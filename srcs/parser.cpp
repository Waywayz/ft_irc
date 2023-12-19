
#include "IRC.hpp"
/*
    Remplacer la classe par juste qques fonctions:
        tableau de paires : string / pointeur sur fonction
    si mot du parsing = commande[x][1](str) 
    alors exec command[x][2](*f())    

    Le parser doit while tant qu'il y a des lignes 
    dans le buffer <!>

        
*/


void    parse_n_exec(char *buffer, Client *client) {

typedef void (*cmds)(Client*, std::vector<std::string>);
std::vector<std::pair<std::string, cmds> > commands;
commands.push_back(std::make_pair("JOIN", static_cast<cmds>(&join)));
commands.push_back(std::make_pair("KICK", static_cast<cmds>(&kick)));
commands.push_back(std::make_pair("PASS", static_cast<cmds>(&pass)));
commands.push_back(std::make_pair("USER", static_cast<cmds>(&user)));
commands.push_back(std::make_pair("MODE", static_cast<cmds>(&mode)));
commands.push_back(std::make_pair("PRIVMSG", static_cast<cmds>(&privMsg)));
commands.push_back(std::make_pair("TOPIC", static_cast<cmds>(&topic)));

    std::istringstream bufferStream(buffer);
    std::string line;

    while (std::getline(bufferStream, line)) {
        std::istringstream lineStream(line);
        std::string command;
        lineStream >> command;
        std::cout << command << std::endl;
        for (size_t i = 0; i < commands.size(); ++i) {
            if (commands[i].first == command) {

                std::vector<std::string> args;
                std::string arg;
                while (lineStream >> arg) {
                    args.push_back(arg);
                }
                commands[i].second(client, args);
                break;
            }
        }
    }
}

std::string trim(const std::string &str)
{
    std::string WHITESPACE = " \n\r\t\f\v";
    std::string result = "";

    size_t start = str.find_first_not_of(WHITESPACE);
    if (start != std::string::npos)
        result = str.substr(start);

    size_t end = result.find_last_not_of(WHITESPACE);
    if (end != std::string::npos)
        result = result.substr(0, end + 1);

    return result;
}
/*
void invoke(Client *client, const std::string &message)
{
    std::stringstream ss(message);
    std::string syntax;

    while (std::getline(ss, syntax))
    {
        syntax = trim(syntax);

        std::string name = syntax.substr(0, syntax.find(' '));

        try
        {
            std::vector<std::string> args;
            std::stringstream line(syntax.substr(name.length(), syntax.length()));
            std::string buf;

            Command *cmd = _commands.at(name);

            while (line >> buf)
                args.push_back(buf);

            if (!client->is_registered() && cmd->auth_required())
            {
                client->reply(ERR_NOTREGISTERED(client->get_nickname()));
                return;
            }

            cmd->execute(client, args);
        }
        catch (const std::exception &e)
        {
            client->reply(ERR_UNKNOWNCOMMAND(client->get_nickname(), name));
        }
    }
}*/