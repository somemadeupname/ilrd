
unsigned int CountSetBitsLoop(unsigned int num)
{
	unsigned int num_of_on_bits = 0;
	unsigned int mask = 1;
	
	while ( num > 0 )
	{
		if ( num & mask )
		{
			++num_of_on_bits;
		}
		num >>= 1;
	}
	return num_of_on_bits;
}
