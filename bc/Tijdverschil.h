#ifndef CTIJDVERSCHIL_H
#define CTIJDVERSCHIL_H

#include "tijd.h"
#include <strstream>

class CTijdverschil
{

public:
	unsigned int m_hours;
	unsigned int m_minutes;
	unsigned int m_seconds;
	char tmp[6];

public:
	unsigned int getUren();
	unsigned int getMinuten();
	unsigned int getSeconden();

	CTijdverschil(unsigned int, unsigned int, unsigned int);
	char * toString();
	void operator+=(const CTijdverschil t2);
	friend const CTijdverschil operator +(CTijdverschil t1, CTijdverschil t2);
};

#endif