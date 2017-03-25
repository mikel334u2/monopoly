#include <iostream>
#include <string>

class boardView
{
	private:
		string property;
		string location;

	public:
	
		string getProperty()
		{
			return property;
		}

		string getLocation()
		{
			return location;
		}

		string setProperty(string property)
		{
			this.property = property;
		}

		string setLocation(string location)
		{
			this.locaction = location;
		}	

}