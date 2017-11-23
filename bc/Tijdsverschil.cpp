#include "tijdverschil.h"

CTijdverschil::CTijdverschil(unsigned int hours, unsigned int minutes, unsigned int seconds):m_hours(hours), m_minutes(minutes), m_seconds(seconds)
{
}

unsigned int CTijdverschil::getSeconden()
{
	return m_minutes;
}

unsigned int CTijdverschil::getMinuten()
{
	return m_minutes;
}

unsigned int CTijdverschil::getUren()
{
	return m_hours;
}

string CTijdverschil::toString()
{
    stringstream t;
	if (m_minutes < 10)
		t << m_hours << ":0"	<< m_minutes;
	else
		t << m_hours << ":"	<< m_minutes;
	if (m_seconds < 10)
		t << ":0"	<< m_seconds << ends;
	else
		t << ":"	<< m_seconds << ends;
    return t.str();
}

const CTijdverschil operator + (const CTijdverschil& t1, const CTijdverschil& t2)
{
	signed int totsec = 0;
	totsec += t1.m_seconds + t1.m_minutes * 60 + t1.m_hours * 3600;
	totsec += t2.m_seconds + t2.m_minutes * 60 + t2.m_hours * 3600;

	return CTijdverschil(totsec/3600, (totsec%3600)/60, totsec%60);
	
}

void CTijdverschil::operator += (const CTijdverschil& t2)
{
	signed int totsec = 0;
	totsec += this->m_seconds + this->m_minutes * 60 + this->m_hours * 3600;
	totsec += t2.m_seconds + t2.m_minutes * 60 + t2.m_hours * 3600;

	this->m_hours = totsec/3600;
	this->m_minutes = (totsec%3600)/60;
	this->m_seconds = totsec%60;

}
