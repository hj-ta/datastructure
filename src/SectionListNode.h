#pragma once
#include "SubtitleListNode.h"

class SectionListNode
{
private:
	int sectionNumber; //섹션 넘버
	SubtitleListNode* contentHead; //내용 노드의 시작 포인터
	SectionListNode* next; // 다음 섹션 노드를 가리키는 포인터

public:
	/*
	SectionListNode() : next(nullptr) {}
	~SectionListNode() {}
	*/ 
	SectionListNode(int sectionNumber)
		: sectionNumber(sectionNumber), contentHead(nullptr), next(nullptr) {}

	//동적 메모리 해제가 필요하지 않은 경우에도 소멸자가 필요한가?
	~SectionListNode() {}

	//여기 const 아니고 그냥으로 ?
	int getSectionNumber() const { return sectionNumber; }
	SubtitleListNode* getContentHead() const { return contentHead; }
	SectionListNode* getNext() const { return next; }
	//이거 왜 const가 있어야 되는거지? 안쓰면 오류남
	
	//여기 set sectionNumber 는 안해도 되나? 

	void setContentHead(SubtitleListNode* head) {this-> contentHead = head; }
	//이거 this 다시 확인

	void setNext(SectionListNode* next)	{ this->next = next; }
};
