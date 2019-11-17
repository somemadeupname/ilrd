package il.co.ilrd.complex_number;

import java.util.Objects;

public class ComplexNumber implements Comparable<ComplexNumber> {
    private double real;
    private double imaginary;

    private ComplexNumber() {
        this.real = 0.0;
        this.imaginary = 0.0;
    }

    private ComplexNumber(double real, double imaginary) {
        this.real = real;
        this.imaginary = imaginary;
    }

    public static ComplexNumber createFromReal(double real) {
    	return new ComplexNumber(real, 0.0d);
    }

    public static ComplexNumber createFromImaginary(double imaginary) {
        return new ComplexNumber(0.0d, imaginary);
    }

    public double getReal() {
        return real;
    }

    public void setReal(double real) {
        this.real = real;
    }

    public double getImaginary() {
        return imaginary;
    }

    public void setImaginary(double imaginary) {
        this.imaginary = imaginary;
    }

    public boolean isReal() {
        return (0 == imaginary);
    }

    public boolean isImaginary() {
        return ((0 != imaginary) && (0 == real));
    }

    public static ComplexNumber add(ComplexNumber num1, ComplexNumber num2) {
        return new ComplexNumber(num1.getReal() + num2.getReal(), num1.getImaginary() + num2.getImaginary());
    }

    public static ComplexNumber sub(ComplexNumber num1, ComplexNumber num2) {
        return new ComplexNumber(num1.getReal() - num2.getReal(), num1.getImaginary() - num2.getImaginary());
    }

//    (a+bi)×(c+di) = (ac−bd)+(ad+bc)i.
    public static ComplexNumber mult(ComplexNumber num1, ComplexNumber num2) {
        double realProduct = num1.getReal() * num2.getReal() - num1.getImaginary() * num2.getImaginary();
        double imaginaryProduct = num1.getReal() * num2.getImaginary() + num1.getImaginary() * num2.getReal();
    	return new ComplexNumber(realProduct, imaginaryProduct);
    }
    
    private static ComplexNumber getConjugate(ComplexNumber num) {
    	return new ComplexNumber(num.getReal(), -num.getImaginary());
    }
    	
    public static ComplexNumber div(ComplexNumber num1, ComplexNumber num2) {
    	ComplexNumber nominatorProduct = ComplexNumber.mult(num1, getConjugate(num2));
    	ComplexNumber denominatorProduct = ComplexNumber.mult(num2, getConjugate(num2));
    	
    	double realQuotient = nominatorProduct.getReal() / denominatorProduct.getReal();
    	double imaginaryQuotient = nominatorProduct.getImaginary() / denominatorProduct.getReal();
    	
    	return new ComplexNumber(realQuotient, imaginaryQuotient);
    }

    @Override
    public int compareTo(ComplexNumber num) {
        return getRelativeDistance(this) - getRelativeDistance(num);
    }
    
    private int getRelativeDistance(ComplexNumber num) {
    	return (int) (Math.sqrt(Math.pow(real, 2) + (Math.pow(imaginary, 2))));
    }

    @Override
    public boolean equals(Object o) {
        return (0 == compareTo((ComplexNumber) o));
    }

    @Override
    public int hashCode() {
        return Objects.hash(real, imaginary);
    }

    @Override
    public String toString() {
    	
    	String imaginarySign = (0 > imaginary ? "-" : "+");
        
        if (0 == imaginary) {
        	return new Double(real).toString();
        }
        
        else if (0 == real) {
        	return imaginarySign + new Double(imaginary).toString() + "i"; 
        }
        
        return real + " " + (imaginarySign == "-" ? "" : "+") + " " + new Double(imaginary).toString() + "i";
    }
}