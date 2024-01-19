#include <iostream>
#include <memory>
#include <string>

class CustomerComm {
protected:
    unsigned int customer_id;

public:
    CustomerComm(unsigned int id) : customer_id(id) {}

    // Getter for customer_id
    unsigned int getCustomerId() const {
        return customer_id;
    }

    // Setter for customer_id
    void setCustomerId(unsigned int id) {
        customer_id = id;
    }

    // Virtual function for sending a message
    virtual void send_message(std::string_view message) const {
        //do nothing
    }
};

class CustomerEmail : virtual protected CustomerComm {
private:
    std::string email_address;

public:
    CustomerEmail(unsigned int id, const std::string& email) : CustomerComm(id), email_address(email) {}

    // Getter for email_address
    const std::string& getEmailAddress() const {
        return email_address;
    }

    // Setter for email_address
    void setEmailAddress(const std::string& email) {
        email_address = email;
    }

    // Override send_message method
    void send_message(std::string_view message) const override {
        std::cout << "Sending email " << message << " to " << "{ID: " << getCustomerId() << "} at " << getEmailAddress() << std::endl;
    }
};

class CustomerSms : virtual protected CustomerComm {
private:
    std::string mobile_telephone;

public:
    CustomerSms(unsigned int id, const std::string& mobile) : CustomerComm(id), mobile_telephone(mobile) {}

    // Getter for mobile_telephone
    const std::string& getMobileTelephone() const {
        return mobile_telephone;
    }

    // Setter for mobile_telephone
    void setMobileTelephone(const std::string& mobile) {
        mobile_telephone = mobile;
    }

    // Override send_message method
    void send_message(std::string_view message) const override {
        std::cout << "Sending SMS " << message << " to " << "{ID: " << getCustomerId() << "} on " << getMobileTelephone() << std::endl;
    }
};

class CustomerMob : virtual protected CustomerComm {
private:
    std::string mobile_telephone;

public:
    CustomerMob(unsigned int id, const std::string& mobile)
        : CustomerComm(id), mobile_telephone(mobile) {}

    // Getter and setter for mobile_telephone
    const std::string& getMobileTelephone() const {
        return mobile_telephone;
    }

    void setMobileTelephone(const std::string& mobile) {
        mobile_telephone = mobile;
    }

    // Override send_message method
    void send_message(std::string_view message) const override {
        std::cout << "Sending mobile message " << message << " to " << "{ID: " << getCustomerId() << "} on " << getMobileTelephone() << std::endl;
    }
};

class CustomerSpec : public CustomerMob, public CustomerSms {
public:
    using CustomerMob::getMobileTelephone;  // Bring getMobileTelephone into scope

    CustomerSpec(unsigned int id, const std::string& email, const std::string& mobile)
        : CustomerComm(id), CustomerMob(id, mobile), CustomerSms(id, mobile) {}

    // Override send_message method
    void send_message(std::string_view message) const override {
        std::cout << "Sending specialised comms "<< message << " to " << "{ID: " << getCustomerId() << "} on " << getMobileTelephone() << std::endl;
    }

    void route_ab() {
        std::cout << "AB method" << std::endl;
    }
};


int main() {

    // Create instances of each type with test data using auto
    auto emailPtr = std::make_unique<CustomerEmail>(1001, "jane.@example.com");
    auto smsPtr = std::make_unique<CustomerSms>(1002, "+771234567890");
    auto mobPtr = std::make_unique<CustomerMob>(1003, "+779876543210");
    auto specPtr = std::make_unique<CustomerSpec>(1004, "special.customer@example.com", "+771234563210");

    // Call send_message method for each
    emailPtr->send_message("Hello!");
    smsPtr->send_message("Hola!");
    mobPtr->send_message("Bonjour!");
    specPtr->send_message("Konnichiwa!");
    specPtr->route_ab();

    return 0;
}

