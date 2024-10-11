#pragma once

#include <string>

using namespace std;

class SubtitleBSTNode
{
private:

	string time;
	string content;
	//SubtitleQueueNode* time;
	//SubtitleQueueNode* content;
	//이렇게 하면 왜 안됨?

	SubtitleBSTNode*	left;
	SubtitleBSTNode*	right;

	//time,content 받아야됨 , 큐를 받는다 or 큐 안의 time,content 데이터만 추출해서 받는게 가능?

public:
	//기본생성자
	SubtitleBSTNode() : left(nullptr), right(nullptr) {}

	//생성자 하나하나 초기화 필요한가?
	/*
	SubtitleBSTNode(string time, string content)
        : time(time), content(content), left(nullptr), right(nullptr) {}
	*/

	//소멸자
	~SubtitleBSTNode() {}

	SubtitleBSTNode*	getLeft()				{ return left; }
	SubtitleBSTNode*	getRight()				{ return right; }

	void setLeft(SubtitleBSTNode* left)		{ this->left = left; }
	void setRight(SubtitleBSTNode* right)	{ this->right = right; }


	string getTime() { return time; } 
	string getContent() { return content; }

	void setTime(string time) { this->time = time; }
	void setContent(string content) { this->content = content; }


};
