#include "infosnippet.h"

namespace astrodb {

InfoSnippet::InfoSnippet()
{
}

InfoSnippet::InfoSnippet(const std::string& key, const std::string& context, const std::string& text, int64_t id):
  id(id),
  key(key),
  context(context),
  text(text)
{
}

int64_t InfoSnippet::getId() const
{
  return id;
}

void InfoSnippet::setId(int64_t i)
{
  id = i;
}

const std::string& InfoSnippet::getContext() const
{
  return context;
}

void InfoSnippet::setContext(const std::string& newContext)
{
  context = newContext;
}

const std::string& InfoSnippet::getKey() const
{
  return key;
}

void InfoSnippet::setKey(const std::string& newKey)
{
  key = newKey;
}

const std::string& InfoSnippet::getText() const
{
  return text;
}

void InfoSnippet::setText(const std::string& newText)
{
  text = newText;
}

} // namespace astrodb
