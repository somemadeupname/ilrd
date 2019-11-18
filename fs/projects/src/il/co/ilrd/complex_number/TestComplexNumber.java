package il.co.ilrd.complex_number;

public class TestComplexNumber {
	
	public static ComplexNumber createComplexNumber(double real, double imaginary) {
		ComplexNumber num = ComplexNumber.createFromImaginary(imaginary);
		num.setReal(real);
		return num;
	}
	
	public static void main(String[] args) {
		ComplexNumber num1 = createComplexNumber(5,3);
		System.out.println("num1: " + num1);
		
		ComplexNumber num2 = createComplexNumber(1, 5);
		System.out.println("num2: " + num2);

		System.out.println("addition: " + ComplexNumber.add(num1, num2));
		System.out.println("subtraction: " + ComplexNumber.sub(num1, num2));
		System.out.println("multiplication: " + ComplexNumber.mult(num1, num2));
		System.out.println("division: " + ComplexNumber.div(num1, num2));

	}
}
