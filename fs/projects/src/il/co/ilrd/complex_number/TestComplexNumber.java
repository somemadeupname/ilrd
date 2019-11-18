package il.co.ilrd.complex_number;

public class TestComplexNumber {
	
	public static ComplexNumber createComplexNumber(double real, double imaginary) {
		ComplexNumber num = ComplexNumber.createFromImaginary(imaginary);
		num.setReal(real);
		return num;
	}
}
