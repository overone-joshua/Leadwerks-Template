//
// Created by Joshua on 1/16/2016.
//

#ifndef _COMMON_HPP_H
    #define _COMMON_HPP_H

#pragma once
#include "Leadwerks.h"

// < Macros
#define SAFE_DELETE( p )       { if( p ) { delete ( p );     ( p ) = NULL; } }
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] ( p );   ( p ) = NULL; } }
#define SAFE_RELEASE( p )      { if( p ) { ( p )->Release(); ( p ) = NULL; } }

// -----

#endif _COMMON_HPP_H
