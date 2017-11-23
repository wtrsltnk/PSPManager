#ifndef CTIJD_H
#define CTIJD_H

#include <time.h>
#include <string>
using namespace std;

class CTijd
{

private:
	signed int m_hours;
	signed int m_minutes;
	signed int m_seconds;
	char tmp[9];
	void setvals(int, int, int);

public:
	CTijd();
	CTijd(char * tijd);
    signed int getUren() const;
    signed int getMinuten() const;
    signed int getSeconden() const;
    char * toString() const;
};

#endif
