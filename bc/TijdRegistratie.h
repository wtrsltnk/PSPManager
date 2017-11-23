#ifndef CTIJDREGISTRATIE_H
#define CTIJDREGISTRATIE_H

#include "tijd.h"
#include "datum.h"
#include "tijdverschil.h"

class CTijdRegistratie
{

private:
	CTijd m_starttijd;
	CTijd m_stoptijd;
	CDatum m_startdatum;
	CDatum m_stopdatum;

public:
	CTijdRegistratie();
	CTijdRegistratie(CTijd &, CTijd &,CDatum &,CDatum &);
	
	CTijd getStartTijd();
	CTijd getStopTijd();
	CDatum getStartDatum();
	CDatum getStopDatum();

	void setStartTijd(CTijd);
	void setStopTijd(CTijd);
	void setStartDatum(CDatum);
	void setStopDatum(CDatum);
	
	CTijdverschil getTotaalTijd();
};

#endif