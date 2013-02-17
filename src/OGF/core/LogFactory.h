/*
 * LogFactory.h -- Factory of logs header file.
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

#ifndef __LOG_FACTORY_H__
#define __LOG_FACTORY_H__

#include <fstream>
#include <ostream>
#include <map>

#include <OGRE/OgreSingleton.h>
#include <OGRE/OgreStringConverter.h>

#include "Types.h"
#include "Log.h"

namespace OGF {
	
	typedef std::map<LogId, Log *> LogMap;

	enum DefaultLogs {
		LOG_OUT = -2,
		LOG_ERR = -1
	};

	class LogFactory : public Ogre::Singleton<LogFactory> {

		private:
			
			LogMap _logMap; 	
			
		public:

			LogFactory();
			~LogFactory();

			static LogFactory & getSingleton();
			static LogFactory * getSingletonPtr();
			
			Log * create(const LogId &id, const std::string &path);
			Log * get(const LogId &id);

	}; // Class LogFactory
}; // Namespace OGF

#endif
