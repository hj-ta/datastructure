#pragma once
#include <string>
using namespace std;

class SubtitleQueueNode {
private:
    string time;      // 자막 시간
    string content;   // 자막 내용
    SubtitleQueueNode* next;  // 다음 노드를 가리키는 포인터


public:

    string getTime() { return time; }
    string getContent() { return content; }
    SubtitleQueueNode* getNext(){ return next; }

    void setTime(string time) { this->time = time; }
    void setContent(string content) { this->content = content; }
    void setNext(SubtitleQueueNode* next) { this->next = next; }


    // 생성자: 자막 시간과 내용을 초기화
    SubtitleQueueNode(string time, string content) {
        this->time = time;
        this->content = content;
        next = nullptr;
    }

    // 소멸자
    ~SubtitleQueueNode() {}
};





/*
#pragma once

class SubtitleQueueNode
{
private:

public:
	SubtitleQueueNode() { }
	~SubtitleQueueNode() { }

};
*/