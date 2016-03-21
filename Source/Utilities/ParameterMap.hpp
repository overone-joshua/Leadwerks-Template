/*-------------------------------------------------------
                    <copyright>
    
    File: ParameterMap.hpp
    Language: C++
    
    (C) Copyright Eden Softworks
    
    Author: Joshua Allen
    E-Mail: Joshua(AT)EdenSoftworks(DOT)net
    
    Description: Header file for ParameterMap utility.
                 The ParameterMap provides a convenient 
                 way to dynamically add or access
                 different properties of different types.

---------------------------------------------------------*/

#ifndef _PARAMETERMAP_HPP_
	#define _PARAMETERMAP_HPP_

#pragma once
#include "Leadwerks.h"
#include <string>
#include <map>

struct ParameterMap
{
	typedef std::map<std::string, int>::iterator IntMapIterator;
	typedef std::map<std::string, float>::iterator FloatMapIterator;
	typedef std::map<std::string, Leadwerks::Vec3>::iterator Vec3MapIterator;
	typedef std::map<std::string, std::string>::iterator StringMapIterator;		
	typedef std::map<std::string, void*>::iterator DataMapIterator;

	typedef std::map<std::string, int> IntMap;
	typedef std::map<std::string, float> FloatMap;
	typedef std::map<std::string, Leadwerks::Vec3> Vec3Map;
	typedef std::map<std::string, std::string> StringMap;		
	typedef std::map<std::string, void*> DataMap;

public:
	const IntMap& GetIntMap(void) { return intMap; }
	const FloatMap& GetFloatMap(void) { return floatMap; }
	const Vec3Map& GetVec3Map(void) { return vec3Map; }
	const StringMap& GetStringMap(void) { return stringMap; }		
	const DataMap& GetGameObjectMap(void) { return dataMap; }

	const IntMapIterator GetInt(std::string key) { return intMap.find(key); }
	const FloatMapIterator GetFloat(std::string key) { return floatMap.find(key); }
	const Vec3MapIterator GetVec3(std::string key) { return vec3Map.find(key); }
	const StringMapIterator GetString(std::string key) { return stringMap.find(key); }		
	const DataMapIterator GetGameObject(std::string key) { return dataMap.find(key); }

	ParameterMap* Set(std::string key, int val) { if (key != "") { intMap[key] = val; } return this; }
	ParameterMap* Set(std::string key, float val) { if (key != "") { floatMap[key] = val; } return this; }
	ParameterMap* Set(std::string key, Leadwerks::Vec3 val) { if (key != "") { vec3Map[key] = val; } return this; }
	ParameterMap* Set(std::string key, std::string val) { if (key != "") { stringMap[key] = val; } return this; }		
	ParameterMap* Set(std::string key, void* val) { if (key != "") { dataMap[key] = val; return this; } }

    void RemoveInt(std::string key) { if (key != "") { intMap.erase(key); } }
	void RemoveFloat(std::string key) { if (key != "") {floatMap.erase(key); } }
	void RemoveVec3(std::string key) { if (key != "") { vec3Map.erase(key); } }
	void RemoveString(std::string key) { if (key != "") { stringMap.erase(key); } }		
	void RemoveGameObject(std::string key) { if (key != "") { dataMap.erase(key); } }

protected:
	
private:
	IntMap intMap;
	FloatMap floatMap;
	Vec3Map vec3Map;
	StringMap stringMap;		
	DataMap dataMap;

}; // end class.

#endif // _PARAMETERMAP_HPP_