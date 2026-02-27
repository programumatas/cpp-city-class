#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <list>
#include <cassert>

using namespace std;

class City
{
private:
    string cityName;
    int populationSize;
    float areaSize;
    int id;

    static int count;
    static int nextId;

public:
    // Constructors
    City(string name, int population, float area)
    {
        setName(name);
        setPopulation(population);
        setSize(area);
        count++;
        id = nextId++;
    }

    City(string name, int population)
    {
        setName(name);
        setPopulation(population);
        areaSize = round(population / 1500.0f * 100.0f) / 100.0f; // reasonable average for a Lithuanian urban city
        count++;
        id = nextId++;
    }

    // Destructor
    ~City()
    {
        cout << cityName << " has been destroyed.\n";
        count--;
    }

    // Setters
    void setName(string name)
    {
        if (name.empty())
        {
            throw invalid_argument("Name cannot be empty.\n");
        }
        cityName = name;
    }

    void setPopulation(int population)
    {
        if (population < 1)
        {
            throw out_of_range("Population must be at least one.\n");
        }
        populationSize = population;
    }

    void setSize(float size) { areaSize = size; }

    // Getters
    string getName() const { return cityName; }

    int getPopulation() const { return populationSize; }

    float getSize() const { return areaSize; }

    int getId() const { return id; }

    static int getCount() { return count; }

    string toString() const
    {
        stringstream s;
        s << "City: " << cityName << ", Population: " << populationSize << ", Area: " << areaSize << " km²\n";
        return s.str();
    }
};

int City::nextId = 0;
int City::count = 0;

void test1()
{
    City city("Vilnius", 600000, 402);
    string s = city.toString();

    assert(city.getName() == "Vilnius");
    assert(city.getPopulation() == 600000);
    assert(city.getSize() == 402);
    assert(s == ("City: Vilnius, Population: 600000, Area: 402 km²\n"));

    cout << "test1 PASSED\n";
}

void test2()
{
    City city("Kaunas", 450000, 300);
    city.setName("Kaunas2");
    city.setPopulation(450001);
    city.setSize(299);

    assert(city.getName() != "Kaunas");
    assert(city.getPopulation() != 450000);
    assert(city.getSize() != 300);

    cout << "test2 PASSED\n";
}

void test3()
{
    City city("Alytus", 65000, 54.5);

    try
    {
        city.setPopulation(0);
        assert(false && "Expected out_of_range exception was not thrown");
    }
    catch (const out_of_range &e)
    {
        cout << "test3 PASSED\n";
    }
}

void test4()
{
    City city("Utena", 100000, 102);

    int firstId = city.getId();

    City city2("Utena2", 100000, 102);
    City city3("Utena3", 100000, 102);

    assert(city3.getId() == firstId + 2);

    cout << "test4 PASSED\n";
}

void test5()
{
    assert(City::getCount() == 0);
    list<City *> cities;
    cities.push_back(new City("miestas1", 600000, 402));
    cities.push_back(new City("miestas2", 450000, 300));
    cities.push_back(new City("miestas3", 150000, 98));
    assert(City::getCount() == 3);

    for (City *city : cities)
    {
        delete city;
    }
    cities.clear();
    assert(City::getCount() == 0);

    cout << "test5 PASSED\n";
}
int main()
{
    try
    {
        test1();
        test2();
        test3();
        test4();
        test5();
    }
    catch (const exception &e)
    {
        cout << "Unexpected exception: " << e.what();
    }
}