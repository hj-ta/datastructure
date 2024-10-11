#include <sstream>
#include "Manager.h"

using namespace std;

Manager::Manager()
{
    ManagerQueue = new SubtitleQueue();
    subtitleBST = new SubtitleBST();
    sectionList = new SectionList();
}
Manager::~Manager()
{
    //??
    delete ManagerQueue;
}

void Manager::Run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    string cmdBuffer;

    while (getline(fcmd, cmdBuffer)) {
        istringstream iss(cmdBuffer);
        string cmd;
        vector<string> v;

        //명령어를 공백으로 분리하고 벡터에 저장
        while (iss >> cmd) {
            v.push_back(cmd);
        }

        //명령어 확인하고 맞는 동작 실행
        //LOAD
        if (v[0] == "LOAD") {
            LoadSubtitle();
        }
        //QPOP
        else if (v[0] == "QPOP") {
            QPOP();
        }
        //PRINT
        else if (v[0] == "PRINT") {
            Print(v);
        }
        //SECTION
        else if (v[0] == "SECTION") {
            Section(v);
        }
        //DELETE
        else if (v[0] == "DELETE") {
            Delete(v);
        }
        //
        else {

        }




    }

    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============\n" << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============\n" << endl;
}

// LOAD
// LOAD 명령어를 처리하는 함수
void Manager::LoadSubtitle() {
    ifstream fdata("subtitle.txt");

    if (!fdata.is_open()) {
        // subtitle.txt 파일을 열지 못했을 경우 에러 처리
        PrintErrorCode(100);  // LOAD 관련 에러 코드 100
        return;
    }

    string line;
    while (getline(fdata, line)) {
        istringstream iss(line);
        string time;
        string content;

        //iss >> time >> content;
        
        //시간 먼저 읽고
        iss >> time;

        //공백을 포함한 자막 내용 전체 다 읽음
        getline(iss, content);


        // content의 앞뒤 공백 제거
        if (!content.empty() && content[0] == ' ') {
            content.erase(0, 1); // 앞에 있는 공백 제거
        }
        //content = content.substr(content.find_first_not_of(" "), content.find_last_not_of(" ") - content.find_first_not_of(" ") + 1);
        //공백제거 굳이 필요한가?


        // 큐에 자막 시간과 내용을 푸시
        ManagerQueue->Push(time, content);
    }

    fdata.close();

    //큐에 담긴 내용 출력
    PrintQueueContents();
    //PrintSuccess("LOAD");
}

void Manager::PrintQueueContents() {
    SubtitleQueueNode* current = ManagerQueue->Front(); // 큐의 맨 앞 노드를 가져옴
    flog << "========= LOAD =========" << endl;

    while (current != nullptr) {
        flog << current->getTime() << " - " << current->getContent() << endl;
        current = current->getNext(); // 다음 노드로 이동
    }

    flog << "=========================\n" << endl;
}

////////////////// QPOP////////////////////
// QPOP 명령어를 처리하는 함수
void Manager::QPOP() {
    // SubtitleQueue에 데이터가 존재하지 않을 경우 에러 처리
    if (ManagerQueue->IsEmpty()) {
        PrintErrorCode(200);  // QPOP 관련 에러 코드 200 출력
        return;
    }

    // SubtitleQueue에서 모든 노드를 POP하여 subtitleBST에 삽입
    while (!ManagerQueue->IsEmpty()) {
        SubtitleQueueNode* node = ManagerQueue->Pop();  // 큐의 맨 앞 노드 POP
        if (node != nullptr) {
            subtitleBST->Insert(node->getTime(), node->getContent());  // BST에 데이터 삽입
            delete node;  // 메모리 해제
        }
    }

    // 성공 메시지 출력
    PrintSuccess("QPOP");
}

// /////////PRINT///////////////////
void Manager::Print(const vector<string>& v) {
    if (v.size() == 1) {  // PRINT 명령어만 입력된 경우
        if (subtitleBST->getRoot() == nullptr) {
            PrintErrorCode(300);  // BST가 비어 있을 때 에러 코드 300 출력
            return;
        }
        flog << "===== PRINT =====" << endl;
        subtitleBST->Print(flog);  // Subtitle_BST 중위 순회하여 출력
        flog << "===============" << endl;
    }
    else if (v.size() == 2) {  // PRINT <section_number> 형식인 경우
        int sectionNumber = stoi(v[1]); //std::앞에 있었음
        SectionListNode* section = sectionList->findSection(sectionNumber);
        if (section == nullptr) {
            PrintErrorCode(300);  // 섹션 번호가 존재하지 않을 때 에러 코드 300 출력
            return;
        }
        flog << "===== PRINT =====" << endl;
        flog << "Section " << sectionNumber << endl;
        SubtitleListNode* content = section->getContentHead();
        while (content != nullptr) {
            flog << content->getTime() << " - " << content->getContent() << endl;
            content = content->getNext();
        }
        flog << "===============" << endl;
    }
}

////////////// SECTION///////////
// SECTION 명령어를 처리하는 함수
void Manager::Section(const vector<string>& v) {
    // SECTION 명령어의 인자 검증
    if (v.size() != 4) {  // 올바른 형식이 아닌 경우
        PrintErrorCode(400);  // SECTION 관련 에러 코드 400 출력
        return;
    }

    int sectionNumber = stoi(v[1]);  // 첫 번째 인자는 섹션 번호
    string startTime = v[2];  // 두 번째 인자는 탐색 시작 시간
    string endTime = v[3];    // 세 번째 인자는 탐색 종료 시간

    // 새로운 섹션 헤더 노드 생성
    SubtitleListNode* contentHead = nullptr;
    SubtitleListNode* lastContentNode = nullptr;

    // BST에서 시간 범위에 맞는 노드를 탐색하여 연결 리스트로 만듦
    bool foundNodes = subtitleBST->FindNodesInRange(startTime, endTime, contentHead, lastContentNode);

    if (!foundNodes) {  // 탐색된 노드가 없을 경우
        PrintErrorCode(400);  // SECTION 관련 에러 코드 400 출력
        return;
    }

    // sectionList에 새로운 섹션 추가
    sectionList->addSection(sectionNumber, contentHead);

    // 성공 메시지 출력
    PrintSuccess("SECTION");
}

//////////////DELETE//////////
// DELETE 명령어를 처리하는 함수
void Manager::Delete(const vector<string>& v) {
    if (v.size() < 3) {  // 인자의 개수가 올바르지 않을 경우
        PrintErrorCode(500);  // DELETE 관련 에러 코드 500 출력
        return;
    }

    string option = v[1];
    string targetTime = v[2];

    // BST가 비어 있는지 확인
    if (subtitleBST->getRoot() == nullptr) {
        PrintErrorCode(500);  // BST가 비어 있을 때 에러 코드 500 출력
        return;
    }

    if (option == "EQUAL") {  // DELETE EQUAL 명령어 처리
        SubtitleBSTNode* targetNode = subtitleBST->Search(targetTime);
        if (targetNode == nullptr) {
            PrintErrorCode(500);  // 특정 자막 시간이 존재하지 않을 때 에러 코드 500 출력
            return;
        }
        subtitleBST->Delete(targetTime);
        PrintSuccess("DELETE");
    }
    else if (option == "UNDER") {  // DELETE UNDER 명령어 처리
        //bool found = subtitleBST.DeleteNodesUnder(targetTime);
        //if (!found) {
        //    PrintErrorCode(500);  // 특정 자막 시간이 존재하지 않을 때 에러 코드 500 출력
        //    return;
        //}
        //PrintSuccess("DELETE");
    }
    else {
        PrintErrorCode(500);  // 올바르지 않은 옵션이 입력된 경우 에러 코드 500 출력
    }
}







    /*
    while (fcmd >> cmd) {
        if (cmd == "LOAD") {
            LoadSubtitle();
        }
        else {//or else if
            PrintErrorCode(1000);
            exit(-1);
            //error code 100
        }
    }
    */


    /*
    if (LoadSubtitle() = false) { //==
        PrintErrorCode(100);

    }
    else if (qpop = false) {
        PrintErrorCode(200);
    }
    else {
        //exit?
    }
    */

    // Read and Run command
