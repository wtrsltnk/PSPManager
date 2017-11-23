#include "Datum.h"
#include <iostream>
#include <sstream>

using namespace std;

CDatum::CDatum()
{
	time_t datum;
	time(&datum);
	struct tm t = *localtime( &datum );
	setvals(t.tm_mday, t.tm_mon+1, t.tm_year+1900);
}

CDatum::CDatum(char * tijd)
{
	char t[8];
	t[0] = tijd[0];
	t[1] = tijd[1];
	t[2] = tijd[3];
	t[3] = tijd[4];
	t[4] = tijd[6];
	t[5] = tijd[7];
	t[6] = tijd[8];
	t[7] = tijd[9];
	t[8] = '\0';
	int i = atoi(t);
	setvals(i/1000000, (i%1000000)/10000,i%10000);
}

void CDatum::setvals(int d, int m, int y)
{
	m_years = y;
	m_months = m;
	m_days = d;
}

string  CDatum::toString() const
{
    stringstream t;
	if (m_days < 10)
		t << "0" << m_days << "-";
	else
		t << m_days << "-";
	if (m_months < 10)
		t << "0" << m_months << "-";
	else
		t << m_months << "-";
	if (m_years < 10)
		t << "0" << m_years;
	else
		t << m_years;
	t << ends;

	return t.str();
}

signed int CDatum::getDagen() const
{
	return m_days;
}

signed int CDatum::getMaanden() const
{
	return m_months;
}

signed int CDatum::getJaren() const
{
	return m_years;
}

signed int CDatum::getTotaaldagen() const
{
	signed int jaar[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	signed int d = m_days;
	for (int i =0; i<m_months-1; i++)
		d += jaar[i];

	d += 365 * m_years + m_years/4;

	return d;
}

void CDatum::setDatum(int dag, int maand, int jaar)
{
	// HIER GAAT PATRICK STRAKS FF DE DATUM CONTROLEREN. :-P
	
	setvals(dag, maand, jaar);
}

bool CDatum::operator <(CDatum d2)
{
	if (d2.m_years <= m_years && d2.m_months <= m_months && (d2.m_days + 1) <= m_days)
		return true;

/*	
	if (d2.m_years < m_years)
		return true;
	if (d2.m_months < m_months)
		return true;
	if (d2.m_days < m_days)
		return true;
*/
  
	return false;
}
