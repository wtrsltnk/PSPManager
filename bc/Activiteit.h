#ifndef CACTIVITEIT_H
#define CACTIVITEIT_H


#include "TijdRegistratie.h"
#include "ProjectActiviteit.h"
#include <vector>


class CActiviteit : public CProjectActiviteit
{
private:
	vector <CTijdRegistratie> m_tijdsregistratie;
public:
	CActiviteit();
	CActiviteit(string, signed int, CDatum, string);
	void addTijdRegistratie(CTijdRegistratie);
    const vector <CTijdRegistratie>& getTijdRegistraties() const;
	void setActiviteit(CProjectActiviteit);
    CTijdverschil getTotaalTijd() const;
};

#endif
