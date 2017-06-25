#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <queue>
#include <vector>
#include <memory>
#include <thread>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <uuid/uuid.h>
#include "boggartqueue.h"
#include "boggartworker.h"


struct Worker{
    std::string address; // address to use when routing messages
    int expiry; // time to expire before heartbeat

    Worker(std::string addr, int expire=0){
        address = addr;
        expiry = expire;
    }
};


class Service{
private:
    std::string servicename_;
    std::unordered_map<int, std::shared_ptr<BoggartWorker>> registered_workers_; // holds workers who have issued a READY cmd and are still active
    BoggartQueue<std::shared_ptr<BoggartWorker>> workers_; // Holds workers that are active and are being shuffled in between jobs
    BoggartQueue<std::pair<std::string, std::string>> jobs_; // holds the jobs to be processed by workers
    BoggartQueue<std::pair<std::string, std::string>> async_job_results_; // holds the result of asynchronous job results
    BoggartQueue<std::pair<std::string, std::string>> sync_job_results_; // // holds the result of synchronous job results

public:
    Service(std::string servicename);
    std::string GetResult(std::string jobid, bool sync=false);
    void AddJob(std::string workpayload);
    void RegisterWorker(std::shared_ptr<BoggartWorker> worker);
    void AddWorker(std::shared_ptr<BoggartWorker> worker);
    bool WorkerExists(int fd);
    int TotalJobs();
    void ConsumeJob();    
};



#endif // SERVICE_H
