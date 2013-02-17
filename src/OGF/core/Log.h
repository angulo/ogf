/*
 * Log.h -- Logger class header file.
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

#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>
#include <fstream>

#define OGF_LOG_MARK std::string("[OGF]")
#define OGF_LOG_END_MARK std::string("[/OGF]")

namespace OGF {
	
	enum LogSeverity {
		LOG_SEVERITY_ERROR = 0,
		LOG_SEVERITY_WARN = 1,
		LOG_SEVERITY_INFO = 2
	};
	
	class Log {
		
		private:

			std::ostream *_outputStream;
			bool _isFile;
		
		public:
			
			Log(std::ostream *outputStream, const bool &isFile = true);
			~Log();

			void log(const std::string &rawOutput);
			void log(const std::string &className, const std::string &method, const std::string &message, const LogSeverity &severity = LOG_SEVERITY_INFO);
			void log(const std::string &context, const std::string &message);
	}; // Class Log
}; // Namespace OGF

#endif
