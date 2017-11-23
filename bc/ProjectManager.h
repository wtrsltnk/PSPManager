#ifndef CPROJECTMANAGER_H
#define CPROJECTMANAGER_H

//#include "Project.h"
#include <vector>
#include "ProjectActiviteit.h"
#include "Project.h"
#include <string>
#include <windows.h>

using namespace std;

class CProjectManager 
{
private:
	vector <CProject> m_data;

public:
	void addProject(CProject);
	CProject * getProject(string);
	void setProject(CProjectActiviteit);
	bool removeProject(string);
	vector<CProject> getProjecten();
};

#endif


