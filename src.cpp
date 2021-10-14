#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>
void help()
{
	std::cout<<"-o open text file"<<std::endl;
	std::cout<<"-s set speed of words in seconds"<<std::endl;
	std::cout<<"-i index of where reading should start, default value will be starting or where last left for the same file"<<std::endl;
	std::cout<<"If starting a new file while the previous one was left in the middle, run the new one with an option of \"-i 1\""<<std::endl;
	std::cout<<"-h display this help message"<<std::endl;
}
int main(int argc,char* argv[])
{
	int index=1,counter=1;
	float speed=0.5;
	char ch;
	bool started=false;
	std::string line="",content="";
	std::ifstream data;
	//detecting if windows or not for clear command
	#if defined(_WIN32)
		#define CLEAR "cls"
	#else
		#define CLEAR "clear"
	#endif
	//checking if an index value is already set
	std::string liner;
	std::ifstream datar;
	datar.open("index.txt");
	while(datar>>line)
	{
		index=std::stoi(line);
		break;
	}
	datar.close();
	//taking command line arguments
	while((ch=getopt(argc,argv,"o: s: i: h"))!=EOF)
	{
		started=true;
		switch(ch)
		{
			case 'o':
				content=optarg;
				break;
			case 's':
				speed=atof(optarg);
				break;
			case 'i':
				index=atoi(optarg);
				break;
			case 'h':
				help();
				return 0;
			default:
				return 1;
		}
	}
	//preparring for display
	data.open(content);
	system(CLEAR);
	while(data>>line)
	{
		if(index>counter)//ignoring already read lines
		{
			counter++;
			continue;
		}
		started=true;
		std::cout<<line<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(int(speed*1000)));
		index++;
		counter++;
		//saving current index value
		std::ofstream dataw;
		dataw.open("index.txt");
		dataw<<index;
		dataw.close();
		system(CLEAR);
	}
	data.close();
	//resetting index
	std::ofstream dataw;
	dataw.open("index.txt");
	dataw<<"1"<<std::endl;
	dataw.close();
	if(!started) help();
	return 0;
}
