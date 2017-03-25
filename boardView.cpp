#include <iostream>
#include <string>

class boardView
{
	private:
		string property;
		int location;

	public:
	
		string getProperty()
		{
			return property;
		}

		int getLocation()
		{
			return location;
		}

		setProperty(string property)
		{
			this.property = property;
		}

		setLocation(int location)
		{
			this.location = location;
		}	

}