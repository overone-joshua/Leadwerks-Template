//
// Created by Joshua on 1/16/2016.
//

#ifndef _COMMON_HPP_H
    #define _COMMON_HPP_H

#pragma once
#include "App.h"
#include "Services/AppController.hpp"

#include <cstdint>

extern App*             gApp;
extern AppController*   gAppCtrl;

typedef std::uint32_t   uint32_t;
typedef std::uint64_t   uint64_t;

#endif _COMMON_HPP_H
