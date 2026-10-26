#ifndef ASTRODB_INFOSNIPPET_H
#define ASTRODB_INFOSNIPPET_H

#include <string>

namespace astrodb {

class InfoSnippet
{
public:
  InfoSnippet();
  InfoSnippet(const std::string& key, const std::string& context, const std::string& text, int64_t id=-1);

  int64_t getId() const;

  void setId(int64_t i);

  const std::string& getKey() const;

  void setKey(const std::string& newKey);

  const std::string& getContext() const;

  void setContext(const std::string& newContext);

  const std::string& getText() const;

  void setText(const std::string& newText);

private:
  int64_t id;
  std::string key;
  std::string context;
  std::string text;
};

} // namespace astrodb

#endif // INFOSNIPPET_H
