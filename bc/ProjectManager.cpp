#include "Project.h"
#include "ProjectManager.h"
#include <string>
#include <vector>

using namespace std;

CProject * CProjectManager::getProject(string pnaam)
{
	for (int i = 0; i < m_data.size(); i++)
		if (stricmp((m_data[i].getNaam().c_str()), pnaam.c_str()) == 0)
			return &m_data[i];

	return NULL;
}


void CProjectManager::addProject(CProject project)
{
	if (getProject(project.getNaam()) == NULL)
		m_data.push_back(project);
}


void CProjectManager::setProject(CProjectActiviteit data)
{
	
	for (int i = 0; i < m_data.size(); i++)
		if (stricmp(m_data[i].getNaam().c_str(),data.getNaam().c_str()) == 0)
			m_data[i].setProject(data);
}

vector<CProject> CProjectManager::getProjecten()
{
	return m_data;
}

bool CProjectManager::removeProject(string pnaam)
{
	for (int i = 0; i < m_data.size(); i++)
		if (stricmp((m_data[i].getNaam().c_str()), pnaam.c_str()) == 0)
		{
			m_data.erase(m_data.begin() + i);
			return true;
		}

		return false;
}


