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

  virtual std::set<std::string> getKeys() = 0;

  virtual std::set<std::string> getKeys(const std::string& context) = 0;

  virtual std::set<std::string> getContexts() = 0;

  virtual std::set<std::string> getContexts(const std::string& key) = 0;

  virtual std::vector<InfoSnippet> getSnippets(const std::string& key, const std::string& context="") = 0;

  virtual bool add(const InfoSnippet& c) = 0;

  virtual bool update(const InfoSnippet& c) = 0;

  virtual bool remove(int64_t id) = 0;

};

} // namespace astrodb

#endif // INFOSNIPPETTABLE_H
