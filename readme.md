**Leadwerks Template Project**
--------------------------
----------

## Synopsis

The Leadwerks Template Project is an attempt to help ease game development with Leadwerks, using C++.  By using the the provided template, you will be able to jump right into developing a game application, without having to wire up a base application yourself.

## Motivation

I have been developing game projects with Leadwerks and C++ since June 2013, and it has not always been an easy path. I wanted to take the time and share my experiences with Leadwerks, to provide an easier route to developing game applications, using C++ in Leadwerks. By providing the base essentials that are required for a project, any type of application can be developed, or extended from the existing source code.

## Contents

**Camera Manager**

A Manager class, designed to help use, and manipulate the Leadwerks Camera object. The camera manager has support for three different types of camera behaviors, **First-Person**, **Third-Person** and **Flight**. To use the first-person, or third-person camera, you are able to use the built in targeting system, which will automatically attach the game camera to the given target.

**Game Object**

A base game object class, designed to be robust and extensible. This object is used to bring together the game camera, user input and Leadwerks entities. The current state of the game object is very bare-bones however, it is meant to be extended for specific uses like player-objects, weapons etc.

**Input Manager**

A Manager class, designed to help ease the process of polling input information. This class really helps proved an easy way to poll mouse information, and make use of it without having to keep getting a handle to the current Leadwerks window, and or Context.

**State Manager**

A Manager class, designed to add state management to a game project. Having a game is one thing, but being able to manage application states adds a whole new way for user's to interact with an application. The State Manager provides an easy, and efficient way to create states, switch between registered states and to remove states, while preserving the flow of the application.

## Versions

v0.0.2 - Contains the added Game Object, Camera Manager, Input Manager and State Manager, providing a complete game-application template. This can be used if you want to start getting right into game development, without having to wire up base requirements for an application.

v0.0.1 - Contains refactored App.h and App.cpp source files, providing a complete boilerplate application. This can be used if you want to build your own application from scratch.

## Licence

Copyright (c) 2013 2014 2015 Eden Softworks Joshua J Allen
	
This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.