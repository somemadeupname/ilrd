import java.util.*;  

public class Ex4
{
	public static void main(String[] args)
	{
		List<int[]> myList = new ArrayList<int[]>();
		for (int i = 0; i < 1000; ++i)
		{
			myList.add(new int[100000]);
		    Runtime r = Runtime.getRuntime();
	        System.out.println("Total Memory: "+r.totalMemory());  
            System.out.println("Free Memory: "+r.freeMemory());
		}
	}
}
