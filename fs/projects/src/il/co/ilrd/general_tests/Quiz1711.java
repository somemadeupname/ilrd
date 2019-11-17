package il.co.ilrd.general_tests;

import java.util.Arrays;

public class Quiz1711 {
	public static void foo(int i) {System.out.println("int ...");};	
	public static void foo(short i) {System.out.println("short");};
	public static void foo(long i) {System.out.println("long");};
	public static void foo(Integer i) {System.out.println("Integer");};
	
	public static void main(String[] args) {
//		foo(10);
		int[] arr1 = {1,2,3,4,5};
		int[] arr2 = {1,2,3,4,5};
		
//		System.out.println(arr1 == arr2);
//		System.out.println(Arrays.toString(arr1));		
//		System.out.println(Arrays.equals(arr1, arr2));
		
		Integer i = (11);
		Integer k = (11);
		
		System.out.println(i == k);
		
	}

}
