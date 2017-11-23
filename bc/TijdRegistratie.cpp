#include "TijdRegistratie.h"

CTijdRegistratie::CTijdRegistratie()
{
	m_startdatum = CDatum();
	m_stopdatum = m_startdatum;
	m_starttijd = CTijd();
	m_stoptijd = m_starttijd;
}


CTijdRegistratie::CTijdRegistratie(CTijd &start_t, CTijd &stop_t, CDatum &start_d, CDatum &stop_d):m_starttijd(start_t), m_stoptijd(stop_t), m_startdatum(start_d), m_stopdatum(stop_d)
{
}

CTijd CTijdRegistratie::getStartTijd()
{
	return m_starttijd;
}

CTijd CTijdRegistratie::getStopTijd()
{
	return m_stoptijd;
}

CDatum CTijdRegistratie::getStartDatum()
{
	return m_startdatum;
}

CDatum CTijdRegistratie::getStopDatum()
{
	return m_stopdatum;
}

CTijdverschil CTijdRegistratie::getTotaalTijd()
{
	signed int stop = (m_stoptijd.getSeconden() + m_stoptijd.getMinuten() * 60 + m_stoptijd.getUren()*3600 + m_stopdatum.getTotaaldagen() * 86400);
	signed int start = (m_starttijd.getSeconden() + m_starttijd.getMinuten() * 60+ m_starttijd.getUren()*3600 + m_startdatum.getTotaaldagen() * 86400);
	
	CTijdverschil tmp = CTijdverschil((stop - start) / 3600 , ((stop - start)%3600)/60, (stop - start)%60);
	return tmp;
}


void CTijdRegistratie::setStartDatum(CDatum datum)
{
	m_startdatum = datum;
}

void CTijdRegistratie::setStopDatum(CDatum datum)
{
	m_stopdatum = datum;
}

void CTijdRegistratie::setStartTijd(CTijd tijd)
{
	m_starttijd = tijd;
}

void CTijdRegistratie::setStopTijd(CTijd tijd)
{
	m_stoptijd = tijd;
}
