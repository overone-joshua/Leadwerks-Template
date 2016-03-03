/*-------------------------------------------------------
                    <copyright>
    
    File: Macros.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for Project Macros.
                 This file provides a singular location
                 for storing generic macros that a
                 regularly used accross a project.                 
    
    Functions: 1. SAFE_DELETE(p);
               
               2. SAFE_DELETE_ARRAY(p);
               
               3. SAFE_RELEASE(p);
               
               4. CLASS_TYPE(className);

---------------------------------------------------------*/

#ifndef _MACROS_HPP_
	#define _MACROS_HPP_

// < Macros
#define SAFE_DELETE( p )       { if( p ) { delete ( p );     ( p ) = NULL; } }
#define SAFE_DELETE_ARRAY( p ) { if( p ) { delete[] ( p );   ( p ) = NULL; } }
#define SAFE_RELEASE( p )      { if( p ) { ( p )->Release(); ( p ) = NULL; } }

#define CLASS_TYPE(classname) \
	public: \
		virtual const char* ObjectType() { return ClassType(); } \
		static const char* ClassType() { return #classname; }

// -----

#endif _MACROS_HPP_