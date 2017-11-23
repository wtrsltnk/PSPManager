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
	string getNaam();
	void setNaam(string);

	signed int getStatus();
	void setStatus(signed int);
	
	CDatum getDeadLine();
	void setDeadLine(CDatum);

	string getNotitie();
	void setNotitie(string);

};
#endif