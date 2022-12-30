#ifndef WEATHER_CITYCODE_H
#define WEATHER_CITYCODE_H

#include <QString>
#include <QMap>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>

class WeatherTool{
private:
    static QMap<QString, QString> mCityMap;

    static void initCityMap(){
        //读取文件
        QString filePath = "C:/Users/ASUS/Desktop/weatherTray/citycode.json";

        QFile file(filePath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray json = file.readAll();
        file.close();

        //解析，写入到map
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(json,&err);
        if(err.error != QJsonParseError::NoError){
            return;
        }
        if(!doc.isArray()){
            return;
        }

        QJsonArray cities = doc.array();
        for(int i=0;i < cities.size();i++){
            QString city = cities[i].toObject().value("cityName").toString();
            QString code = cities[i].toObject().value("cityCode").toString();
            if(code.size() > 0){
                mCityMap.insert(city,code);
            }
        }
    }

public:
    static QString getCityCode(QString cityName){
        if(mCityMap.isEmpty()){
            initCityMap();
        }
        QMap<QString,QString>::iterator it = mCityMap.find(cityName);
        if(it == mCityMap.end()){
            it = mCityMap.find(cityName + "市");

        }
        if(it != mCityMap.end()){
            return it.value();
        }

        return "";
    }

};

QMap<QString,QString> WeatherTool::mCityMap = {};

#endif // WEATHER_CITYCODE_H
