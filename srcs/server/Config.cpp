/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rovillar <rovillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:39:05 by rovillar          #+#    #+#             */
/*   Updated: 2023/10/31 02:48:09 by rovillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config() {
    //need config constructor
};

Config::~Config() {};

Config  &Config::operator=(const Config &src) {
    this->_m = src._m;

    return (*this);
};

void    Config::set(const std::string &key, const std::string &value) {
    this->_m[key] = value;
};

const std::string   &Config::get(const std::string &key) {
    return (this->_m[key]);
};