#ifndef SERIALPORT_H
#define SERIALPORT_H
#ifdef __cplusplus

#include <string>
#include <memory>
#include <boost/asio.hpp>

class serialport
{
    std::shared_ptr<boost::asio::io_service>  sp_io;
    boost::asio::serial_port *sp;
public:
    serialport();
    virtual ~serialport();
    bool open(std::string port);
    bool is_open();
    void close();
    size_t write(std::string data);
    std::string readall();
};

#endif // __cplusplus

#endif // SERIALPORT_H

