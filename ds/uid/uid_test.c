#include <assert.h>
#include "uid.h"

/* Forward Declarations */
void TestUIDCreateMultipleUIDsInASecond();
void TestUIDIsSameNotTheSame();
void TestUIDIsSame();

int main()
{
	TestUIDCreateMultipleUIDsInASecond();
	
	TestUIDIsSameNotTheSame();
	
	TestUIDIsSame();
	
	return 0;
}

void TestUIDCreateMultipleUIDsInASecond()
{
	uid_t u1 = UIDCreate();
	uid_t u2 = UIDCreate();
	size_t loop_times = 0;
	for (loop_times = 0; loop_times < 50; ++loop_times)
	{
		assert(0 == UIDIsSame(u1,u2));
		u1 = UIDCreate();
		u2 = UIDCreate();
	}
}

void TestUIDIsSameNotTheSame()
{
	uid_t u1 = UIDCreate();
	uid_t u2 = UIDCreate();
	assert(0 == UIDIsSame(u1,u2));
}

void TestUIDIsSame()
{
	uid_t u = UIDCreate();
	assert(1 == UIDIsSame(u,u));
}
