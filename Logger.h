#pragma once

#include <Windows.h>
#include <stdio.h>

/*
	* 类名：Logger
	* 作用：提供写日志功能，支持多线程，支持可变形参数操作，支持写日志级别的设置
	* 接口：SetLogLevel：设置写日志级别
			TraceKeyInfo：忽略日志级别，写关键信息
			TraceError：写错误信息
			TraceWarning：写警告信息
			TraceInfo：写一般信息

	*使用：
	#include "Common/Logger/Logger.h"
	Logger log;

	log.SetLogLevel(LogLevelAll);
	log.TraceInfo("Ready Go");
*/
// 日志级别的提示信息
static const char * KEYINFOPREFIX	= " Key: \n";
static const char * ERRORPREFIX		= " Error: \n";
static const char * WARNINGPREFIX	= " Warning: \n";
static const char * INFOPREFIX		= " Info: \n";

static const int MAX_STR_LEN = 1024;
namespace Common
{
	// 日志级别美剧
	typedef enum EnumLogLevel
	{
		LogLevelAll = 0,	//所有信息都写日志
		LogLevelMid,		//写错误，警告信息
		LogLevelNormal,		//只写错误信息
		LogLevelStop		//不写日志
	};

	class Logger
	{
	public:
		Logger(void);
		Logger(const char * strLogPath, EnumLogLevel nLogLevel = EnumLogLevel::LogLevelNormal);
		virtual ~Logger(void);
	public:
		//写关键信息
		void TraceKeyInfo(const char * strInfo, ...);
		//写错误信息
		void TraceError(const char* strInfo, ...);
		//写警告信息
		void TraceWarning(const char * strInfo, ...);
		//写一般信息
		void TraceInfo(const char * strInfo, ...);
		//设置写日志级别
		void SetLogLevel(EnumLogLevel nLevel);
	private:
		//写文件操作
		void Trace(const char * strInfo);
		//获取当前系统时间
		char * GetCurrentTime();
		//创建日志文件名称
		void GenerateLogName();
		//创建日志路径
		void CreateLogPath();
	private:
		//写日志文件流
		FILE * m_pFileStream;
		//写日志级别
		EnumLogLevel m_nLogLevel;
		//日志的路径
		char m_strLogPath[MAX_STR_LEN];
		//日志的名称
		char m_strCurLogName[MAX_STR_LEN];
		//线程同步的临界区变量
		CRITICAL_SECTION m_cs;
	};
};