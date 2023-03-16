#include "serialport.h"
#include "boost/asio.hpp"


serialport::serialport():sp(NULL)
{
    sp_io=(std::make_shared<boost::asio::io_service>());
    sp=new boost::asio::serial_port(*sp_io.get());
}

bool serialport::open(std::string port)
{
    try
    {
        if(sp==NULL)
        {
            return false;
        }
        sp->open(port);
        return sp->is_open();
    }
    catch(...)
    {

    }
    return false;
}

void serialport::setdatarate(size_t datarate)
{
    try
    {
        sp->set_option(boost::asio::serial_port::baud_rate(datarate));
    }
    catch(...)
    {

    }
}

void serialport::setdatabits(size_t databits)
{
    try
    {
        sp->set_option(boost::asio::serial_port::character_size(databits));
    }
    catch(...)
    {

    }
}

void serialport::setstopbits(serialport::StopBits stopbits)
{
    try
    {
        boost::asio::serial_port::stop_bits sb(boost::asio::serial_port::stop_bits::one);
        switch(stopbits)
        {
        case SERIALPORT_STOPBITS_ONE:
        {
            sb=boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one);
        }
        break;
        case SERIALPORT_STOPBITS_ONEHALF:
        {
            sb=boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::onepointfive);
        }
        break;
        case SERIALPORT_STOPBITS_TWO:
        {
            sb=boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::two);
        }
        break;
        default:
            break;
        }
        sp->set_option(sb);
    }
    catch(...)
    {

    }
}

void serialport::setflowcontrol(serialport::FlowControl flowcontrol)
{
    try
    {
        boost::asio::serial_port::flow_control fc(boost::asio::serial_port::flow_control::none);
        switch(flowcontrol)
        {
        case SERIALPORT_FLOWCONTROL_NONE:
        {
            fc=boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none);
        }
        break;
        case SERIALPORT_FLOWCONTROL_SOFT:
        {
            fc=boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::software);
        }
        break;
        case SERIALPORT_FLOWCONTROL_HARD:
        {
            fc=boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::hardware);
        }
        break;
        default:
            break;
        }
        sp->set_option(fc);
    }
    catch(...)
    {

    }

}
void serialport::setparity(serialport::Parity _parity)
{
    try
    {
        boost::asio::serial_port::parity parity(boost::asio::serial_port::parity::none);
        switch(_parity)
        {
        case SERIALPORT_PARITY_NONE:
        {
            parity=boost::asio::serial_port::parity(boost::asio::serial_port::parity::none);
        }
        break;
        case SERIALPORT_PARITY_ODD:
        {
            parity=boost::asio::serial_port::parity(boost::asio::serial_port::parity::odd);
        }
        break;
        case SERIALPORT_PARITY_EVEN:
        {
            parity=boost::asio::serial_port::parity(boost::asio::serial_port::parity::even);
        }
        break;
        default:
            break;
        }
        sp->set_option(parity);
    }
    catch(...)
    {

    }

}

bool serialport::is_open()
{
    try
    {
        if(sp==NULL)
        {
            return false;
        }
        return sp->is_open();
    }
    catch(...)
    {

    }
    return false;
}

void serialport::close()
{
    try
    {
        if(sp==NULL)
        {
            return;
        }
        sp->close();
    }
    catch(...)
    {

    }
}

size_t serialport::write(std::string data)
{
    try
    {
        if(sp==NULL)
        {
            return 0;
        }
        return sp->write_some(boost::asio::buffer(data.c_str(),data.length()));
    }
    catch(...)
    {

    }
    return 0;

}

std::string serialport::readall()
{
    try
    {
        if(sp==NULL)
        {
            return std::string();
        }
        uint8_t _buff[4096]= {0};
        boost::asio::mutable_buffer buff(_buff,sizeof(_buff));
        size_t length=sp->read_some(buff);
        if(length==0)
        {
            return std::string();
        }
        return std::string((const char *)buff.data(),length);
    }
    catch(...)
    {

    }
    return std::string();
}

serialport::~serialport()
{
    if(is_open())
    {
        close();
    }
    if(sp==NULL)
    {
        delete sp;
        sp=NULL;
    }
}


