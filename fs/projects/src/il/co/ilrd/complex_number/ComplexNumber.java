package il.co.ilrd.complex_number;

import java.util.Objects;

public class ComplexNumber implements Comparable<ComplexNumber> {
    
	private double real;
    private double imaginary;

    private ComplexNumber() {
        
    	this(0.0,0.0);
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
        
    	double resultReal = num1.getReal() + num2.getReal();
    	double resultImaginary = num1.getImaginary() + num2.getImaginary();
    	
    	return new ComplexNumber(resultReal,resultImaginary);
    }

    public static ComplexNumber sub(ComplexNumber num1, ComplexNumber num2) {
        
    	double resultReal = num1.getReal() - num2.getReal();
    	double resultImaginary = num1.getImaginary() - num2.getImaginary();

    	return new ComplexNumber(resultReal , resultImaginary);
    }

    public static ComplexNumber mult(ComplexNumber num1, ComplexNumber num2) {
        
    	double realProduct = num1.getReal() * num2.getReal() - num1.getImaginary() * num2.getImaginary();
        double imaginaryProduct = num1.getReal() * num2.getImaginary() + num1.getImaginary() * num2.getReal();
    	
        return new ComplexNumber(realProduct, imaginaryProduct);
    }
    
    /*
     *  Returns the conjugate for ComplexNumber @num 
     */
    private static ComplexNumber getConjugate(ComplexNumber num) {
    	
    	return new ComplexNumber(num.getReal(), -num.getImaginary());
    }
    	
    public static ComplexNumber div(ComplexNumber num1, ComplexNumber num2) {
    	
    	ComplexNumber nominatorProduct = ComplexNumber.mult(num1, getConjugate(num2));
    	ComplexNumber denominatorProduct = ComplexNumber.mult(num2, getConjugate(num2));
    	
    	double realQuotient = (nominatorProduct.getReal() / denominatorProduct.getReal());
    	double imaginaryQuotient = (nominatorProduct.getImaginary() / denominatorProduct.getReal());
    	
    	return new ComplexNumber(realQuotient, imaginaryQuotient);
    }

    @Override
    public int compareTo(ComplexNumber num) {
    	
    	double difference = getRelativeDistance(this) - getRelativeDistance(num);
        
        if (difference > 0) {
        	return 1;
        }
        else if (difference < 0) {
        	return -1;
        }
        
        return 0;
    }
    
    /*
     *  Returns the distance of @num from the origin 
     */
    private double getRelativeDistance(ComplexNumber num) {
    	
    	return (Math.sqrt(Math.pow(num.getReal(), 2) + Math.pow(num.getImaginary(), 2)));
    }   

    @Override
    public int hashCode() {
       
    	return Objects.hash(real, imaginary);
    }

    @Override
    public String toString() {
    	
    	String imaginarySign = "+";
    	
    	double absImaginary = imaginary;
    	if (imaginary < 0) {
    		absImaginary = -absImaginary;
    		imaginarySign = "-";
    	}
        
        if (0 == imaginary) {
        	return new Double(real).toString();
        }
        
        else if (0 == real) {
        	return imaginarySign + imaginary + "i"; 
        }
        
        return real + " " + (imaginarySign == "-" ? "-" : "+") + " " + absImaginary + "i";
    }

	@Override
	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}
		if (getClass() != obj.getClass()) {
			return false;
		}
		ComplexNumber other = (ComplexNumber) obj;
		if (this.getReal() != other.getReal()) {
			return false;
		}
		
		if (this.getImaginary() != other.getImaginary()) {
			return false;
		}
		
		return true;		
	}
}