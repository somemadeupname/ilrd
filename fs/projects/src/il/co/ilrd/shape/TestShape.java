package il.co.ilrd.shape;

public class TestShape {

	public static void main(String[] args) {
		Shape defaultShape = new Shape();
		System.out.println(defaultShape.getColor());
		System.out.println(defaultShape.getFilled());
		System.out.println(defaultShape);
		System.out.println("Change to red and not filled:");
		defaultShape.setColor("red");
		defaultShape.setFilled(false);
		System.out.println(defaultShape.getColor());
		System.out.println(defaultShape.getFilled());
		System.out.println(defaultShape);
		
		Circle circle = new Circle();
		System.out.println(circle);
		Circle nonDefaultCircle = new Circle(4.7d);
		System.out.println(nonDefaultCircle.getPerimeter());
		System.out.println(nonDefaultCircle.getArea());
		System.out.println(circle.getArea());
		System.out.println(circle.getPerimeter());
		
		Circle nonDefaultCircle2 = new Circle("yellow", false, 6.8d);
		System.out.println(nonDefaultCircle2);
		System.out.println(nonDefaultCircle2.getArea());
		System.out.println(nonDefaultCircle2.getPerimeter());
		

	}

}
