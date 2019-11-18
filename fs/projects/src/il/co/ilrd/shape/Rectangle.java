package il.co.ilrd.shape;

public class Rectangle extends Shape {
	private double width;
	private double length;
	
	public Rectangle() {
		this.width = 1.0d;
		this.length = 1.0d;
	}
	
	public Rectangle(double width, double length) {
		this.width = width;
		this.length = length;
	}
	
	public Rectangle(String color, boolean filled, double width, double length) {
		super(color, filled);
		this.width = width;
		this.length = length;
	}

	public double getWidth() {
		return width;
	}

	public void setWidth(double width) {
		this.width = width;
	}

	public double getLength() {
		return length;
	}

	public void setLength(double length) {
		this.length = length;
	}
	
	public double getArea() {
		return (this.width * this.length);
	}
	
	public double getPerimeter() {
		return ( 2 * (this.width + this.length));
	}
	
	@Override
	public String toString() {
		return ("A Rectangle with width=" + this.width + " and length="
				+ this.length + ", which is subclass of" + super.toString());
				
	}
}
