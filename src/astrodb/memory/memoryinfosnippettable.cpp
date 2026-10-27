#include "memoryinfosnippettable.h"

namespace astrodb {

MemoryInfoSnippetTable::MemoryInfoSnippetTable():
  id(0)
{
}

MemoryInfoSnippetTable::~MemoryInfoSnippetTable()
{
}

std::set<std::string> MemoryInfoSnippetTable::getKeys()
{
  std::set<std::string> keys;
  for (const InfoSnippet& s : data)
  {
    keys.insert(s.getKey());
  }
  return keys;
}

std::set<std::string> MemoryInfoSnippetTable::getKeys(const std::string& context)
{
  if (context.empty()) return getKeys();
  std::set<std::string> keys;
  for (const InfoSnippet& s : data)
  {
    if (s.getContext() == context)
    {
      keys.insert(s.getKey());
    }
  }
  return keys;
}

std::set<std::string> MemoryInfoSnippetTable::getContexts()
{
  std::set<std::string> contexts;
  for (const InfoSnippet& s : data)
  {
    contexts.insert(s.getKey());
  }
  return contexts;
}

std::set<std::string> MemoryInfoSnippetTable::getContexts(const std::string& key)
{
  if (key.empty()) return getContexts();
  std::set<std::string> contexts;
  for (const InfoSnippet& s : data)
  {
    if (s.getKey() == key)
    {
      contexts.insert(s.getContext());
    }
  }
  return contexts;
}

std::vector<InfoSnippet> MemoryInfoSnippetTable::getSnippets(const std::string& key, const std::string& context)
{
  std::vector<InfoSnippet> list;
  for (const InfoSnippet& s : data)
  {
    if ((key.empty() || s.getKey() == key) && (context.empty() || s.getContext() == context))
    {
      list.push_back(s);
    }
  }
  return list;
}

bool MemoryInfoSnippetTable::add(const InfoSnippet& s)
{
  ++id;
  data.push_back(s);
  data.back().setId(id);
  return true;
}

bool MemoryInfoSnippetTable::update(const InfoSnippet& s)
{
  int index = findIndex(s.getId());
  if (index >= 0)
  {
    data[index] = s;
    return true;
  }
  return false;
}

bool MemoryInfoSnippetTable::remove(int64_t id)
{
  int index = findIndex(id);
  if (index >= 0)
  {
    data.erase(data.begin()+index);
    return true;
  }
  return false;
}


size_t MemoryInfoSnippetTable::findIndex(int64_t id)
{
  ssize_t index = 0;
  for (const auto& s : data)
  {
    if (s.getId() == id) return index;
    ++index;
  }
  return -1;
}

} // namespace astrodb
