#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

class WeatherData;

class Observers {
public:
    virtual void Update(float t, float h, float p) = 0;
    virtual ~Observers() {
    };
};


class Somebody {
private:
    float temp;
    float humidity;
    float pressure;
    list<Observers *> observers;
public:
    void Attach(Observers & o) {
        observers.push_back(&o);
    }
    void Detach(Observers & o) {
        observers.remove(&o);
    }
    void setMeasurements(float t, float h, float p) {
        temp = 9 / 5 * t + 32;
        humidity = h / 100;
        pressure = p * 133,32; // from mercury column to pascal
        Notify();
    }
    void Notify() {
        for (auto it = observers.begin(); it != observers.end();  it++ ) {
            (*it)->Update(temp, humidity, pressure);
        }
    }
};


class WeatherData {
    float temp = 10;
    float humidity = 20;
    float pressure = 10;
    list<Observers *> observers;

public:
    void measurementsChanged() {
        Notify();
    }
    void Attach(Observers & o) {
        observers.push_back(&o);
    }
    void Detach(Observers & o) {
        observers.remove(&o);
    }
    void setMeasurements (float t, float h, float p) {
        temp = t;
        humidity = h;
        pressure = p;
        measurementsChanged();

    }
    void Notify() {

        for (auto it = observers.begin(); it != observers.end();  it++ ) {
            (*it)->Update(temp, humidity, pressure);
        }
    }
    float getTemperature() {
        return temp;
    }
    float getHumidity() {
        return humidity;
    }
    float getPressure() {
        return pressure;
    }
    ~WeatherData() {
        observers.clear();
    }

};
class CurrentConditionDisplay : public Observers {
    float temperature = 0;
    float humidity = 0;
public:
    void Update(float t, float h, float p){
        cout <<"UPDATE:\n" << t << endl;
        temperature = t;
        humidity = h;
        display();
    }
    void display() {
        cout << "Current condition: Temperature "  <<
             temperature << "; Humidity " << humidity << endl;
    }
};

//class AnotherSubject : public Observers {
//private:
//    float temperature;
//    float humidity;
//    float pressure;
//public:
//    void Update(float t, float h, float p) override {
//        cout << "congrats! everything is now upgraded: /n"
//        <<
//    }
//};

class ForecastConditionDisplay : public Observers {
    float temperature = 0;
    float humidity = 0;
    float pressure = 0;

public:
    void Update(float t, float h, float p){
        temperature = t;
        humidity = h;
        pressure = p;
        display();
    }
    void display() {
        cout << "Forecast info: Temperature "  << temperature+1 << "; Humidity " << humidity+1 <<
             " Pressure  " << pressure << endl;
    }
};

int main() {
    CurrentConditionDisplay current;
    WeatherData wd;
    wd.Attach(current);
    ForecastConditionDisplay another;
    wd.Attach(another);
    wd.setMeasurements(40, 50, 60);

    Somebody sb;
    sb.Attach(current);
    sb.Attach(another);
    sb.setMeasurements(100, 111, 122);
}