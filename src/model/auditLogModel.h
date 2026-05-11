/* Alli */
/* 3/14/2026 */
#ifndef AUDITLOG_H
#define AUDITLOG_H

#include <string>
#include <chrono>
#include <Wt/WServer.h>
#include <Wt/Dbo/Dbo.h>

namespace dbo = Wt::Dbo;

class AuditLog : public dbo::Dbo<AuditLog>{
    private:
        std::chrono::system_clock::time_point   timestamp;
        std::string     username;
        std::string     eventType;
        std::string     entityType;
        std::string     details;

    public:
        template<class Action>
        void persist(Action& a)
        {
                dbo::field(a, timestamp, "timestamp");
                dbo::field(a, username, "username");
                dbo::field(a, eventType, "eventType");
                dbo::field(a, entityType, "entityType");
                dbo::field(a, details, "details");
        }
        
        //Constructor
        AuditLog() = default;//delete;
        AuditLog(std::chrono::system_clock::time_point ts, std::string un, 
            std::string evT, std::string enT, std::string d) :
            timestamp(ts), username(un), eventType(evT), entityType(enT), details(d) {
            }

        //Getters
        std::chrono::system_clock::time_point getTimestamp() const {
                return timestamp;
        }
        std::string getUsername() const {
                return username;
        }
        std::string getEventType() const {
                return eventType;
        }
        std::string getEntityType() const {
                return entityType;
        }
        std::string getDetails() const {
                return details;
        }

        //Setters
        void setTimestamp(std::chrono::system_clock::time_point t) {
                timestamp = t;
        }
        void setUsername(const std::string& u) {
                username = u;
        }
        void setEventType(const std::string& e) {
                eventType = e;
        }
        void setEntityType(const std::string& e) {
                entityType = e;
        }
        void setDetails(const std::string& d) {
                details = d;
        }   
};

#endif //AUDITLOG_H
