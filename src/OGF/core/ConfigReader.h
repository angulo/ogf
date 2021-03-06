/*
 * ConfigReader.h -- Config reader interface header file 
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

#ifndef __CONFIG_READER_H__
#define __CONFIG_READER_H__

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>

#include <OGRE/Ogre.h>

#include "LogFactory.h"

#define CONFIG_READER_KEY_DELIMITER ':'

namespace OGF {
	
	class ConfigReader {
		
		protected:
			
			std::string _configFile;
			bool _useCache;

			std::map<std::string, std::string> _config;
			
			template<class T>
			T _read(const std::string &key);
			
			void _loadConfigFile();

		public:
			
			ConfigReader(const std::string &configFile, const bool &useCache);
			~ConfigReader();
			
			template<class T>
			T get(const std::string &key);
	};

	class ConfigKeyNotFoundException : public std::exception {
		
		private:
			
			std::string _message;

		public:
		
			ConfigKeyNotFoundException(const std::string &message)
				: _message(message)
			{
			}

			virtual ~ConfigKeyNotFoundException() throw () {
			}

			virtual const char *
			what() const throw ()
			{
				return _message.c_str();
			}
	};

	// Template implementations
	
	template<class T>
	T
	ConfigReader::get(const std::string &key)
	{
		if (!_useCache)
			_loadConfigFile();
		
		if (_config.find(key) == _config.end()) {
			LogFactory::getSingletonPtr()->get(LOG_ERR)->log("ConfigReader", "get", "Config key not found: " + key, LOG_SEVERITY_ERROR);
			throw new ConfigKeyNotFoundException(key);
		}

		T result = _read<T>(key);
		return result;
	}
};

#endif
