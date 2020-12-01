
#include "stdafx.h"
#include "windows.h"
#include <conio.h>
#include <stdlib.h>
//#include <fstream.h>
#include <fstream>
#include <io.h>
#include <string.h>
#include <stdio.h>

#define INTE_PER_SEC 100 
#define MAX_THREAD_NUM  64
#define SEM_MAX_FULL    64
#define READER 'R'
#define WRITER 'W'

using namespace  std;

struct ThreadInfo
{
	int    serial;
	char   entity;
	double delay;
	double persist;
};


int read_count = 0;

CRITICAL_SECTION smutex;
CRITICAL_SECTION sw;

HANDLE mutex;
HANDLE W;


void READERWRITER(char* file);
void Thread_READER(void* p);
void Thread_WRITER(void* p);

int main(int argc, char* argv[])
{
	READERWRITER("rwdata.txt");
	return 0;
}

///////////////////////////////////////////
void READERWRITER(char* file)
{
	DWORD n_thread = 0;
	DWORD thread_ID;

	HANDLE		h_Thread[MAX_THREAD_NUM];
	ThreadInfo  thread_info[MAX_THREAD_NUM];


	ifstream inFile;
	inFile.open(file);

	puts("Read Data File \n");

	while (inFile)
	{
		inFile >> thread_info[n_thread].serial;
		inFile >> thread_info[n_thread].entity;
		inFile >> thread_info[n_thread].delay;
		inFile >> thread_info[n_thread].persist;
		n_thread++;
		inFile.get();
	}


	for (int i = 0; i < (int)(n_thread); i++)
	{
		if (thread_info[i].entity == READER)

			h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(Thread_READER),
				&thread_info[i], 0, &thread_ID);
		else
		{
			if (thread_info[i].entity == WRITER)

				h_Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)(Thread_WRITER),
					&thread_info[i], 0, &thread_ID);

			else
			{
				puts("Bad File\n");
				exit(0);
			}
		}
	}


	InitializeCriticalSection(&smutex);
	InitializeCriticalSection(&sw);

	mutex = CreateSemaphore(NULL, 1, SEM_MAX_FULL, "mutex");
	W = CreateSemaphore(NULL, 1, SEM_MAX_FULL, "W");

	WaitForMultipleObjects(n_thread, h_Thread, TRUE, -1);

	printf("Task is Finished!\n");

	getch();

}


///////////////////////////////////////////


void  Thread_WRITER(void* p)
{

	DWORD m_delay;
	DWORD m_persist;
	int		m_serial;

	m_serial = ((ThreadInfo*)(p))->serial;
	m_delay = (DWORD)(((ThreadInfo*)(p))->delay * INTE_PER_SEC);
	m_persist = (DWORD)(((ThreadInfo*)(p))->persist * INTE_PER_SEC);

	while (true)
	{
		Sleep(m_delay);
		printf("W thread %d send the W require.\n", m_serial);
		WaitForSingleObject(W, INFINITE);
		EnterCriticalSection(&sw);
		printf("W thread %d Begin to W.\n", m_serial);
		Sleep(m_persist);
		printf("W thread %d Finish W.\n", m_serial);
		ReleaseSemaphore(W, 1, NULL);
		LeaveCriticalSection(&sw);
	}

}


void Thread_READER(void* p)
{
	DWORD m_delay;
	DWORD m_persist;
	int		m_serial;
	m_serial = ((ThreadInfo*)(p))->serial;
	m_delay = (DWORD)(((ThreadInfo*)(p))->delay * INTE_PER_SEC);
	m_persist = (DWORD)(((ThreadInfo*)(p))->persist * INTE_PER_SEC);

	while (true)
	{

		Sleep(m_delay);
		printf("R thread %d send the R require.\n", m_serial);
		WaitForSingleObject(mutex, INFINITE);
		EnterCriticalSection(&smutex);
		read_count++;
		if (read_count == 1)
		{
			WaitForSingleObject(W, INFINITE);
		}
		ReleaseSemaphore(mutex, 1, NULL);
		LeaveCriticalSection(&smutex);
		printf("R thread %d Begin to R.\n", m_serial);
		Sleep(m_persist);
		printf("R thread %d Finish R.\n", m_serial);
		WaitForSingleObject(mutex, INFINITE);
		EnterCriticalSection(&smutex);
		read_count--;
		if (read_count == 0)
		{
			ReleaseSemaphore(W, 1, NULL);
		}

		ReleaseSemaphore(mutex, 1, NULL);
		LeaveCriticalSection(&smutex);
	}
}






