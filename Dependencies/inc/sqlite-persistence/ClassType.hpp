#ifndef _CLASS_TYPE_HPP_
#define _CLASS_TYPE_HPP_

#pragma once

#define CLASS_TYPE(classname) \
	public: \
		virtual const char* ObjectType() { return ClassType(); } \
		static const char* ClassType() { return #classname; }

#endif _CLASS_TYPE_HPP_