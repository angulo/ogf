/*
 * LogFactory.cpp -- Factory of logs implementation file.
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

#include "LogFactory.h"

using namespace OGF;

template<> LogFactory * Ogre::Singleton<LogFactory>::msSingleton = 0;

LogFactory::LogFactory()
{
	// Create predefined output logs
	_logMap[LOG_OUT] = new Log(&std::cout, false);
	_logMap[LOG_ERR] = new Log(&std::cerr, false);
}

LogFactory::~LogFactory()
{
	for (LogMap::iterator it = _logMap.begin(); it != _logMap.end(); it++)
		delete it->second;
}

LogFactory &
LogFactory::getSingleton()
{
	if (!msSingleton) {
		LogFactory *instance = new LogFactory();
	}

	return *msSingleton;
}

LogFactory *
LogFactory::getSingletonPtr()
{
	if (!msSingleton) {
		LogFactory *instance = new LogFactory();
	}

	return msSingleton;
}

Log *
LogFactory::create(const LogId &id, const std::string &path)
{
	std::ostream *outputStream = NULL;
	std::ofstream *fileStream = new std::ofstream(path.c_str(), std::ios::out | std::ios::app);

	// Default to cout if its not possible to open the logfile
	if (!fileStream->is_open()) {
		delete fileStream;
		outputStream = &std::cout;
		_logMap[LOG_ERR]->log("LogFactory", "create", "Impossible to open log file to write as " + path + ", cout to be used", LOG_SEVERITY_WARN);
	} else {
		outputStream = fileStream;
	}

	Log *log = new Log(outputStream);
	_logMap[id] = log;

	return log;
}

Log *
LogFactory::get(const LogId &id)
{
	Log *log = NULL;
	LogMap::iterator it = _logMap.find(id);

	if (it != _logMap.end()) {
		log = it->second;
	} else {
		_logMap[LOG_ERR]->log("LogFactory", "get", "No valid log with id " + Ogre::StringConverter::toString(id) + ", cout to be used", LOG_SEVERITY_WARN);
		log = _logMap[LOG_OUT];
	}

	return log;
}
