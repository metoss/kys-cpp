#pragma once
#include "others/INIReader.h"
#include "others/libconvert.h"
#include <algorithm>
#include <functional>
#include <string>

//该类用于读取配置文件，并转换其中的字串设置为枚举
//注意实数只获取双精度数，如果是单精度模式会包含隐式转换
//获取整数的时候，先获取双精度数并强制转换
struct Option
{
    Option() {}
    Option(const std::string& filename);
    ~Option() {}

private:
    static Option option_;

    INIReader ini_reader_;
    std::string default_section_ = "";

    std::string dealString(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        convert::replaceAllString(str, "_", "");
        return str;
    }

public:
    static Option* getInstance() { return &option_; }

    //载入ini文件
    void loadIniFile(const std::string& filename);
    void loadIniString(const std::string& content);

    //默认section
    void setDefautlSection(const std::string& section) { default_section_ = section; }
    const std::string& getDefautlSection() { return default_section_; }

    //从指定section提取
    int getInt(const std::string& section, const std::string& key, int default_value = 0)
    {
        return int(ini_reader_.getReal(section, dealString(key), default_value));
    }
    double getReal(const std::string& section, const std::string& key, double default_value = 0.0)
    {
        return ini_reader_.getReal(section, dealString(key), default_value);
    }
    std::string getString(const std::string& section, const std::string& key, std::string default_value = "");

    void setOption(std::string section, std::string key, std::string value)
    {
        ini_reader_.setKey(section, dealString(key), value);
    }

    void print();

public:
    int MaxLevel = 30;
    int MaxHP = 999;
    int MaxMP = 999;
    int MaxPhysicalPower = 100;

    int MaxPosion = 100;

    int MaxAttack = 100;
    int MaxDefence = 100;
    int MaxSpeed = 100;

    int MaxMedcine = 100;
    int MaxUsePoison = 100;
    int MaxDetoxification = 100;
    int MaxAntiPoison = 100;

    int MaxFist = 100;
    int MaxSword = 100;
    int MaxKnife = 100;
    int MaxUnusual = 100;
    int MaxHiddenWeapon = 100;

    int MaxKnowledge = 100;
    int MaxMorality = 100;
    int MaxAttackWithPoison = 100;
    int MaxFame = 999;
    int MaxIQ = 100;

    int MaxExp = 99999;

    int MoneyItemID = 174;
    int CompassItemID = 182;

    void loadSaveValues();
};
