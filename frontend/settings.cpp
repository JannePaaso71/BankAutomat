#include "settings.h"

QSettings *Settings::getInstance()
{
    if (!_instance) {
        auto settingsFile1 = qgetenv("userprofile").toStdString() + "\\.atm_settings.ini";
        qDebug() << "Settings file goes to: " << settingsFile1;
        _instance = new QSettings(QString::fromStdString(settingsFile1), QSettings::Format::IniFormat);
    }
    return _instance;
}

Settings::~Settings()
{
    delete _instance;
}


QSettings *Settings::_instance = nullptr;


