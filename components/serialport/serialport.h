#ifndef SERIALPORT_H
#define SERIALPORT_H
#ifdef __cplusplus

#include <string>
#include <memory>
#include <boost/asio.hpp>

class serialport
{
public:
    typedef enum
    {
        SERIALPORT_STOPBITS_ONE,
        SERIALPORT_STOPBITS_ONEHALF,
        SERIALPORT_STOPBITS_TWO,
    } StopBits;
    typedef enum
    {
        SERIALPORT_FLOWCONTROL_NONE,
        SERIALPORT_FLOWCONTROL_SOFT,
        SERIALPORT_FLOWCONTROL_HARD,
    } FlowControl;
    typedef enum
    {
        SERIALPORT_PARITY_NONE,
        SERIALPORT_PARITY_ODD,
        SERIALPORT_PARITY_EVEN,
    } Parity;
private:
    std::shared_ptr<boost::asio::io_service>  sp_io;
    boost::asio::serial_port *sp;
public:
    serialport();
    virtual ~serialport();
    bool open(std::string port);
    void setdatarate(size_t datarate);
    void setdatabits(size_t databits);
    void setstopbits(StopBits stopbits);
    void setflowcontrol(FlowControl flowcontrol);
    void setparity(Parity parity);
    bool is_open();
    void close();
    size_t write(std::string data);
    std::string readall();
};

#endif // __cplusplus

#endif // SERIALPORT_H

