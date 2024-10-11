#include "SectionList.h"

SectionList::SectionList(): head(nullptr)
{
	//뭔가를 채워야 하는건가?
}
SectionList::~SectionList()
{
    // SectionListNode와 연결된 메모리를 모두 해제
    SectionListNode* current = head;
    while (current != nullptr) {
        SectionListNode* nextNode = current->getNext();

        // 연결된 SubtitleListNode들의 메모리 해제
        SubtitleListNode* contentNode = current->getContentHead();
        while (contentNode != nullptr) {
            SubtitleListNode* nextContent = contentNode->getNext();
            delete contentNode; // 내용 노드 메모리 해제
            contentNode = nextContent;
        }

        delete current; // 섹션 노드 메모리 해제
        current = nextNode;
    }
}

SectionListNode* SectionList::getHead() { return head; }

/////////////// Insert///////////
	// 새로운 섹션을 추가하는 함수
void SectionList::addSection(int sectionNumber, SubtitleListNode* contentHead) {
	SectionListNode* newSection = new SectionListNode(sectionNumber);
	newSection->setContentHead(contentHead);

	//SectionListNode* temp = head;

	if (head == nullptr) {
		head = newSection;
	}
	else {
		SectionListNode* temp = head;
		while (temp->getNext() != nullptr) {
			temp = temp->getNext();
		}
		temp->setNext(newSection);
	}
}
////////// Search///////////
 // 섹션 번호를 기준으로 섹션을 검색하는 함수
SectionListNode* SectionList::findSection(int sectionNumber) const {
	SectionListNode* temp = head;
	while (temp != nullptr) {
		if (temp->getSectionNumber() == sectionNumber) {
			return temp;
		}
		temp = temp->getNext();
	}
	return nullptr;  // 섹션 번호가 없으면 nullptr 반환
}