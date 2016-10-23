#pragma once
#ifdef CRYSTALCORE_EXPORTS
#define CRYSTALCORE_API __declspec(dllexport)
#else
#define CRYSTALCORE_API __declspec(dllimport)
#endif
/***********************************/
//					LogServer
//Purpose:����LogClient������Log����д���ļ�
//Version:		0.7 Beta
//The way:	Pipe for windows&queue
//		(C)Copyright @FrozenMac
/***********************************/
//struct _err {
//	int err;
//	int step;
//};
UINT CALLBACK LogServerMainThread(PVOID);
UINT CALLBACK WriteThread(PVOID);
class CRYSTALCORE_API LogServer
{
	wofstream *out;
	HANDLE hMainThread;
	HANDLE hWriteThread;
public:
	queue<wstring>* _Queue;
	LogServer();

	//д���ļ�
	void Log(const wchar_t*);

	//д���ļ�&���ʱ��
	//Ӧ����LogServer ���ڳ���ʹ��
	void LogWithTime(const wchar_t*);
	bool bRun;
	
	//������Դ
	~LogServer();
	//_err err;
};

