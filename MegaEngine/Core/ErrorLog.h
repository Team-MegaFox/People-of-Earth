// ***********************************************************************
// Author           : Jesse Derochie
// Created          : 01-30-2016
//
// Last Modified By : Jesse Derochie
// Last Modified On : 02-01-2016
// ***********************************************************************
// <copyright file="ErrorLog.h" company="Team MegaFox">
//     Copyright (c) Team MegaFox. All rights reserved.
// </copyright>
// <summary>
/*
	This ErrorLog file is used to keep track of errors being created within 
	MegaEngine. 
*/
// </summary>
// ***********************************************************************
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <fstream>
#include <string>
#include <ctime>
#include "..\Core\Time.h"

class ErrorLog
{
public:

	/// <summary>
	/// The log file name
	/// </summary>
	std::string logFileName = "MegaEngine_ErrorLog.txt";
	/// <summary>
	/// The SeverityLevel Enum of the ErrorLog
	/// </summary>
	enum SeverityLevel
	{
		MEGA_NONE,		// NO ERROR
		MEGA_INFO,		// MEGAENGINE LOAD-UP SEQUENCE
		MEGA_WARNING,	// WARNING BUT OK TO CONTINUE
		MEGA_ERROR,		// MEGA ERROR
		MEGA_TRACE		// ERROR TRACE
	};

	/// <summary>
	/// Finalizes an instance of the <see cref="ErrorLog"/> class.
	/// </summary>
	~ErrorLog();
	/// <summary>
	/// Gets the instance.
	/// </summary>
	/// <returns></returns>
	static ErrorLog * getInstance()
	{
		if (instance == nullptr)
		{
			instance = new ErrorLog;
		}
		return instance;
	}
	/// <summary>
	/// Closes this instance.
	/// </summary>
	void close();
	/// <summary>
	/// Logs the specified severity.
	/// </summary>
	/// <param name="severity">The severity.</param>
	/// <param name="message">The message.</param>
	void log(SeverityLevel severity, std::string message);
	/// <summary>
	/// Sets the log file.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	void setLogFile(std::string & fileName);
	/// <summary>
	/// Sets the severity setting of the LogManager, only
	///	those messages whose severity is greater than
	///	or equal to this severity will be added to the log.
	/// </summary>
	/// <param name="severity">The minimum severity of messages to print.</param>
	void setSeverity(SeverityLevel severity) { m_currentSeverity = severity; }
	/// <summary>
	/// Returns the current severity of the ErrorLog
	/// </summary>
	/// <returns></returns>
	SeverityLevel getSeverity() { return m_currentSeverity; }
	/// <summary>
	/// Errors the specified message.
	/// </summary>
	/// <param name="message">The message.</param>
	void error(std::string message);
	/// <summary>
	/// Warnings the specified message.
	/// </summary>
	/// <param name="message">The message.</param>
	void warning(std::string message);
	/// <summary>
	/// Traces the specified message.
	/// </summary>
	/// <param name="message">The message.</param>
	void trace(std::string message);
	/// <summary>
	/// Informations the specified message.
	/// </summary>
	/// <param name="message">The message.</param>
	void info(std::string message);
	/// <summary>
	/// Sets up log.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	void setUpLog(std::string fileName);
	/// <summary>
	/// Gets the time.
	/// </summary>
	/// <returns></returns>
	std::string getTime() { setRealTime(); return m_time; }

private:
	/// <summary>
	/// The instance of this class
	/// </summary
	static ErrorLog * instance;
	/// <summary>
	/// The m_output stream
	/// </summary>
	std::ofstream * m_outputStream = nullptr;
	/// <summary>
	/// The log was setup
	/// </summary>
	bool logWasSetup = false;
	/// <summary>
	/// The m_current severity
	/// </summary>
	SeverityLevel m_currentSeverity = MEGA_NONE;

	/// <summary>
	/// Sets the real time.
	/// </summary>
	void setRealTime()
	{
		time_t temp = (time_t)Time::getTime();
		m_time = ctime(&temp);
	}

	/// <summary>
	/// The num_ errors
	/// </summary>
	int Num_Errors = 0;

	/// <summary>
	/// The m_time
	/// </summary>
	std::string m_time;

	/// <summary>
	/// Prevents a default instance of the <see cref="ErrorLog"/> class from being created.
	/// </summary>
	ErrorLog() {}
};

