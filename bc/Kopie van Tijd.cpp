#include "Tijd.h"
#include <strstream>

CTijd::CTijd()
{
	time_t tijd;
	time(&tijd);
	struct tm t = *localtime( &tijd );
	setvals(t.tm_hour, t.tm_min, t.tm_sec);
}

CTijd::CTijd(char * tijd)
{
	char t[7];
	t[0] = tijd[0];
	t[1] = tijd[1];
	t[2] = tijd[3];
	t[3] = tijd[4];
	t[4] = tijd[6];
	t[5] = tijd[7];
	t[6] = '\0';

	int i = atoi(t);
		setvals(i/1000000, (i%1000000)/10000,i%10000);
}

void CTijd::setvals(int h, int m, int s)
{
	m_hours = h;
	m_minutes = m;
	m_seconds = s;
}

char * CTijd::toString()
{
	strstream t;
	if (m_hours < 10)
		t << "0" << m_hours << ":";
	else
		t << m_hours << ":";
	if (m_hours < 10)
		t << "0" << m_hours << ":";
	else
		t << m_hours << ":";
	if (m_seconds < 10)
		t << "0" << m_seconds;
	else
		t << m_seconds;
	t << ends;

	return t.str();
}

signed int CTijd::getSeconden()
{
	return m_seconds;
}

signed int CTijd::getMinuten()
{
	return m_minutes;
}

signed int CTijd::getUren()
{
	return m_hours;
}