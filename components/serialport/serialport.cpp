#include "serialport.h"
#include "boost/asio.hpp"
#include "memory"
#include <thread>
#include <chrono>


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
        std::shared_ptr<size_t> length=std::make_shared<size_t>();
        (*length.get())=0;
#ifdef __WXMSW__
        sp->async_read_some(buff,[=](boost::system::error_code,std::size_t bytes){(*length.get())=bytes;});
        try
        {
            std::chrono::steady_clock::time_point start=std::chrono::steady_clock::now();
            while((*length.get())==0)
            {
                sp_io.get()->run_for(std::chrono::milliseconds(1));
                if(start+std::chrono::milliseconds(500) < std::chrono::steady_clock::now())
                {
                    break;
                }
            }
        }
        catch(...)
        {

        }
#else
        //TODO:非windows下异步读取有问题，暂时使用同步读取
        (*length.get())=sp->read_some(buff);
#endif
        if((*length.get())==0)
        {
            return std::string();
        }
        return std::string((const char *)buff.data(),*(length.get()));
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


