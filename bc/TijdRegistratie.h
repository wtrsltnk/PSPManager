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
	
    CTijd getStartTijd() const;
    CTijd getStopTijd() const;
    CDatum getStartDatum() const;
    CDatum getStopDatum() const;

	void setStartTijd(CTijd);
	void setStopTijd(CTijd);
	void setStartDatum(CDatum);
	void setStopDatum(CDatum);
	
    CTijdverschil getTotaalTijd() const;
};

#endif
