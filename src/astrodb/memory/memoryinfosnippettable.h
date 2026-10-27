#ifndef MEMORYINFOSNIPPETTABLE_H
#define MEMORYINFOSNIPPETTABLE_H

#include "../infosnippettable.h"
#include <map>

namespace astrodb {

class MemoryInfoSnippetTable: public InfoSnippetTable
{
public:
  MemoryInfoSnippetTable();
  ~MemoryInfoSnippetTable();

  virtual std::set<std::string> getKeys() override;

  virtual std::set<std::string> getKeys(const std::string& context) override;

  virtual std::set<std::string> getContexts() override;

  virtual std::set<std::string> getContexts(const std::string& key) override;

  virtual std::vector<InfoSnippet> getSnippets(const std::string& key, const std::string& context="") override;

  virtual bool add(const InfoSnippet& s) override;

  virtual bool update(const InfoSnippet& s) override;

  virtual bool remove(int64_t id) override;

private:
  size_t findIndex(int64_t id);

  int64_t id;
  std::vector<InfoSnippet> data;

};

} // namespace astrodb

#endif // MEMORYINFOSNIPPETTABLE_H
