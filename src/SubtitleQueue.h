#pragma once
#include "SubtitleQueueNode.h"
#include <iostream>

using namespace std;

class SubtitleQueue
{
private:
    int MAX_SIZE;
    SubtitleQueueNode* front;         // 큐의 앞
    SubtitleQueueNode* rear;          // 큐의 뒷부분을 가리키는 포인터
    int size;                         // 현재 큐의 크기

public:
    SubtitleQueue();
    ~SubtitleQueue();

    bool IsEmpty();
    bool IsFull();
    //얘는 get,set 필요 없는건가? 접근 가능하니까?
    void Push(string time, string content);
    SubtitleQueueNode* Pop();
    SubtitleQueueNode* Front();
};

/*
#pragma once
#include "SubtitleQueueNode.h"

class SubtitleQueue
{
private:

public:
	SubtitleQueue();
	~SubtitleQueue();

	bool IsEmpty();
	bool IsFull();
	void Push();
	SubtitleQueueNode Pop();
	SubtitleQueueNode Front();
};
*/