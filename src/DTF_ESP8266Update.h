#ifndef DTF_ESP8266Update_H
#define DTF_ESP8266Update_H

enum class DTF_UpdateResponse
{
    UPDATE_FAILED = -1,
    NO_UPDATE_AVAILABLE = 1,
    UPDATE_SUCCEEDED = 2,
};

class DTF_ESP8266Update
{
    public:
        static DTF_UpdateResponse getFirmwareUpdate(const char* updateUrl, const char* currentVersion, bool setTime = true);
        static void DTF_UpdateStart();
        static void DTF_UpdateFinished();
        static void DTF_UpdateProgress(int _current, int _total);
};

#endif // DTF_ESP8266Update_H