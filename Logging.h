
#pragma once

class CLogFile
{
public:
	CLogFile();
	~CLogFile();

	bool Open(const char *filepath);
	void Close();
	void Write(const char *text);

private:
	FILE *m_File;
};

class CLogger
{
public:
	typedef void(*LogFunc_t)(int, int, const char *);

	CLogger();
	virtual ~CLogger();

	bool Open();
	void Close();
	void Write(int category, int level, const char *format, ...);

	void AddLogCallback(LogFunc_t callback) { if (std::find(m_LogCallbacks.begin(), m_LogCallbacks.end(), callback) == m_LogCallbacks.end()) { m_LogCallbacks.push_back(callback); } }

private:
	CLogFile m_Log;
	std::list<LogFunc_t> m_LogCallbacks;
};

extern CLogger g_Logger;

enum {
	LOGLEVEL_Debug = 0,
	LOGLEVEL_Verbose,
	LOGLEVEL_Normal,
	LOGLEVEL_Warning,
	LOGLEVEL_Error,
	LOGLEVEL_Fatal
};

enum {
	LOGCATEGORY_Temp = 0,
	LOGCATEGORY_UserInterface,
	LOGCATEGORY_Server,
	LOGCATEGORY_World,
	LOGCATEGORY_Network,
	LOGCATEGORY_Object,
	LOGCATEGORY_Database,
	LOGCATEGORY_Client,
	LOGCATEGORY_Player,
	LOGCATEGORY_Animation,
	LOGCATEGORY_Command
};

#define LOG(category, level, ...) g_Logger.Write(LOGCATEGORY_##category, LOGLEVEL_##level, __VA_ARGS__)
#define LOG_BYTES(category, level, data, len) g_Logger.Write(LOGCATEGORY_##category, LOGLEVEL_##level, DebugBytesToString(data, len).c_str())


