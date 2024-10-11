#pragma once
#include "SectionListNode.h"

class SectionList
{
private:
	SectionListNode* head;
	//List 의 첫 번째 섹션 노드를 가리키는 포인터

public:
	
	SectionList(); //생성자 선언
	~SectionList(); //소멸자 선언
	

	SectionListNode* getHead();
	//세터는?

	//선언만
	void addSection(int sectionNumber, SubtitleListNode* contentHead);
	SectionListNode* findSection(int sectionNumber) const;

};
