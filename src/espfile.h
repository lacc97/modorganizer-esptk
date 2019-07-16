#ifndef ESPFILE_H
#define ESPFILE_H


#include <string>
#include <fstream>
#include <set>
#include "record.h"
#include "tes3record.h"


namespace ESP {

class SubRecord;

class File
{
public:

  File(const std::string &fileName);

#if defined(WIN32)
  File(const std::wstring &fileName);
#endif

  Record readRecord();

  bool isMaster() const;
  bool isLight() const;
  bool isDummy() const;
  std::string author() const { return m_Author; }
  std::string description() const { return m_Description; }
  std::set<std::string> masters() const { return m_Masters; }

private:

  void init();

  void onHEDR(const SubRecord &rec);
  void onMAST(const SubRecord &rec);
  void onCNAM(const SubRecord &rec);
  void onSNAM(const SubRecord &rec);

private:

  std::ifstream m_File;

  struct {
    float version;
    int32_t numRecords;
    uint32_t nextObjectId;
  } m_Header;

  struct {
	  float version;
	  uint32_t unknown;
	  char author[32];
	  char description[256];
	  uint32_t numRecords;
  } m_TES3Header;

  Record m_MainRecord;

  std::string m_Author;
  std::string m_Description;

  std::set<std::string> m_Masters;

};

}

#endif // ESPFILE_H
