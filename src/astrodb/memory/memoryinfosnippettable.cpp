#include "memoryinfosnippettable.h"

namespace astrodb {

MemoryInfoSnippetTable::MemoryInfoSnippetTable():
  id(0)
{
}

MemoryInfoSnippetTable::~MemoryInfoSnippetTable()
{
}

std::set<QString> MemoryInfoSnippetTable::getKeys()
{
  std::set<QString> keys;
  for (const InfoSnippet& s : data)
  {
    keys.insert(s.getKey());
  }
  return keys;
}

std::set<QString> MemoryInfoSnippetTable::getKeys(const QString& context)
{
  if (context.isEmpty()) return getKeys();
  std::set<QString> keys;
  for (const InfoSnippet& s : data)
  {
    if (s.getContext() == context)
    {
      keys.insert(s.getKey());
    }
  }
  return keys;
}

std::set<QString> MemoryInfoSnippetTable::getContexts()
{
  std::set<QString> contexts;
  for (const InfoSnippet& s : data)
  {
    contexts.insert(s.getKey());
  }
  return contexts;
}

std::set<QString> MemoryInfoSnippetTable::getContexts(const QString& key)
{
  if (key.isEmpty()) return getContexts();
  std::set<QString> contexts;
  for (const InfoSnippet& s : data)
  {
    if (s.getKey() == key)
    {
      contexts.insert(s.getContext());
    }
  }
  return contexts;
}

std::vector<InfoSnippet> MemoryInfoSnippetTable::getSnippets(const QString& key, const QString& context)
{
  std::vector<InfoSnippet> list;
  for (const InfoSnippet& s : data)
  {
    if ((key.isEmpty() || s.getKey() == key) && (context.isEmpty() || s.getContext() == context))
    {
      list.push_back(s);
    }
  }
  return list;
}

bool MemoryInfoSnippetTable::add(InfoSnippet& s)
{
  ++id;
  s.setId(id);
  data.push_back(s);
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
