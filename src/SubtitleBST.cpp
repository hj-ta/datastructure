#include "SubtitleBST.h"
#include "SubtitleListNode.h"

#include <iostream>
#include <fstream> //이거 필요?

using namespace std;

//생성자 안에는 비워도 되나?
SubtitleBST::SubtitleBST() : root(nullptr) {}

SubtitleBST::~SubtitleBST(){
	DestroyTree(root);
}

// 재귀적으로 트리의 모든 노드를 삭제하는 함수
void SubtitleBST::DestroyTree(SubtitleBSTNode* node) {
    if (node != nullptr) {
        DestroyTree(node->getLeft());
        DestroyTree(node->getRight());
        delete node;
    }
}

//루트 노드를 반환하는 함수
SubtitleBSTNode* SubtitleBST::getRoot()  {
	return root;
}

// Insert
// _ 트리에 새로운 자막 데이터를 삽입한는 함수
void SubtitleBST::Insert(string time, string content) {
    root = InsertNode(root, time, content);
}

//재귀적으로 트리에 노드 삽입
SubtitleBSTNode* SubtitleBST::InsertNode(SubtitleBSTNode* node, string time, string content) {
    if (node == nullptr) {
        //새로운 노드를 생성하고
        SubtitleBSTNode* newNode = new SubtitleBSTNode();
        // or new SubtitleBSTNode(time, content);????

        //set으로 데이터 입력? 삽입?
        newNode->setTime(time);
        newNode->setContent(content);
        
        return newNode;
    }

    //자막 시간에 따라 왼쪽 또는 오른쪽 서브트리에 삽입
    //new노드의 시간이 현재 노드의 시간보다 작으면 왼쪽에 생성 후 삽입
    if (time < node->getTime()) {
        node->setLeft(InsertNode(node->getLeft(), time, content));
    }
    //new노드의 시간이 현재 노드의 시간보다 크면 오른쪽에 생성 후 삽입
    else {
        node->setRight(InsertNode(node->getRight(), time, content));
    }
    return node;
}

// 특정시간 범위에 해당하는 노드를 탐색하고 그 결과를 SubtitleListNode 로 연결하는 기능을 하는 함수들
//범위 내에 노드를 찾기 위한 진입점 _FindNodesInRangeHelper를 호줄하는 역할
bool SubtitleBST::FindNodesInRange(string startTime, string endTime, SubtitleListNode*& contentHead, SubtitleListNode*& lastContentNode) {
    return FindNodesInRangeHelper(root, startTime, endTime, contentHead, lastContentNode);
}

//BST 를 재귀적으로 탐색하고 시간 범위에 해당하는 노드를 찾은 후 ,
//해당 노드를 SubtitleListNode 형태로 연결
bool SubtitleBST::FindNodesInRangeHelper(SubtitleBSTNode* node, string startTime, string endTime, SubtitleListNode*& contentHead, SubtitleListNode*& lastContentNode) {
    if (node == nullptr) {
        return false;
    }

    bool found = false;

    // 왼쪽 서브트리 탐색
    if (startTime <= node->getTime()) {
        found = FindNodesInRangeHelper(node->getLeft(), startTime, endTime, contentHead, lastContentNode) || found;
    }

    // 현재 노드가 시간 범위 내에 있는 경우
    if (startTime <= node->getTime() && node->getTime() <= endTime) {
        SubtitleListNode* newNode = new SubtitleListNode(node->getTime(), node->getContent());
        if (contentHead == nullptr) {
            contentHead = newNode;
        }
        else {
            lastContentNode->setNext(newNode);
        }
        lastContentNode = newNode;
        found = true;
    }

    // 오른쪽 서브트리 탐색
    if (endTime >= node->getTime()) {
        found = FindNodesInRangeHelper(node->getRight(), startTime, endTime, contentHead, lastContentNode) || found;
    }

    return found;
}

// //////Print
//트리의 데이터를 중위 순회 방식으로 출력하는 함수_실행함수
void SubtitleBST::Print(ofstream& flog) {
    InOrderPrint(root,flog);
}

//재귀적으로 트리를 중위 순회 하면서 출력하는 함수_재귀함수
void SubtitleBST::InOrderPrint(SubtitleBSTNode* node, ofstream& flog) {
    //BST 가 비어있는 경우, 종료조건
    if (node == nullptr) return;

    //시간순으로 출력
    InOrderPrint(node->getLeft(),flog);
    flog << node->getTime() << " - " << node->getContent() << endl;
    InOrderPrint(node->getRight(),flog);
}

// /////////Search
//특정 시간를 인자로 받아 search 실행하는 함수
SubtitleBSTNode* SubtitleBST::Search(string time) {
    return SearchNode(root, time); //bst.h 에서
}

//재귀적으로 seach 하는 함수_특정시간 기준으로
SubtitleBSTNode* SubtitleBST::SearchNode(SubtitleBSTNode* node, string time) {
    //재귀함수 종료조건_bst가 비어있거나(?), 찾았을 때
    if (node == nullptr || node->getTime() == time) {
        return node;  //현재 노드를 반환
    }

    //찾고자하는 특정시간이 현재 노드의 시간보다 작다면, 
    // 왼쪽으로 다시 search 보냄
    if (time < node->getTime()) {
        return SearchNode(node->getLeft(), time);
    }
    //~~ 크다면 현재노드의 오른쪽에서 seach 보냄
    else {
        return SearchNode(node->getRight(), time);
    }
}

////////// Delete
//특정시간을 인자로 받고 해당하는 노드 삭제 실행 하는 함수
void SubtitleBST::Delete(string time) {
    //실행
    root = DeleteNode(root, time);
}

//재귀적으로 트리를 순회하고 노드를 삭제하는 함수
SubtitleBSTNode* SubtitleBST::DeleteNode(SubtitleBSTNode* node, string time) {
    //종료조건
    if (node == nullptr) return node;

    //특정 시간 노드가 더 작을때
    if (time < node->getTime()) {
        node->setLeft(DeleteNode(node->getLeft(), time));
    }
    //특정 시간 노드가 더 클 때
    else if (time > node->getTime()) {
        node->setRight(DeleteNode(node->getRight(), time));
    }
    //삭제할 노드를 찾았을 때
    else {
        //case1 : node의 right 자식 노드만 존재할때,left node 존재x
        if (node->getLeft() == nullptr) {
            SubtitleBSTNode* temp = node->getRight();
            delete node;
            return temp;
        }
        //case2 : node 의 left 자식 노드만 존재할 때
        else if (node->getRight() == nullptr) {
            SubtitleBSTNode* temp = node->getLeft();
            delete node;
            return temp;
        }

        //case 3: 양쪽 자식 노두 모두 존재할 때_오른쪽 서브트리에서 최소값 찾기
        //////////////(아니면 왼쪽 서브트리에서 가장 큰값 찾아야됨)
       //최소값 찾아서 temp에 저장
        SubtitleBSTNode* temp = FindMin(node->getRight());

        //대체할 노드(temp)를 삭제된 노드의 자리로 가져옴
        node->setTime(temp->getTime());
        node->setContent(temp->getContent());

        //왼쪽 서브트리를 대체할 노드와 연결해야하나????
        //node->setLeft(node->getLeft());

        //temp를 삭제할 노드의 위치로 데려오고, 기존 오른쪽 서브트리와 연결
        node->setRight(DeleteNode(node->getRight(), temp->getTime()));

        //노드를 삭제하고 서브트리와 연결한 후 , temp를 서브트리에서 지우는 로직?

    }
    return node;
}

//DELETE 로 메모리 해제??
//오른쪽 서브트리에서 최소값을 찾는 함수
SubtitleBSTNode* SubtitleBST::FindMin(SubtitleBSTNode* node) {
    while (node->getLeft() != nullptr) { //왼쪽 자식이 없으면 , 해당노드가 최소
        node = node->getLeft();
    }
    return node; //이 노드가 삭제할 노드를 대체 할 것임
}

// 특정 시간보다 이전인 자막 시간을 가진 노드들을 삭제하는 재귀적 헬퍼 함수
SubtitleBSTNode* SubtitleBST::DeleteNodesUnderHelper(SubtitleBSTNode* node, string targetTime, bool& found) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->getTime() < targetTime) {
        found = true;
        SubtitleBSTNode* rightSubtree = node->getRight();
        delete node;
        return DeleteNodesUnderHelper(rightSubtree, targetTime, found);
    }

    node->setLeft(DeleteNodesUnderHelper(node->getLeft(), targetTime, found));
    return node;
}