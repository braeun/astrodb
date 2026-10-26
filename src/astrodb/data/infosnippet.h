#ifndef ASTRODB_INFOSNIPPET_H
#define ASTRODB_INFOSNIPPET_H

#include <QString>

namespace astrodb {

class InfoSnippet
{
public:
  InfoSnippet();
  InfoSnippet(const QString& key, const QString& context, const QString& text, int64_t id=-1);

  int64_t getId() const;

  void setId(int64_t i);

  const QString& getKey() const;

  void setKey(const QString& newKey);

  const QString& getContext() const;

  void setContext(const QString& newContext);

  const QString& getText() const;

  void setText(const QString& newText);

private:
  int64_t id;
  QString key;
  QString context;
  QString text;
};

} // namespace astrodb

#endif // INFOSNIPPET_H
