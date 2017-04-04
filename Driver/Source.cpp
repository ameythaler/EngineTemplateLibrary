#include "Utility/LogStream.h"

using ETL::Utility::LogOutStream;

int main(int argc, char** argv)
{
	LogOutStream str;
	str << "Hello World!";
	
	return 0;
}