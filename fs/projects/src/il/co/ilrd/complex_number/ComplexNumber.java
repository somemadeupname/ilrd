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

    public ComplexNumber createFromReal(double real) {
    	return new ComplexNumber(real, 0.0d);
    }

    public ComplexNumber createFromImaginary(double imaginary) {
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
        return ((0 != real) && (0 == imaginary));
    }

    public boolean isImaginary() {
        return ((0 != imaginary) && (0 == real));
    }

    public static ComplexNumber add(ComplexNumber num1, ComplexNumber num2) {
        return null;
    }

    public static ComplexNumber sub(ComplexNumber num1, ComplexNumber num2) {
        return null;
    }

    public static ComplexNumber mult(ComplexNumber num1, ComplexNumber num2) {
        return null;
    }

    public static ComplexNumber div(ComplexNumber num1, ComplexNumber num2) {
        return null;
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
        return "";
    }
}