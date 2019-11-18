package il.co.ilrd.complex_number;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class ComplexNumberTest {
	
	
	private static ComplexNumber createComplexNumber(double real, double imaginary) {
		ComplexNumber num = ComplexNumber.createFromImaginary(imaginary);
		num.setReal(real);
		return num;
	}
	
	@Test
	void addTest() {
		double realOne = 5.6d;
		double realTwo = 2.0d;
		double imageOne = 3.0d;
		double imageTwo = -6.2d;
		
		ComplexNumber num1 = createComplexNumber(realOne, imageOne);
		ComplexNumber num2 = createComplexNumber(realTwo, imageTwo);
		
		ComplexNumber expectedResult = createComplexNumber(realOne + realTwo, imageOne + imageTwo);
		ComplexNumber actualResult = ComplexNumber.add(num1, num2);
		
		assertEquals(expectedResult, actualResult);
	}
	
	@Test
	void subtractTest() {
		double realOne = 0d;
		double realTwo = 0d;
		double imageOne = 0d;
		double imageTwo = -6.2d;
		
		ComplexNumber num1 = createComplexNumber(realOne, imageOne);
		ComplexNumber num2 = createComplexNumber(realTwo, imageTwo);
		
		ComplexNumber expectedResult = createComplexNumber(realOne - realTwo, imageOne - imageTwo);
		ComplexNumber actualResult = ComplexNumber.sub(num1, num2);
		
		assertEquals(expectedResult, actualResult);
	}
	
	@Test
	void multTest() {
		double realOne = 4.0d;
		double realTwo = 1.0d;
		double imageOne = 5.0d;
		double imageTwo = -18.0d;
		
		ComplexNumber num1 = createComplexNumber(realOne, imageOne);
		ComplexNumber num2 = createComplexNumber(realTwo, imageTwo);
		
		ComplexNumber expectedResult = createComplexNumber(94, -67);
		ComplexNumber actualResult = ComplexNumber.mult(num1, num2);
		
		assertEquals(expectedResult, actualResult);
	}
	
	@Test
	void divTest() {
		double realOne = 4.0d;
		double realTwo = 1.0d;
		double imageOne = 5.0d;
		double imageTwo = -18.0d;
		
		ComplexNumber num1 = createComplexNumber(realOne, imageOne);
		ComplexNumber num2 = createComplexNumber(realTwo, imageTwo);
		
		ComplexNumber expectedResult = createComplexNumber(-86.0d/325.0d, 77.0d/325.0d);
		ComplexNumber actualResult = ComplexNumber.div(num1, num2);
		
		assertEquals(expectedResult, actualResult);
		
		realOne = 0.0d;
		realTwo = 0.0d;
		imageOne = 0.0d;
		imageTwo = 0.0d;
		
		num1 = createComplexNumber(realOne, imageOne);
		num2 = createComplexNumber(realTwo, imageTwo);
		
		expectedResult = createComplexNumber(0,0);
		actualResult = ComplexNumber.div(num1, num2);
		
		assertEquals(expectedResult, actualResult);
		
		realOne = 1.0d;
		realTwo = 0.0d;
		imageOne = 0.0d;
		imageTwo = 1.0d;
		
		num1 = createComplexNumber(realOne, imageOne);
		num2 = createComplexNumber(realTwo, imageTwo);
		
		expectedResult = createComplexNumber(0,-1);
		actualResult = ComplexNumber.div(num1, num2);
		
		assertEquals(expectedResult, actualResult);

	}
	
	@Test
	void isRealAndIsImaginary() {
		ComplexNumber imaginaryNum = createComplexNumber(0.0d, 1.0);
		assertTrue(imaginaryNum.isImaginary());
		assertFalse(imaginaryNum.isReal());

		
		ComplexNumber realNum = createComplexNumber(1.0d, 0.0d);
		assertTrue(realNum.isReal());
		assertFalse(realNum.isImaginary());
	}
	
	@Test
	void testHashCode() {
		ComplexNumber num1 = createComplexNumber(0.0d, 1.0);
		ComplexNumber num2 = createComplexNumber(0.0d, 1.0);
		
		assertEquals(num1.hashCode(), num2.hashCode());
		
		num1 = createComplexNumber(0.0d, 1.0);
		num2 = createComplexNumber(1.0d, 0.0);
		
		assertNotEquals(num1.hashCode(), num2.hashCode());

	}
	
	@Test
	void testToString() {
		ComplexNumber num1 = createComplexNumber(-7.0d, 41.0);
		ComplexNumber num2 = createComplexNumber(+-3.0d, +1.0);
		
		System.out.println(num1);
		System.out.println(num2);
	}


}
