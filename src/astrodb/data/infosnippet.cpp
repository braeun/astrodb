#include "infosnippet.h"

namespace astrodb {

InfoSnippet::InfoSnippet()
{
}

InfoSnippet::InfoSnippet(const QString& key, const QString& context, const QString& text, int64_t id):
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

const QString& InfoSnippet::getContext() const
{
  return context;
}

void InfoSnippet::setContext(const QString& newContext)
{
  context = newContext;
}

const QString& InfoSnippet::getKey() const
{
  return key;
}

void InfoSnippet::setKey(const QString& newKey)
{
  key = newKey;
}

const QString& InfoSnippet::getText() const
{
  return text;
}

void InfoSnippet::setText(const QString& newText)
{
  text = newText;
}

} // namespace astrodb
