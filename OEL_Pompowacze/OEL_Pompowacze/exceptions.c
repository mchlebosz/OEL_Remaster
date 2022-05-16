#include "exceptions.h"

void exception_out_of_range()
{
	puts("\nIndex out of range!");
	exit(-1);
}

void exception_allocation_error()
{
	puts("\nMemory allocation went wrong!");
	exit(-1);
}

void exception_wrong_type()
{
	puts("\nData types are not the same size!");
	exit(-1);
}
