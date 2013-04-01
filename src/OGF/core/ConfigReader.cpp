/*
 * ConfigReader.cpp -- Config reader interface implementation file
 *
 * Copyright (C) 2013 Javier Angulo Luceron <javier.angulo1@gmail.com>
 * 
 * ogf is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ogf is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ConfigReader.h"

using namespace OGF;

template<class T>
T _read(const std::string &key)
{

}

ConfigReader::ConfigReader(const std::string &configFile, const bool &useCache)
	: _configFile(configFile), _useCache(useCache)
{

}

ConfigReader::~ConfigReader()
{

}

template<class T>
T
ConfigReader::get(const std::string &key)
{
	T result = _read<T>(key);
	return result;
}
