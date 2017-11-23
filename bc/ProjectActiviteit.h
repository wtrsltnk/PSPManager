#ifndef CPROJECTACTIVITEIT_H
#define CPROJECTACTIVITEIT_H

#include <string>
#include "Tijd.h"
#include "Datum.h"
using namespace std;

class CProjectActiviteit
{
protected:
	string m_naam;
	signed int m_status;
	CDatum m_deadline;
	string m_notitie;
public:
	CProjectActiviteit();
	CProjectActiviteit(string, signed int, CDatum, string);
    string getNaam() const;
	void setNaam(string);

    signed int getStatus() const;
	void setStatus(signed int);
	
    CDatum getDeadLine() const;
	void setDeadLine(CDatum);

    string getNotitie() const;
	void setNotitie(string);

};
#endif
