#ifndef CDATUM_H
#define CDATUM_H

#include <time.h>
#include <string>
using namespace std;

class CDatum
{

private:
	signed int m_years;
	signed int m_months;
	signed int m_days;
	void setvals(int, int, int);

public:
	CDatum();
	CDatum(char * datum);
	signed int getDagen();
	signed int getMaanden();
	signed int getJaren();
	signed int getTotaaldagen();
	char * toString();
	void setDatum(int, int, int);
	bool operator <(const CDatum);
};

#endif