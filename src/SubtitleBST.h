#pragma once
#include "SubtitleBSTNode.h"
#include <string>
#include "SubtitleListNode.h"
//이거 왜....?

using namespace std;

class SubtitleBST
{
private:
	SubtitleBSTNode* root;

	// 재귀적으로 노드를 삽입하는 함수
	SubtitleBSTNode* InsertNode(SubtitleBSTNode* node, string time, string content);

	// 재귀적으로 트리를 중위 순회하면서 출력하는 함수
	void InOrderPrint(SubtitleBSTNode* node, ofstream& flog);

	// 재귀적으로 특정 자막 시간을 탐색하는 함수
	SubtitleBSTNode* SearchNode(SubtitleBSTNode* node, string time);

	// 재귀적으로 노드를 삭제하는 함수
	SubtitleBSTNode* DeleteNode(SubtitleBSTNode* node, string time);

	// 오른쪽 서브트리에서 최소값을 찾는 함수
	SubtitleBSTNode* FindMin(SubtitleBSTNode* node);

	// 트리의 모든 노드를 삭제하는 함수
	void DestroyTree(SubtitleBSTNode* node);

	// 재귀적으로 시간 범위 내 노드를 탐색하는 헬퍼 함수
	bool FindNodesInRangeHelper(SubtitleBSTNode* node, string startTime, string endTime, SubtitleListNode*& contentHead, SubtitleListNode*& lastContentNode);


	//DELETE 때 필요한건데 뭔지 모르겠음
	//특정 시간보다 이전인 자막 시간을 가진 노드들을 삭제하는 재귀적 헬퍼 함수
	//DeleteNodesUnderHelper 함수는 재귀적으로 내부에서만 사용되므로 private 영역도 ok
	SubtitleBSTNode* DeleteNodesUnderHelper(SubtitleBSTNode* node, string targetTime, bool& found);


public:
	SubtitleBST();
	~SubtitleBST();

	//루트노드를 반환하는 게터임, 세터는 왜 필요없지?
	SubtitleBSTNode* getRoot();

	//insert 함수 (트리에 새로운 노드 삽입)
	void Insert(string time, string content);


	//Print 함수 (트리를 중위순휘 하며 출력)
	void Print(ofstream& flog);
	//void Print();

	//Search 함수? _특정노드를 찾는 함수 (특정 자막시간 기준)
	SubtitleBSTNode* Search(string time);

	//Delete 함수 _ 특정 자막시간을 가진 노드를 삭제
	void Delete(string time);

	//특정 시간보다 이전인 자막 시간을 가진 노드들을 삭제하는 함수
	//(이 함수는 외부에서 접근해야 하기 때문에 public 으로 선언해야됨 ㅠ 이거때매 오류 ㅅㅂ)
	//bool DeleteNodesUnder(string targetTime);

	// 시간 범위 내에 있는 노드를 찾는 함수
	bool FindNodesInRange(string startTime, string endTime, SubtitleListNode*& contentHead, SubtitleListNode*& lastContentNode);


	// Insert
	// Print
	// Search
	// Delete
};
