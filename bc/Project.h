#ifndef CPROJECT_H
#define CPROJECT_H


#include <vector>
#include "Activiteit.h"

using namespace std;

class CProject : public CProjectActiviteit
{
private:
	vector <CActiviteit> m_activiteit;
public:
	CProject();
	CProject(string, signed int, CDatum, string);
	void addActiviteit(CActiviteit);
	CActiviteit * getActiviteit(string);
	void setActiviteit(CProjectActiviteit);
	bool removeActiviteit(string);
    const vector<CActiviteit>& getActiviteiten() const;
	void setProject(CProjectActiviteit);
    CTijdverschil getTotaalTijd() const;
};
#endif
