#include "infosnippettableqt.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace astrodb {

InfoSnippetTableQt::InfoSnippetTableQt(const QString& con):
  con(con)
{
}

std::set<std::string> InfoSnippetTableQt::getKeys()
{
  std::set<std::string> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT UNIQUE(key) FROM InfoSnippets");
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  else
  {
    while (q.next())
    {
      list.insert(q.value(0).toString().toStdString());
    }
  }
  return list;
}

std::set<std::string> InfoSnippetTableQt::getKeys(const std::string& context)
{
  std::set<std::string> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT UNIQUE(key) FROM InfoSnippets WHERE context=?");
  q.bindValue(0,QString::fromStdString(context));
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  else
  {
    while (q.next())
    {
      list.insert(q.value(0).toString().toStdString());
    }
  }
  return list;
}

std::set<std::string> InfoSnippetTableQt::getContexts()
{
  std::set<std::string> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT UNIQUE(context) FROM InfoSnippets");
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  else
  {
    while (q.next())
    {
      list.insert(q.value(0).toString().toStdString());
    }
  }
  return list;
}

std::set<std::string> InfoSnippetTableQt::getContexts(const std::string& key)
{
  std::set<std::string> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  q.prepare("SELECT UNIQUE(context) FROM InfoSnippets WHERE key=?");
  q.bindValue(0,QString::fromStdString(key));
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  else
  {
    while (q.next())
    {
      list.insert(q.value(0).toString().toStdString());
    }
  }
  return list;

}

std::vector<InfoSnippet> InfoSnippetTableQt::getSnippets(const std::string& key, const std::string& context)
{
  std::vector<InfoSnippet> list;
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return list;
  QSqlQuery q(db);
  if (key.empty() && context.empty())
    q.prepare("SELECT * FROM InfoSnippets");
  else if (context.empty())
  {
    q.prepare("SELECT * FROM InfoSnippets WHERE key=?");
    q.bindValue(0,QString::fromStdString(key));
  }
  else if (key.empty())
  {
    q.prepare("SELECT * FROM InfoSnippets WHERE context=?");
    q.bindValue(0,QString::fromStdString(context));
  }
  else
  {
    q.prepare("SELECT * FROM InfoSnippets WHERE key=? AND context=?");
    q.bindValue(0,QString::fromStdString(key));
    q.bindValue(1,QString::fromStdString(context));
  }
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  else
  {
    while (q.next())
    {
      list.push_back(get(q));
    }
  }
  return list;

}

bool InfoSnippetTableQt::add(const InfoSnippet& c)
{
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("INSERT INTO InfoSnippets (key,context,note) VALUES (?,?,?)");
  q.bindValue(0,QString::fromStdString(c.getKey()));
  q.bindValue(1,QString::fromStdString(c.getContext()));
  q.bindValue(2,QString::fromStdString(c.getText()));
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}

bool InfoSnippetTableQt::update(const InfoSnippet& c)
{
  if (c.getId() < 0) return add(c);
  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("UPDATE InfoSnippets SET key=?,context=?,note=? WHERE id=?");
  q.bindValue(0,QString::fromStdString(c.getKey()));
  q.bindValue(1,QString::fromStdString(c.getContext()));
  q.bindValue(2,QString::fromStdString(c.getText()));
  q.bindValue(3,(qlonglong)c.getId());
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;

}

bool InfoSnippetTableQt::remove(int64_t id)
{

  QSqlDatabase db = QSqlDatabase::database(con);
  if (!(db.isValid() && db.isOpen())) return false;
  QSqlQuery q(db);
  q.prepare("DELETE * FROM InfoSnippets where id=?");
  q.bindValue(0,(qlonglong)id);
  bool ret = q.exec();
  lastError = q.lastError().text();
  if (!ret)
  {
    qWarning() << q.lastError();
    qWarning() << q.executedQuery();
  }
  return ret;
}


InfoSnippet InfoSnippetTableQt::get(const QSqlQuery& q) const
{
  std::string key = q.value("key").toString().toStdString();
  std::string context = q.value("context").toString().toStdString();
  std::string text = q.value("text").toString().toStdString();
  InfoSnippet o(key,context,text);
  o.setId(q.value("id").toLongLong());
  return o;
}



} // namespace astrodb
