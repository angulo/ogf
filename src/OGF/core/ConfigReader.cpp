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

namespace OGF {

	void
	ConfigReader::_loadConfigFile()
	{
		std::ifstream inputStream(_configFile.c_str());
		std::string tempLine;

		if (inputStream.is_open()) {
			std::string line;

			while (std::getline(inputStream, line)) {
				std::string key, value;
				std::stringstream ss(line);

				std::getline(ss, key, CONFIG_READER_KEY_DELIMITER);
				std::getline(ss, value, CONFIG_READER_KEY_DELIMITER);

				_config[key] = value;
			}
		}

		inputStream.close();
	}

	ConfigReader::ConfigReader(const std::string &configFile, const bool &useCache)
		: _configFile(configFile), _useCache(useCache)
	{
		if (_useCache)
			_loadConfigFile();
	}

	ConfigReader::~ConfigReader()
	{

	}

	// Simple type specializations

	template<>
	bool
	ConfigReader::_read(const std::string &key)
	{
		return Ogre::StringConverter::parseBool(_config[key]);
	}

	template<>
	int
	ConfigReader::_read(const std::string &key)
	{
		return Ogre::StringConverter::parseInt(_config[key]);
	}

	template<>
	long int
	ConfigReader::_read(const std::string &key)
	{
		return Ogre::StringConverter::parseLong(_config[key]);
	}

	template<>
	std::string
	ConfigReader::_read(const std::string &key)
	{
		return _config[key];
	}

	template<>
	Ogre::Real
	ConfigReader::_read(const std::string &key)
	{
		return Ogre::StringConverter::parseReal(_config[key]);
	}

	// Vector specializations

	template<>
	std::vector<bool>
	ConfigReader::_read(const std::string &key)
	{
		std::vector<bool> result;
		return result;
	}

	template<>
	std::vector<int>
	ConfigReader::_read(const std::string &key)
	{
		std::vector<int> result;
		return result;
	}

	template<>
	std::vector<long int>
	ConfigReader::_read(const std::string &key)
	{
		std::vector<long> result;
		return result;
	}

	template<>
	std::vector<Ogre::Real>
	ConfigReader::_read(const std::string &key)
	{
		std::vector<Ogre::Real> result;
		return result;
	}

};
