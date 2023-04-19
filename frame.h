#ifndef FRAME_H
#define FRAME_H
#include "GUIFrame.h"
#include "wxrc.h"
#include <vector>
#include <list>
#include <chrono>
#include <string>
#include <mosquittopp.h>
#include "onenetonejson.h"

class App;

class Frame:public MainFrame,public mosqpp::mosquittopp
{
public:
    Frame();
    virtual ~Frame();

    //mosquitto回调函数
    virtual void on_connect(int /*rc*/);
    virtual void on_connect_with_flags(int /*rc*/, int /*flags*/)
    {
        return;
    }
    virtual void on_disconnect(int /*rc*/);
    virtual void on_publish(int /*mid*/)
    {
        return;
    }
    virtual void on_message(const struct mosquitto_message * /*message*/);
    virtual void on_subscribe(int /*mid*/, int /*qos_count*/, const int * /*granted_qos*/)
    {
        return;
    }
    virtual void on_unsubscribe(int /*mid*/)
    {
        return;
    }
    virtual void on_log(int /*level*/, const char * /*str*/);
    virtual void on_error()
    {
        return;
    }


protected:
    virtual void OnTokenSize( wxSizeEvent& event );
    virtual void OnTokenetChoiceUpdate( wxCommandEvent& event );
    virtual void OnTokenetTextUpdate( wxCommandEvent& event );
    virtual void OnTokenresChoice( wxCommandEvent& event );
    virtual void OnTokenGenerateButtonClick( wxCommandEvent& event );
    virtual void OnMenuLwM2MDeviceAdd( wxCommandEvent& event );
    virtual void OnMenuLwM2MDeviceListClearAll( wxCommandEvent& event );
    virtual void OnMenuLwM2MDeviceListRemove( wxCommandEvent& event );
    virtual void OnLwM2MDeviceListContextMenu( wxDataViewEvent& event );
    virtual void OnLwM2MDeviceListSaveButtonClick( wxCommandEvent& event );
    virtual void OnMQTTDeviceServerConnectButtonClick( wxCommandEvent& event );
    virtual void OnMQTTDeviceServerDisconnectButtonClick( wxCommandEvent& event );
    virtual void OnButtonLwM2MDeviceListClearAllClick( wxCommandEvent& event );
    virtual void OnMenuFileSubExit( wxCommandEvent& event );
    virtual void OnMenuLinksSubOneNET( wxCommandEvent& event );
    virtual void OnMenuLinksSubOneNETToken( wxCommandEvent& event );
    virtual void OnMenuHelpAbout( wxCommandEvent& event );

private:
    App &app;
    wxTimer *UITimer;
    void UITimerEvent(wxTimerEvent& event)
    {
        app.ProcessUIEvent();
    }

    //LwM2MDevice列表
    typedef struct
    {
        wxString DeviceName;
        wxString IMEI;
        wxString IMSI;
        wxString AuthCode;
        wxString PSK;
    } LwM2MDevice;
    std::vector<LwM2MDevice> LwM2MDeviceList;
    void ClearAllLwM2MDevice();
    void AddLwM2MDevice(LwM2MDevice device);
    void RemoveLwM2MDevice(size_t index);
    wxString TokenGenerate();
    bool CheckMQTTDeviceConnectInfo();
    bool CheckMQTTTokenInfo();

    //onejson上下文
    struct
    {
        wxString productid;
        wxString devicename;
    } current_onejson_settings;
    struct OneNETOneJsonContext *onejson;

    //MQTT消息发送与接收记录
    typedef struct
    {
        std::string topic;
        std::string payload;
        std::chrono::system_clock::time_point timestamp;
    } MQTTMessage;
    size_t MaxMQTTPublishMessageListLength;
    std::list<MQTTMessage> MQTTPublishMessage;
    std::mutex  MQTTPublishMessageLock;
    bool MQTTPublish(std::string topic,std::string payload);
    size_t MaxMQTTReceiveMessageListLength;
    std::list<MQTTMessage> MQTTReceiveMessage;
    std::mutex  MQTTReceiveMessageLock;


};

#endif // FRAME_H
