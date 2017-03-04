#ifndef BROKER_H
#define BROKER_H

#include <string>
#include <vector>
#include <memory>
#include <zmqpp/zmqpp.hpp>
#include "service.h"


class Broker{
private:
    std::string host_;
    std::string port_;
    std::string endpoint_url_;    
    std::unique_ptr<zmqpp::socket> server_;
    std::map<std::string, std::shared_ptr<Service>> services_;
    std::shared_ptr<Service> GetService(std::string service);
    void HandleClient(std::string service, std::string payload);
    void HandleWorker(zmqpp::message msg);
    void HandleInternalCommunication(zmqpp::message msg);
public:
    Broker(std::string qhost, std::string qport);
//    ~Broker();
    void StartBroker();
};

#endif // BROKER_H
