#include "ProjectActiviteit.h"
using namespace std;

CProjectActiviteit::CProjectActiviteit()
{}

CProjectActiviteit::CProjectActiviteit(string naam, signed int status, CDatum deadline, string notitie)
{
	m_naam = naam;
	m_status = status;
	m_deadline = deadline;
	m_notitie = notitie;
}

string CProjectActiviteit::getNaam() const
{
	return m_naam;
}

void CProjectActiviteit::setNaam(string naam)
{
	m_naam = naam;
}

CProjectActiviteit::getStatus() const
{
	return m_status;
}

void CProjectActiviteit::setStatus(int status)
{
	m_status = status;
}

string CProjectActiviteit::getNotitie() const
{
	return m_notitie;
}

void CProjectActiviteit::setNotitie(string notitie)
{
	m_notitie = notitie;
}


CDatum CProjectActiviteit::getDeadLine() const
{
	return m_deadline;
}

void CProjectActiviteit::setDeadLine(CDatum dl)
{
	m_deadline = dl;
}





	
