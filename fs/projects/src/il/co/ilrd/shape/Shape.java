package il.co.ilrd.shape;

public class Shape {
	private String color;
	private boolean filled;
	
	Shape () {
		this.color = "green";
		this.filled = true;
	}
	
	Shape(String color, boolean filled) {
		this.color = color;
		this.filled = filled;
	}
	
	public String getColor() {
		return this.color;
	}
	
	public boolean getFilled() {
		return this.filled;
	}
	
	public void setColor(String color) {
		this.color = color;
	}
	
	public void setFilled(boolean filled) {
		this.filled = filled;
	}
	
	public String toString() {
		return ("A shape with color " + this.color + " and " + (this.filled ? "filled" : "Not filled"));
	}
}
