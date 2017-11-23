#include "Supermanager.h"

CSuperManager::	CSuperManager()
{
}

void CSuperManager::addProject(CProject project)
{
	m_pm.addProject(project);
}

CProject * CSuperManager::getProject(string id)
{
	return m_pm.getProject(id);
}

void CSuperManager::setProject(CProjectActiviteit project)
{
	m_pm.setProject(project);
}

bool CSuperManager::removeProject(string id)
{
	return m_pm.removeProject(id);
}

vector<CProject> CSuperManager::getProjecten()
{
	return m_pm.getProjecten();
}

void CSuperManager::addActiviteit(string project, CActiviteit activiteit)
{
	CProject * p = m_pm.getProject(project);
	if (p != NULL)
		p->addActiviteit(activiteit);
}

CActiviteit * CSuperManager::getActiviteit(string project, string activiteit)
{
	CProject * p = m_pm.getProject(project);
	if (p != NULL)
		return p->getActiviteit(activiteit);
	else
		return NULL;
}

void CSuperManager::setActiviteit(string project, CProjectActiviteit activiteit)
{
	CProject * p = m_pm.getProject(project);
	if (p != NULL)
		p->setActiviteit(activiteit);
}

bool CSuperManager::removeActiviteit(string project, string activiteit)
{
	CProject * p = m_pm.getProject(project);
	if (p != NULL)
		return p->removeActiviteit(activiteit);
	else
		return false;
}

vector<CActiviteit> CSuperManager::getActiviteiten(string project)
{
	CProject * p = m_pm.getProject(project);
	if (p != NULL)
        return (p->getActiviteiten());
    return vector<CActiviteit>();
}

void CSuperManager::addTijdRegistratie(string project, string activiteit, CTijdRegistratie tijdregistratie)
{
	CProject * p = m_pm.getProject(project);
	if (p != NULL)
	{
		CActiviteit * a = p->getActiviteit(activiteit);
		if (a != NULL)
			a->addTijdRegistratie(tijdregistratie);
	}
}

CTijdverschil CSuperManager::getTotaalTijd(string project)
{
	CProject * p = m_pm.getProject(project);
	if (p != NULL)
        return (p->getTotaalTijd());
    return CTijdverschil(0, 0, 0);
}

CTijdverschil CSuperManager::getTotaalTijd(string project, string activiteit)
{
	CProject * p = m_pm.getProject(project);
	if (p != NULL)
	{
		CActiviteit * a = p->getActiviteit(activiteit);
		if (a != NULL)
            return (a->getTotaalTijd());
	}
    return CTijdverschil(0, 0, 0);
}

bool CSuperManager::readXML(string filename)
{
	return m_xm.readXML(filename, false, m_pm);
}

bool CSuperManager::importXML(string filename)
{
	return m_xm.readXML(filename, true, m_pm);
}

bool CSuperManager::saveXML()
{
	return m_xm.saveXML(m_pm);
}

bool CSuperManager::saveXML(string filename)
{
	return m_xm.saveXML(filename, false, m_pm);
}

bool CSuperManager::exportXML(string filename)
{
	return m_xm.saveXML(filename, true, m_pm);
}

void CSuperManager::setXMLPath(string filename)
{
	m_xm.setXMLPath(filename);
}

//nieuwe functie
string CSuperManager::getXMLPath()
{
	return m_xm.getXMLPath();
}
