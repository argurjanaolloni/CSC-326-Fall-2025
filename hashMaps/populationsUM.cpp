#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;
int main()
{
  // TODO: Create a map
  string country;
  unordered_map<string, int> populations;
  // TODO: Insert 5 country-population pairs
  populations["USA"] = 331002651;
  populations["Albania"] = 2877797;
  populations["Switzerland"] = 8654622;
  populations["Canada"] = 37742154;
  populations["Japan"] = 126476461;
  // TODO: Print all key-value pairs
  for (auto &[country, pop] : populations)
  {
    cout << country << ": " << pop << endl;
  }
  // TODO: Search for a country entered by the user - canada
  cout << "Enter a country to search: ";
  cin >> country;
  if (populations.find(country) != populations.end())
  {
    cout << country << " found with population " << populations[country] << endl;
  }
  else
  {
    cout << country << " not found in the map." << endl;
  }
  return 0;
}
