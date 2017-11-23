#ifndef CSUPERMANAGER_H
#define CSUPERMANAGER_H

#include "ProjectManager.h"
#include "XMLManager.h"

class CSuperManager
{
private:
	CProjectManager m_pm;
	CXMLManager m_xm;
public:
	CSuperManager();
	void addProject(CProject);
	CProject * getProject(string);
	void setProject(CProjectActiviteit);
	bool removeProject(string);
	vector<CProject> getProjecten();

	void addActiviteit(string, CActiviteit);
	CActiviteit * getActiviteit(string, string);
	void setActiviteit(string, CProjectActiviteit);
	bool removeActiviteit(string, string);
	vector<CActiviteit> * getActiviteiten(string);

	void addTijdRegistratie(string, string, CTijdRegistratie);
	CTijdverschil * getTotaalTijd(string);
	CTijdverschil * getTotaalTijd(string, string);

	bool readXML(string);
	bool importXML(string);
	bool saveXML();
	bool saveXML(string);
	bool exportXML(string);

	void setXMLPath(string);
	string getXMLPath();
};

#endif