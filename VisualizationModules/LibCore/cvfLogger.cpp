//##################################################################################################
//
//   Custom Visualization Core library
//   Copyright (C) 2011-2012 Ceetron AS
//    
//   This library is free software: you can redistribute it and/or modify 
//   it under the terms of the GNU General Public License as published by 
//   the Free Software Foundation, either version 3 of the License, or 
//   (at your option) any later version. 
//    
//   This library is distributed in the hope that it will be useful, but WITHOUT ANY 
//   WARRANTY; without even the implied warranty of MERCHANTABILITY or 
//   FITNESS FOR A PARTICULAR PURPOSE.   
//    
//   See the GNU General Public License at <<http://www.gnu.org/licenses/gpl.html>> 
//   for more details. 
//
//##################################################################################################

#include "cvfBase.h"
#include "cvfLogger.h"
#include "cvfLogEvent.h"
#include "cvfLogDestination.h"

namespace cvf {



//==================================================================================================
///
/// \class cvf::Logger
/// \ingroup Core
///
/// Logger class
///
/// Note that in itself, the Logger is not thread safe. This means that logger configuration, such
/// as setting the logging level and specifying the log destination, must be done in a single
/// threaded environment.
/// 
//==================================================================================================

//--------------------------------------------------------------------------------------------------
/// Constructor
//--------------------------------------------------------------------------------------------------
Logger::Logger(const String& loggerName, int logLevel, LogDestination* logDestination)
:   m_name(loggerName),
    m_logLevel(logLevel),
    m_destination(logDestination)
{
}


//--------------------------------------------------------------------------------------------------
/// Destructor
//--------------------------------------------------------------------------------------------------
Logger::~Logger()
{
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
const String& Logger::name() const
{
    return m_name;
}


//--------------------------------------------------------------------------------------------------
/// Set the logging level of this logger
///
/// Set a level of 0 to disable all logging for this logger. 
//--------------------------------------------------------------------------------------------------
void Logger::setLevel(int logLevel)
{
    m_logLevel = logLevel;
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
int Logger::level() const
{
    return m_logLevel;
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
LogDestination* Logger::destination()
{
    return m_destination.p();
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void Logger::setDestination(LogDestination* logDestination)
{
    m_destination = logDestination;
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void Logger::error(const String& message)
{
    error(message, CodeLocation());
}


//--------------------------------------------------------------------------------------------------
///
//--------------------------------------------------------------------------------------------------
void Logger::error(const String& message, const CodeLocation& location)
{
    if (m_logLevel >= LL_ERROR && m_destination.notNull())
    {
        log(message, LL_ERROR, location);
    }
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void Logger::warning(const String& message)
{
    warning(message, CodeLocation());
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void Logger::warning(const String& message, const CodeLocation& location)
{
    if (m_logLevel >= LL_WARNING && m_destination.notNull())
    {
        log(message, LL_WARNING, location);
    }
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void Logger::info(const String& message)
{
    info(message, CodeLocation());
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void Logger::info(const String& message, const CodeLocation& location)
{
    if (m_logLevel >= LL_INFO && m_destination.notNull())
    {
        log(message, LL_INFO, location);
    }
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void Logger::debug(const String& message, const CodeLocation& location)
{
    if (m_logLevel >= LL_DEBUG && m_destination.notNull())
    {
        log(message, LL_DEBUG, location);
    }
}


//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
void Logger::log(const String& message, Logger::Level messageLevel, const CodeLocation& location)
{
    if (m_logLevel >= messageLevel && m_destination.notNull())
    {
        m_destination->log(LogEvent(m_name, message, messageLevel, location));
    }
}





} // namespace cvf

