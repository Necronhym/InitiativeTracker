#include "GetFromFile.h"
std::string GetFromFile(const char* string, const char* file)
	{
		//Teporary coinainter file variable:
		std::ifstream tempfile(file);
		//Error check if file opened propperly:
		if(tempfile.is_open())
			{	
				//Temporary string storage:
				std::string tempstring;
				//Looks for string though the file line by line until end of file:
				while(!tempfile.eof())
		 			{
						std::getline(tempfile, tempstring);
						if(tempstring.find(string) == 0)
							{
								//Cleanns up and returns the string:
								tempfile.close();
								return tempstring.erase(0, strlen(string)+1);
							}
					}
				//Clean up:
				tempfile.close();
				//If file not found returns error:
			}
	}
int StringToInt(std::string string)
	{
		//temporary integer container
		int x;
		//temporary string strem gonainer
		std::stringstream s(string);
		//Converts the string to an integer
		s >> x;
		return x;
	}
