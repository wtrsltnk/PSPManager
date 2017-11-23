#include "XMLManager.h"
#include <fstream>
using namespace std;

bool CXMLManager::saveXML(CProjectManager pm)
{
	return saveXML(m_readwritepath, false, pm);
}

bool CXMLManager::readXML(string filename, bool import, CProjectManager& pm)
{
	if (!import)
		m_readwritepath = filename;

	string text = openFileForXMLInput(filename);
	if (stricmp((const char*)text.c_str(), "") == 0)
		return false;

	vector<XMLINFO> vec;
	signed int pos = 0;

	while (pos < text.size())
	{
		XMLINFO newitem;
		while (text[pos] != '<' && text[pos] != '\0')
			pos++;

		pos++;

		while (text[pos] != '>' && text[pos] != '\0')
		{
			newitem.tag += text[pos];
			pos++;
		}

		pos++;

		while (text[pos] != '<' && text[pos] != '\0')
		{
			newitem.value += text[pos];
			pos++;
		}

		if (newitem.tag[0] != '/' && newitem.tag[0] != '?' && newitem.tag[0] != '!')
			vec.push_back(newitem);
	}

	//Hier wordt de vector verwerkt naar een CProjectManager
	if (!import)
		CProjectManager pm = CProjectManager();
	CProject * cp = NULL;
	CActiviteit * ca = NULL;
	CTijdRegistratie * ct = NULL;
	string prevtag;
	XMLINFO xml;
	
	for (signed int i = 0; i < vec.size(); i++)
	{
		xml=vec[i];

		if (cp == NULL)
		{
			if (stricmp(xml.tag.c_str(),"project") == 0)
			{
				cp = new CProject();
			}
		}
		else if (ca == NULL)
		{
			if (stricmp(xml.tag.c_str(),"project") == 0)
			{
				addProject(&pm, &cp);
				cp = NULL;
				cp = new CProject();
			}
			if (stricmp(xml.tag.c_str(),"activiteit") == 0)
			{
				ca = new CActiviteit();
			}
			else if (stricmp(xml.tag.c_str(),"naam") == 0)
			{
				cp->setNaam(xml.value);
			}
			else if (stricmp(xml.tag.c_str(),"notitie") == 0)
			{
				cp->setNotitie(xml.value);
			}
			else if (stricmp(xml.tag.c_str(),"deadline") == 0)
			{
				cp->setDeadLine(CDatum((char *)xml.value.c_str()));
			}
			else if (stricmp(xml.tag.c_str(),"status") == 0)
			{
				if (stricmp(xml.value.c_str(),"actief") == 0)
					cp->setStatus(0);
				else if (stricmp(xml.value.c_str(),"beeindigd") == 0)
					cp->setStatus(1);
				else if (stricmp(xml.value.c_str(),"geblokkeerd") == 0)
					cp->setStatus(2);
			}
		}
		else if (ct == NULL)
		{
			if (stricmp(xml.tag.c_str(),"project") == 0)
			{
				addActiviteit(cp, &ca);
				ca = NULL;
				addProject(&pm, &cp);
				cp = NULL;
				cp = new CProject();
			}
			else if (stricmp(xml.tag.c_str(),"activiteit") == 0)
			{
				addActiviteit(cp, &ca);
				ca = NULL;
				ca = new CActiviteit();
			}
			else if (stricmp(xml.tag.c_str(),"naam") == 0)
			{
				ca->setNaam(xml.value);
			}
			else if (stricmp(xml.tag.c_str(),"notitie") == 0)
			{
				ca->setNotitie(xml.value);
			}
			else if (stricmp(xml.tag.c_str(),"deadline") == 0)
			{
				ca->setDeadLine(CDatum((char *)xml.value.c_str()));
			}
			else if (stricmp(xml.tag.c_str(),"status") == 0)
			{
				if (stricmp(xml.value.c_str(),"actief") == 0)
					ca->setStatus(0);
				else if (stricmp(xml.value.c_str(),"beeindigd") == 0) //inlezen XML file error op ë
					ca->setStatus(1);
				else if (stricmp(xml.value.c_str(),"geblokkeerd") == 0)
					ca->setStatus(2);
			}
			else if (stricmp(xml.tag.c_str(),"tijden") == 0)
			{
				if(!import)
					ct = new CTijdRegistratie();
			}
		}
		else //ct != NULL
		{
			if (stricmp(xml.tag.c_str(),"project") == 0)
			{
				addTijdRegistratie(ca, &ct);
				addActiviteit(cp, &ca);
				addProject(&pm, &cp);
				cp = new CProject();
			}
			else if (stricmp(xml.tag.c_str(),"activiteit") == 0)
			{
				addTijdRegistratie(ca, &ct);
				addActiviteit(cp, &ca);
				ca = new CActiviteit();
			}
			else if (stricmp(xml.tag.c_str(),"tijden") == 0)
			{
				addTijdRegistratie(ca, &ct);
				ct = new CTijdRegistratie();
			}
			else if (stricmp(xml.tag.c_str(),"start") == 0)
			{
				prevtag = "start";
			}
			else if (stricmp(xml.tag.c_str(),"stop") == 0)
			{
				prevtag = "stop";
			}
			else if (stricmp(xml.tag.c_str(),"tijd") == 0)
			{
				if (stricmp(prevtag.c_str(), "start") == 0)
				{
					ct->setStartTijd(CTijd((char *)xml.value.c_str()));
					ct->setStopTijd(ct->getStartTijd());
				}
				else if(stricmp(prevtag.c_str(), "stop") == 0)
					ct->setStopTijd(CTijd((char *)xml.value.c_str()));
			}
			else if (stricmp(xml.tag.c_str(),"datum") == 0)
			{
				if (stricmp(prevtag.c_str(), "start") == 0)
				{
					ct->setStartDatum(CDatum((char *)xml.value.c_str()));
					ct->setStopDatum(ct->getStartDatum());
				}
				else if(stricmp(prevtag.c_str(), "stop") == 0)
					ct->setStopDatum(CDatum((char *)xml.value.c_str()));
			}
		}
	}
	addTijdRegistratie(ca,&ct);
	addActiviteit(cp,&ca);
	addProject(&pm,&cp);

	if (cp != NULL)
		delete cp;
	if (ca != NULL)
		delete ca;
	if (ct != NULL)
		delete ct;

	return true;
}

void CXMLManager::addTijdRegistratie(CActiviteit * act, CTijdRegistratie ** tr)
{
	if (*tr != NULL)
		act->addTijdRegistratie(**tr);

	delete *tr;
	*tr = NULL;
}

void CXMLManager::addActiviteit(CProject * pr, CActiviteit ** act)
{
	if (*act != NULL)
		pr->addActiviteit(**act);

	delete *act;
	*act = NULL;
}

void CXMLManager::addProject(CProjectManager * pm, CProject ** pr)
{
	if (*pr != NULL)
		pm->addProject(**pr);

	delete *pr;
	*pr = NULL;
}

string CXMLManager::openFileForXMLInput(string filename)
{
	string total;
	ifstream input;
	input.open((const char *)filename.c_str());

	if (input.fail())
		return total;

	char tmptext;

	input.get(tmptext);

	while (!input.eof())
	{
		if (tmptext != '\n' && tmptext != '\t')
			total += tmptext;
		else if(tmptext == '\t')
			total += " ";

		input.get(tmptext);
	}
	
	return total;
}

bool CXMLManager::saveXML(string filename, bool export, CProjectManager pm)
{
	if (!export)
	{
		m_readwritepath = filename;//.append(".xml");
	}

	if (stricmp(filename.c_str(), "") == 0)
		filename = "c:\\psp_noname.xml";

	const string activiteiten[3] = {"actief", "beeindigd", "geblokkeerd"};
	ofstream output;
	output.open((const char *)filename.c_str());

	if (output.fail())
		return false;

	output  << "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n"
			<< "<!--  export PSP-manager van " << CDatum().toString() << " " << CTijd().toString() << " -->\n"
			<< "<psp>\n";

	vector<CProject> vec1 = pm.getProjecten();

	for ( int i = 0; i < vec1.size(); i++)
	{
		output  << "\t<project>\n\t\t<pid>\n"
				<< "\t\t\t<naam>" << vec1[i].getNaam() << "</naam>\n"
				<< "\t\t\t<status>" << activiteiten[vec1[i].getStatus()] << "</status>\n"
				<< "\t\t\t<notitie>" << vec1[i].getNotitie() << "</notitie>\n"
				<< "\t\t\t<deadline>" << vec1[i].getDeadLine().toString() << "</deadline>\n"
				<< "\t\t</pid>\n";

		vector<CActiviteit> vec2 = vec1[i].getActiviteiten();

		for ( int j = 0; j < vec2.size(); j++)
		{
			output  << "\t\t<activiteit>\n\t\t\t<aid>\n"
					<< "\t\t\t\t<naam>" << vec2[j].getNaam() << "</naam>\n"
					<< "\t\t\t\t<status>" << activiteiten[vec2[j].getStatus()] << "</status>\n"
					<< "\t\t\t\t<notitie>" << vec2[j].getNotitie() << "</notitie>\n"
					<< "\t\t\t\t<deadline>" << vec2[j].getDeadLine().toString() << "</deadline>\n"
					<< "\t\t\t</aid>\n";

			if (!export)
			{
				vector<CTijdRegistratie> vec3 = vec2[j].getTijdRegistraties();

				for ( int k = 0; k < vec3.size(); k++)
				{
					output  << "\t\t\t<tijden>\n"
							<< "\t\t\t\t<start>\n"
							<< "\t\t\t\t\t<tijd>" << vec3[k].getStartTijd().toString() << "</tijd>\n"
							<< "\t\t\t\t\t<datum>" << vec3[k].getStartDatum().toString() << "</datum>\n"
							<< "\t\t\t\t</start>\n"
							<< "\t\t\t\t<stop>\n"
							<< "\t\t\t\t\t<tijd>" << vec3[k].getStopTijd().toString() << "</tijd>\n"
							<< "\t\t\t\t\t<datum>" << vec3[k].getStopDatum().toString() << "</datum>\n"
							<< "\t\t\t\t</stop>\n"
							<< "\t\t\t</tijden>\n";
				}
			}
			output << "\t\t</activiteit>\n";
		}
		output << "\t</project>\n";
	}
	output << "</psp>\n";

	output.close();
	return true;
}

void CXMLManager::setXMLPath(string filename)
{
	m_readwritepath = filename;
}

//Nieuwe functie
string CXMLManager::getXMLPath()
{
	return m_readwritepath;
}