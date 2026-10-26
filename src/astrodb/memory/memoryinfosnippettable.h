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

  virtual std::set<QString> getKeys() override;

  virtual std::set<QString> getKeys(const QString& context) override;

  virtual std::set<QString> getContexts() override;

  virtual std::set<QString> getContexts(const QString& key) override;

  virtual std::vector<InfoSnippet> getSnippets(const QString& key, const QString& context="") override;

  virtual bool add(InfoSnippet& s) override;

  virtual bool update(const InfoSnippet& s) override;

  virtual bool remove(int64_t id) override;

private:
  size_t findIndex(int64_t id);

  int64_t id;
  std::vector<InfoSnippet> data;

};

} // namespace astrodb

#endif // MEMORYINFOSNIPPETTABLE_H
