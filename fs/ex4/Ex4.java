import java.util.*; 

public class Ex4
{
	public static void main(String[] args) throws InterruptedException
	{
		List<int[]> myList = new ArrayList<int[]>();
		while (true)
		{
			myList.add(new int[100000]);
			Runtime r = Runtime.getRuntime();
		    System.out.println("Total Memory (in bytes):\t "+r.totalMemory());  
	        System.out.println("Free Memory: (in bytes):\t "+r.freeMemory());
	        Thread.sleep(100);
		}
	}
}
