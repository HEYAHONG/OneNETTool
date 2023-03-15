#include "serialport.h"
#include "boost/asio.hpp"


serialport::serialport():sp(NULL)
{
    sp_io=(std::make_shared<boost::asio::io_service>());
    sp=new boost::asio::serial_port(*sp_io.get());
}

bool serialport::open(std::string port)
{
    if(sp==NULL)
    {
        return false;
    }
    sp->open(port);
    return sp->is_open();
}

bool serialport::is_open()
{
    if(sp==NULL)
    {
        return false;
    }
    return sp->is_open();
}

void serialport::close()
{
    if(sp==NULL)
    {
        return;
    }
    sp->close();
}

size_t serialport::write(std::string data)
{
    if(sp==NULL)
    {
        return 0;
    }
    return sp->write_some(boost::asio::buffer(data.c_str(),data.length()));
}

std::string serialport::readall()
{
    if(sp==NULL)
    {
        return std::string();
    }
    boost::asio::mutable_buffer buff;
    size_t length=sp->read_some(buff);
    if(length==0)
    {
        return std::string();
    }
    return std::string((const char *)buff.data(),length);
}

serialport::~serialport()
{
    if(sp==NULL)
    {
        delete sp;
        sp=NULL;
    }
}


