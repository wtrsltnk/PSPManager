#include "Project.h"
#include <string>
#include <string.h>
#include <vector>
#include <iostream>
using namespace std;

CProject::CProject():CProjectActiviteit()
{}

CProject::CProject(string naam, signed int status, CDatum deadline, string notitie):CProjectActiviteit(naam,status,deadline,notitie)
{}

void CProject::addActiviteit(CActiviteit activiteit)
{
	if (getActiviteit(activiteit.getNaam()) == NULL)
		if (this->getStatus() == 0)
			m_activiteit.push_back(activiteit);
}

CActiviteit * CProject::getActiviteit(string anaam)
{
	for (int i = 0; i < m_activiteit.size(); i++)
		if (stricmp((m_activiteit[i].getNaam().c_str()), anaam.c_str()) == 0)
			return &m_activiteit[i];

	return NULL;
}

void CProject::setActiviteit(CProjectActiviteit data)
{
	for (int i = 0; i < m_activiteit.size(); i++)
		if (stricmp((m_activiteit[i].getNaam().c_str()), data.getNaam().c_str()) == 0)
		{
			m_activiteit[i].setNaam(data.getNaam());
			m_activiteit[i].setNotitie(data.getNotitie());
			m_activiteit[i].setStatus(data.getStatus());
			m_activiteit[i].setDeadLine(data.getDeadLine());

		}
	
	
}

bool CProject::removeActiviteit(string anaam)
{
	for ( int i = 0; i < m_activiteit.size(); i++)
		if (stricmp((m_activiteit[i].getNaam().c_str()), anaam.c_str()) == 0)
		{
			 m_activiteit.erase(m_activiteit.begin() + i);
			return true;
		}
	return false;
}

const vector<CActiviteit>& CProject::getActiviteiten() const
{
	return m_activiteit;
}

void CProject::setProject(CProjectActiviteit projectactiviteit)
{
	setNaam(projectactiviteit.getNaam());
	setStatus(projectactiviteit.getStatus());
	setDeadLine(projectactiviteit.getDeadLine());
	setNotitie(projectactiviteit.getNotitie());
}

CTijdverschil CProject::getTotaalTijd() const
{
	CTijdverschil tv = CTijdverschil(0, 0, 0);
	for (signed int i = 0; i < m_activiteit.size(); i++)
		tv += m_activiteit[i].getTotaalTijd();

	return tv;
}



	




	


