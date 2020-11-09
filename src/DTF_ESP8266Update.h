#ifndef DTF_ESP8266Update_H
#define DTF_ESP8266Update_H

enum class DTF_UpdateResponse
{
    UPDATE_FAILED = -1,
    NO_UPDATE_AVAILABLE = 1,
};

class DTF_ESP8266Update
{
    public:
        static DTF_UpdateResponse getFirmwareUpdate(const char* updateUrl, const char* currentVersion, bool setTime = true);   
};

#endif // DTF_ESP8266Update_H