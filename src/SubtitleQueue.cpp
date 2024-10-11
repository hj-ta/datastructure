#include "SubtitleQueue.h"
#include <iostream>

// 생성자: 큐를 초기화
SubtitleQueue::SubtitleQueue() {
    MAX_SIZE = 100;
    front = nullptr;
    rear = nullptr;
    size = 0;
}

// 소멸자: 동적 메모리 해제
SubtitleQueue::~SubtitleQueue() {
    while (!IsEmpty()) {
        Pop();  // 큐가 비어있을 때까지 모든 노드를 삭제
    }
}

// 큐가 비었는지 확인
bool SubtitleQueue::IsEmpty() {
    if (size == 0) return true;
    else return false;
}

// IsFull_ 큐가 꽉 찼는지 
bool SubtitleQueue::IsFull() {
    return size == MAX_SIZE;
}

// Push 함수 _ 큐에 새 노드를 삽입
void SubtitleQueue::Push(string time, string content) {
    if (IsFull()) {
        std::cerr << "Error: Queue is full!" << std::endl;
        exit(EXIT_FAILURE);  // 프로그램 종료
    }

    SubtitleQueueNode* newNode = new SubtitleQueueNode(time, content);  // 새로운 노드 생성

    if (IsEmpty()) {
        front = newNode;  // 큐가 비어있으면 front도 새 노드를 가리킴
        rear = newNode;
    }
    else {
        rear->setNext(newNode);
        rear = rear->getNext();
        // 그렇지 않으면 기존 rear의 next가 새 노드를 가리키게 함
    }

    size++;
    return;
}

// Pop 함수_ 큐에서 맨앞노드를 반환 (노드 제거)
SubtitleQueueNode* SubtitleQueue::Pop() {
    if (IsEmpty()) {
        std::cerr << "Error: Queue is empty!" << std::endl;
        exit(EXIT_FAILURE);  // 프로그램 종료
    }

    SubtitleQueueNode* temp = front;
    // 이거x
    // SubtitleQueueNode result = *front;  // 반환할 데이터를 저장

    front = front->getNext();
    //front = front->next; 

    //pop한 후 큐가 비었을 때
    if (front == nullptr) {
        rear = nullptr;  // 큐가 비었으면 rear도 nullptr로 설정
    }

    // 메모리 해제   delete temp; 필요없음?
    size--;

    return temp;
}

// 큐의 맨 앞 노드를 반환 (제거하지 x)
//반환형이 이게 맞나? 아니면 &ubtitleQueueNode SubtitleQueue or *SubtitleQueueNode SubtitleQueue ??
SubtitleQueueNode* SubtitleQueue::Front() {
    if (IsEmpty()) {
        std::cerr << "Error: Queue is empty!" << std::endl;
        exit(EXIT_FAILURE);  // 프로그램 종료
    }

    return front;  // front가 가리키는 노드 반환
}


/*
#include "SubtitleQueue.h"

SubtitleQueue::SubtitleQueue()
{

}
SubtitleQueue::~SubtitleQueue()
{

}

bool SubtitleQueue::IsEmpty()
{
	
}
bool SubtitleQueue::IsFull()
{
	
}
void SubtitleQueue::Push()
{
	
}
SubtitleQueueNode SubtitleQueue::Pop()
{
	
}
SubtitleQueueNode SubtitleQueue::Front()
{
	
}
*/