/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rovillar <rovillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 02:39:07 by rovillar          #+#    #+#             */
/*   Updated: 2023/11/02 16:35:16 by rovillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include <map>
# include <fstream>
# include <sstream>
# include <iostream>

class Config
{
public:

    Config();
    ~Config();

    const std::map<std::string, std::string>    &get_map();
    void                                        set(const std::string &key, const std::string &value);
    const std::string                           &get(const std::string &key);

private:

    std::map<std::string, std::string>  _m;

    Config(const Config &src);
    Config &operator=(const Config &src);

};

#endif