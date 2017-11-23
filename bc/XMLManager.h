#include "projectmanager.h"
#include <string>
#include <vector>

using namespace std;

typedef struct _XMLINFO
{
	string tag;
	string value;
} XMLINFO;

class CXMLManager
{
private:
	void addTijdRegistratie(CActiviteit *, CTijdRegistratie **);
	void addActiviteit(CProject *, CActiviteit **);
	void addProject(CProjectManager *, CProject **);
	string openFileForXMLInput(string);
	string m_readwritepath;
public:
	bool readXML(string, bool, CProjectManager&);
    bool saveXML(string, bool, const CProjectManager&);
    bool saveXML(const CProjectManager& pm);
	void setXMLPath(string);
	string getXMLPath();
};

