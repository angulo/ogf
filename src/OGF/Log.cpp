/*
 * Log.cpp -- Logger class implementation.
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

#include "Log.h"

using namespace OGF;

Log::Log(std::ostream *outputStream, const bool& isFile)
	:	_outputStream(outputStream), _isFile(isFile)
{
}

Log::~Log()
{
	if (_isFile) {
		dynamic_cast<std::ofstream *>(_outputStream)->close();
		delete _outputStream;
	}
}

void
Log::log(const std::string &rawOutput)
{
	*_outputStream << OGF_LOG_MARK << " " << rawOutput << std::endl;
}

void
Log::log(const std::string &className, const std::string &method, const std::string &message, const LogSeverity &severity)
{
	std::string severityString;

	switch(severity) {
		case LOG_SEVERITY_ERROR:
			severityString = "ERROR!";
			break;
		case LOG_SEVERITY_WARN:
			severityString = "warn";
			break;
		case LOG_SEVERITY_INFO:
			severityString = "info";
			break;
	}


	*_outputStream << OGF_LOG_MARK << " " << std::endl
		<< " * |Severity| " << severityString << std::endl
		<< " * |Class   | " << className << std::endl
		<< " * |Method  | " << method << std::endl
		<< " * |Message | " << message << std::endl
		<< OGF_LOG_END_MARK << std::endl;
}

void
Log::log(const std::string &context, const std::string &message)
{
	*_outputStream << OGF_LOG_MARK << " " << std::endl
		<< " * |Context | " << context << std::endl
		<< " * |Message | " << message << std::endl
		<< OGF_LOG_END_MARK << std::endl;
}
