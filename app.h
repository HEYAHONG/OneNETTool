#ifndef APP_H
#define APP_H

#include <wx/app.h>
#include <wx/timer.h>
#include <queue>
#include <vector>
#include <mutex>
#include <functional>

class Frame;

class App : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();

private:
    //UI刷新函数队列(其它线程的函数转发至队列执行)
    std::queue<std::function<void()>> UIEvent;
    std::mutex UIEventLock;
    void ProcessUIEvent()
    {
        std::lock_guard<std::mutex> lock(UIEventLock);
        while(UIEvent.size()>0)
        {
            std::function<void()> cb=UIEvent.front();
            UIEvent.pop();
            if(cb!=NULL)
            {
                UIEventLock.unlock();
                try
                {
                    cb();
                }
                catch(...)
                {

                }
                UIEventLock.lock();
            }
        }
    };
    std::vector<std::function<void()>> OnExitEvent;
    std::mutex OnExitEventLock;
public:
    /*
    *
    *外部调用用于添加自定义UI事件。
    */
    void AddUIEvent(std::function<void()> cb)
    {
        std::lock_guard<std::mutex> lock(UIEventLock);
        UIEvent.push(cb);
    };
    friend class Frame;
    /*
    *
    *添加退出事件
    */
    void AddOnExitEvent(std::function<void()> cb)
    {
        std::lock_guard<std::mutex> lock(OnExitEventLock);
        OnExitEvent.push_back(cb);
    };

};

/*
获取App指针
*/
App * 	GetInstance();

#define wxID_APP_CUSTPM_BASE 100000
#define wxID_APP_CUSTOM_FRAME_UITIMER (wxID_APP_CUSTPM_BASE+1)

#endif // APP_H


