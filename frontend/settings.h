#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QVariant>
#include <QString>
#include <memory>
#include <utility>

class Settings : public QObject
{
    Q_OBJECT
public:
    static QSettings* getInstance();
    virtual ~Settings() override;
    Settings() = default;
    Settings(Settings& other) = delete;
    Settings& operator = (const Settings) = delete;

private:
    static QSettings* _instance;
};

#endif // SETTINGS_H
