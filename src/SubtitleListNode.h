#pragma once
#include <string>

using namespace std;

class SubtitleListNode
{
private:
	string time;  
	string content;
	SubtitleListNode* next; //다음 노드를 가리키는 포인터

public:
	/*SubtitleListNode() : next(nullptr) {}
	~SubtitleListNode() {}
	*/
	SubtitleListNode(string time, string content)
		: time(time), content(content), next(nullptr) {}

	//소멸자 추가


	string getTime() const { return time; }
	string getContent() const { return content; }
	SubtitleListNode* getNext() { return next; }


	void setTime(string time) { this->time = time; }
	void setContent(string content) { this->content = content; }
	void setNext(SubtitleListNode* next) { this->next = next; }
};
