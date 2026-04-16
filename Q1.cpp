#include <iostream>
#include <string>
using namespace std;

class User;

class DeviceManagement {
protected:
    string ID;
    string Type;
    double powerRating;
    bool Status;

public:
    DeviceManagement(string id, string type, double rating) {
        ID = id;
        Type = type;
        powerRating = rating;
        Status = false;
    }

    virtual void turnOn() {}
    virtual void turnOff() {}
    virtual double calculatePowerUsage(int hours) { return 0; }
};

class Light : public DeviceManagement {
public:
    Light(string id, string type, double rating)
        : DeviceManagement(id, type, rating) {}

    void turnOn() override {
        Status = true;
        cout << Type << " [ID: " << ID << "] turned ON." << endl;
    }

    void turnOff() override {
        Status = false;
        cout << Type << " [ID: " << ID << "] turned OFF." << endl;
    }

    double calculatePowerUsage(int hours) override {
        return powerRating * hours;
    }
};

class Fan : public DeviceManagement {
protected:
    double speedfactor;

public:
    Fan(string id, string type, double rating, double speed)
        : DeviceManagement(id, type, rating) {
        speedfactor = speed;
    }

    void turnOn() override {
        Status = true;
        cout << Type << " [ID: " << ID << "] turned ON at Speed "
             << speedfactor << "." << endl;
    }

    void turnOff() override {
        Status = false;
        cout << Type << " [ID: " << ID << "] turned OFF." << endl;
    }

    double calculatePowerUsage(int hours) override {
        return powerRating * speedfactor * hours;
    }
};

class AirConditioner : public DeviceManagement {
protected:
    double desiredTemp;
    double currentTemp;

public:
    AirConditioner(string id, string type, double rating, double desiredT)
        : DeviceManagement(id, type, rating) {
        desiredTemp = desiredT;
    }

    void turnOn() override {
        Status = true;
        currentTemp = 33.0;
        cout << Type << " [ID: " << ID << "] turned ON. Cooling to "
             << desiredTemp << "°C." << endl;
    }

    void turnOff() override {
        Status = false;
        cout << Type << " [ID: " << ID << "] turned OFF." << endl;
    }

    double calculatePowerUsage(int hours) override {
        return powerRating * hours *
               (1 - (currentTemp - desiredTemp) / 100);
    }
};

class SecuritySystems : public DeviceManagement {
protected:
    bool securityStatus;

public:
    SecuritySystems(string id, string type, double rating)
        : DeviceManagement(id, type, rating) {
        securityStatus = true;
    }

    void turnOn() override {
        Status = true;
        cout << Type << " [ID: " << ID << "] activated." << endl;
    }

    void turnOff() override {
        cout << "Unauthorized attempt! Security system cannot be turned OFF.\n";
    }

    double calculatePowerUsage(int hours) override {
        cout << "Security System: Includes security checks" << endl;
        return powerRating * hours;
    }

    friend void accessSecurityLogs(User &, SecuritySystems &);

    friend class MaintenanceTool;
};

class User {
    string userID;
    string role;
    int accessLevel;

public:
    User(string id, string r, int level) {
        userID = id;
        role = r;
        accessLevel = level;
    }

    void viewAccessibleDevices() {
        cout << "User: " << userID << " - Accessible Devices:" << endl;
        cout << "- LED Light" << endl;
        cout << "- Ceiling Fan" << endl;
        cout << "- Split AC" << endl;
    }

    string getRole() {
        return role;
    }

    string getID() {
        return userID;
    }

    friend void accessSecurityLogs(User &, SecuritySystems &);
};

void accessSecurityLogs(User &u, SecuritySystems &s) {
    if (u.getRole() == "Maintenance Staff") {
        cout << "User: " << u.getID() << " - Security Logs Accessed:" << endl;
        cout << "- Intrusion Detected at 3:00 AM" << endl;
        cout << "- System Reset Required" << endl;
    } else {
        cout << "Access Denied!" << endl;
    }
}

class MaintenanceTool {
public:
    void resetSystem(SecuritySystems &s) {
        s.securityStatus = false;
        cout << "Security system reset." << endl;
    }
};

int main() {

    User user1("U001", "Regular User", 1);
    User user2("U002", "Maintenance Staff", 2);

    
    Light light1("L001", "LED Light", 10);
    Fan fan1("F001", "Ceiling Fan", 75, 1); // speed factor = 1
    AirConditioner ac1("AC001", "Split AC", 1500, 25);
    SecuritySystems secSys1("S001", "Home Alarm", 100);

    light1.turnOn();
    fan1.turnOn();
    ac1.turnOn();
    secSys1.turnOn();

    cout << endl;


    cout << "Power Consumption:" << endl;
    cout << "LED Light: " << light1.calculatePowerUsage(5) << " Watts" << endl;
    cout << "Ceiling Fan: " << fan1.calculatePowerUsage(3) << " Watts" << endl;
    cout << "Split AC: " << ac1.calculatePowerUsage(6) << " Watts" << endl;
    cout << "Security System: " << secSys1.calculatePowerUsage(24) << " Watts" << endl;

    cout << endl;

    user1.viewAccessibleDevices();
    cout << endl;

    accessSecurityLogs(user2, secSys1);

    return 0;
}
