#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>

#include "logging.hpp"

using namespace std;

string ConfigFileRead(string key_)
{
    ifstream configFile;
    char buf[256];
    GetModuleFileName(NULL, buf, MAX_PATH);
    string path;
    string strLine;
    string serverIp;
    path.assign(buf);
    path.append("\\..\\config.ini");
    configFile.open(path.c_str());
    if (configFile.is_open())
    {
        while (!configFile.eof())
        {
            getline(configFile, strLine);
            size_t pos = strLine.find('=');
            string key = strLine.substr(0, pos);

            if (key == key_)
            {
                serverIp = strLine.substr(pos + 1);
            }
        }
    }
    else
    {
        printf("open file failed\n");
        Log::Debug("dem1service:: open file failed\n");
    }
    return serverIp;
}

