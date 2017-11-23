#include "Activiteit.h"
#include "TijdRegistratie.h"
#include <vector>
#include <string>

using namespace std;

CActiviteit::CActiviteit()
{}

CActiviteit::CActiviteit(string naam, signed int status, CDatum deadline, string notitie):CProjectActiviteit(naam,status,deadline,notitie)
{}

void CActiviteit::addTijdRegistratie(CTijdRegistratie registratie)
{
	if (this->getStatus() == 0)
		m_tijdsregistratie.push_back(registratie);
}

const vector<CTijdRegistratie>& CActiviteit::getTijdRegistraties() const
{
	return m_tijdsregistratie;
}

void CActiviteit::setActiviteit(CProjectActiviteit pactiviteit)
{
	setNaam(pactiviteit.getNaam());
	setStatus(pactiviteit.getStatus());
	setDeadLine(pactiviteit.getDeadLine());
	setNotitie(pactiviteit.getNotitie());
}

CTijdverschil CActiviteit::getTotaalTijd() const
{
	CTijdverschil tv = CTijdverschil(0,0, 0);

    for (signed int i = 0; i < m_tijdsregistratie.size(); i++)
		tv += m_tijdsregistratie[i].getTotaalTijd();

	return tv;
}

