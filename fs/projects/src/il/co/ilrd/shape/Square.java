package il.co.ilrd.shape;

public class Square extends Rectangle {
	
	private double side;
	
	public Square() {
		this.side = 1.0d;
	}
	
	public Square(double side) {
		this.side = side;
	}
	
	public Square(double side, String color, boolean filled) {
		super(color, filled, side, side);
		this.side = side;
	}
	
	public double getSide() {
		return side;
	}

	public void setSide(double side) {
		this.side = side;
	}

	@Override
	public double getWidth() {
		// TODO Auto-generated method stub
		return side;
	}

	@Override
	public void setWidth(double width) {
		// TODO Auto-generated method stub
		this.side = width;
	}

	@Override
	public double getLength() {
		// TODO Auto-generated method stub
		return side;
	}

	@Override
	public void setLength(double length) {
		// TODO Auto-generated method stub
		side = length;
	}

	@Override
	public double getArea() {
		// TODO Auto-generated method stub
		return side * side;
	}

	@Override
	public double getPerimeter() {
		// TODO Auto-generated method stub
		return 4 * side;
	}

	@Override
	public String toString() {
		// TODO Auto-generated method stub
		return "A Square with blah blah blah";
	}
}
