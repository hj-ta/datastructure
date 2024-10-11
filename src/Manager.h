#pragma once
#include "SubtitleQueue.h"
#include "SubtitleBST.h"
#include "SectionList.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Manager
{
private:

	ifstream		fcmd;
	ofstream		flog;
	SubtitleQueue* ManagerQueue;
	SubtitleBST* subtitleBST;
	SectionList* sectionList; // SectionList 객체


public:
	Manager();
	~Manager();

	void Run(const char* command);

	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);


	// LOAD
	void LoadSubtitle();
	
	void PrintQueueContents();

	// QPOP
	void QPOP();

	// PRINT
	void Print(const vector<string>& v);

	// SECTION
	void Section(const vector<string>& v);
	
	// DELETE
	void Delete(const vector<string>& v);

};
