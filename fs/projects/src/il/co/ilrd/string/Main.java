/*
 * Author: Shieber
 * Reviewer: Grisha
 */
package il.co.ilrd.string;

public class Main {
	
	public static void checkIfPalindrome(String s) {
		if (!Strings.isPalindrome(s))
		{
			System.out.println(s + " is NOT a palindrome.");
		}
	}
	
	public static void swapInPlaceTest(StringBuilder s1, StringBuilder s2)
	{
		StringBuilder sb1 = s1;
		StringBuilder sb2 = s2;
		
		Strings.swapInPlace(sb1, sb2);
		
		if (sb1 == s1 || sb2 == s2 || sb1.equals(sb2) || sb2.equals(sb1))
		{
			return;
		}
		
		System.out.println("swapInPlaceTest failed with " + s1.toString() + " " + s2.toString());
		
	}

	public static void main(String[] args) {
		// is Palindrome test
		
		Main.checkIfPalindrome("helleh");
		Main.checkIfPalindrome("not_a_palindrome");
		Main.checkIfPalindrome("abaabaa");
		Main.checkIfPalindrome("odo");
		Main.checkIfPalindrome("nevven");		
		Main.checkIfPalindrome("");
		
		// printReverse test
		
		Strings.printReverse("reverse");
		Strings.printReverse("lala");
		Strings.printReverse("");
		
		// permutations test
		
		Strings.printAllPermutations("eat");
		Strings.printAllPermutations("");
		
		// swapInPlace
		
		StringBuilder sb1 = new StringBuilder("string1");
		StringBuilder sb2 = new StringBuilder("string2");
		Main.swapInPlaceTest(sb1, sb2);

	}
}