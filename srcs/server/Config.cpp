/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rovillar <rovillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:39:05 by rovillar          #+#    #+#             */
/*   Updated: 2023/11/02 17:18:24 by rovillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config() {
    std::ifstream   input("config/defaut.conf", std::ifstream::in);

    if (!input.good()) {
        std::cerr << "error: ifstream config file" << std::endl;
        exit(1);
    }

    std::string line;

    while (!input.eof()) {
        std::getline(input, line);

        std::stringstream   ss(line);
        std::string         key;
        std::string         value;

        std::getline(ss, key, '=');
        std::getline(ss, value, '\n');

        this->_m[key] = value;
    }

    input.close();

    if (atoi(this->_m["timeout"].c_str()) <= 0)
        this->_m["timeout"] = "5000";
    if (atoi(this->_m["ping"].c_str()) <= 0)
        this->_m["ping"] = "60";
};

Config::~Config() {};

Config  &Config::operator=(const Config &src) {
    this->_m = src._m;

    return (*this);
};

const std::map<std::string, std::string>    &Config::get_map() {
    return (this->_m);
};

void    Config::set(const std::string &key, const std::string &value) {
    this->_m[key] = value;
};

const std::string   &Config::get(const std::string &key) {
    return (this->_m[key]);
};