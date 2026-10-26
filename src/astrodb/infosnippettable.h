#ifndef INFOSNIPPETTABLE_H
#define INFOSNIPPETTABLE_H

#include "data/infosnippet.h"
#include <set>
#include <vector>

namespace astrodb {

class InfoSnippetTable
{
public:
  InfoSnippetTable();
  virtual ~InfoSnippetTable() = default;

  virtual std::set<QString> getKeys() = 0;

  virtual std::set<QString> getKeys(const QString& context) = 0;

  virtual std::set<QString> getContexts() = 0;

  virtual std::set<QString> getContexts(const QString& key) = 0;

  virtual std::vector<InfoSnippet> getSnippets(const QString& key, const QString& context="") = 0;

  virtual bool add(InfoSnippet& c) = 0;

  virtual bool update(const InfoSnippet& c) = 0;

  virtual bool remove(int64_t id) = 0;

};

} // namespace astrodb

#endif // INFOSNIPPETTABLE_H
