#ifndef INFOSNIPPETTABLEQT_H
#define INFOSNIPPETTABLEQT_H

#include <astrodb/infosnippettable.h>
#include <QString>

class QSqlQuery;

namespace astrodb {

class InfoSnippetTableQt: public InfoSnippetTable
{
public:
  InfoSnippetTableQt(const QString& con);
  ~InfoSnippetTableQt() = default;

  virtual std::set<std::string> getKeys() override;

  virtual std::set<std::string> getKeys(const std::string& context) override;

  virtual std::set<std::string> getContexts() override;

  virtual std::set<std::string> getContexts(const std::string& key) override;

  virtual std::vector<InfoSnippet> getSnippets(const std::string& key, const std::string& context="") override;

  virtual bool add(const InfoSnippet& c) override;

  virtual bool update(const InfoSnippet& c) override;

  virtual bool remove(int64_t id) override;

private:
  InfoSnippet get(const QSqlQuery& q) const;

  QString con;
  QString lastError;
};

} // namespace astrodb

#endif // INFOSNIPPETTABLEQT_H
