package il.co.ilrd.string;

public class Strings {
	
	public static boolean isPalindrome(String str)
	{
		for (int left = 0, right = (str.length() - 1); (left != right) && (right > left); ++left, --right)
		{
			if (str.charAt(left) != str.charAt(right))
			{
				return false;
			}
		}
		
		return true;
	}
	
	public static void printReverse(String str)
	{		
		for (int i = (str.length() - 1); i >= 0; --i)
		{
			System.out.print(str.charAt(i));
		}
		System.out.println(""); // add newline

	}
	
	public static void printAllPermutations(String str)
	{
		permute(str, 0, str.length() - 1);
	}
	
	private static void permute(String str, int left, int right)
	{
		if (left == right)
		{
			System.out.println(str);
			return;
		}
		
		for (int i = left; i <= right; ++i)
		{
			str = swap(str, left, i);
			permute(str, left + 1, right);
			str = swap(str, left, i);
		}
	}
	
	private static String swap(String str, int left, int right)
	{
		char[] charArray = str.toCharArray();
		char tempChar = charArray[left];
		charArray[left] = charArray[right];
		charArray[right] = tempChar;
		
		return String.valueOf(charArray);
	}
	
	public static void swapInPlace(StringBuilder s1, StringBuilder s2)
	{
		StringBuilder tempSb = new StringBuilder(s1);
		
		s1.replace(0, s1.length(), s2.toString());
		s2.replace(0, s2.length(), tempSb.toString());		
	}
}
