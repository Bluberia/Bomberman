/*
** EPITECH PROJECT, 2019
** Indie
** File description:
** Noncopyable
*/

#ifndef INDIE_STUDIO_NONCOPYABLE_HPP
#define INDIE_STUDIO_NONCOPYABLE_HPP

class NonCopyable {
public:
    NonCopyable (const NonCopyable &) = delete;
    NonCopyable &operator =(const NonCopyable &) = delete;
};

#endif
