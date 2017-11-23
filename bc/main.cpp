#include <iostream>
#include "ProjectManager.h"

int main()
{
	// Maken van een project

	CProjectManager manager;
	string naam = "test";
	string notitie = "notedop";
	CProject mijn = CProject(naam, 10, CDatum(), notitie);
	manager.addProject(mijn);
	CActiviteit ac = CActiviteit(notitie, 9, CDatum(), notitie);
	manager.getProject(naam)->addActiviteit(ac);

    CTijdverschil a = CTijdverschil(2,3,0);
    CTijdverschil b = CTijdverschil(2,3,0);
	b+=a;

	cout << b.getUren() << ":" << b.getMinuten() << endl;


	//manager.removeProject(naam); //uitkomst zou "PROJECT NULL" moeten zijn
	manager.getProject(naam)->removeActiviteit(notitie); //uitkomst zou "ACTIVITEIT NULL" moeten zijn
	if (manager.getProject(naam) == NULL)
		cout << "PROJECT NULL" << endl;
	else if (manager.getProject(naam)->getActiviteit(notitie) == NULL)
		cout << "ACTIVITEIT NULL" << endl;
	else
		cout << manager.getProject(naam)->getActiviteit(notitie)->getNaam().c_str() << endl; //cout << "not NULL" << endl;

    return 0;
}
