/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Exception
*/

#ifndef __EXCEPTION_HPP_
#define __EXCEPTION_HPP_

#include <string>
#include <exception>

class IndieException : public std::exception {
public:
    IndieException(const std::string &msg, const std::string &where): _what(msg), _where(where)
        {};

    const char *what() const noexcept override
        {
            return _what.c_str();
        }

    const char *where() const noexcept
        {
            return _where.c_str();
        }

private:
    std::string _what;
    std::string _where;
};

#endif
