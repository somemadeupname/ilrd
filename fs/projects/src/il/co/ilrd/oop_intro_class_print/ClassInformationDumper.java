package il.co.ilrd.oop_intro_class_print;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class ClassInformationDumper {

	public static void main(String[] args) throws ClassNotFoundException {
		// TODO Auto-generated method stub
		Class c = Class.forName(args[0]);
		
		System.out.println("canonical name is: " + c.getCanonicalName());
		System.out.println("ClassLoader is: " + c.getClassLoader());
		
		Field[] fs = c.getDeclaredFields();
		
		System.out.println("Fields are:");
		for (Field f : fs) {
			System.out.println(f);
		}
		
		Method[] ms = c.getDeclaredMethods();
		
		System.out.println("Methods are:");
		for (Method m : ms) {
			System.out.println(m);
		}
		
		System.out.println("TypeName: " + c.getTypeName());
		
		
	}

}
