package il.co.ilrd.shape;

public class TestShape {

	public static void main(String[] args) {
		
		Shape s1 = new Circle("red", false, 5.5);
        
        System.out.println(s1);
        System.out.println(s1.getArea());
        System.out.println(s1.getPerimiter());
        System.out.println(s1.getColor());
        System.out.println(s1.isFilled());
        
        Circle c1 = (Circle)s1;
        
        System.out.println(c1);
        System.out.println(c1.getArea());
        System.out.println(c1.getPerimiter());
        System.out.println(c1.getColor());
        System.out.println(c1.isFilled());
        System.out.println(c1.getRadius());
        
        
        Shape s3 = new Rectangle("red", false, 1.0, 2.0);
        
        System.out.println(s3);
        System.out.println(s3.getArea());
        System.out.println(s3.getPerimiter());
        System.out.println(s3.getColor());
        
        Rectangle r1 = (Rectangle)s3;
        
        System.out.println(r1);
        System.out.println(r1.getArea());
        System.out.println(r1.getColor());
        System.out.println(r1.getLength());
        
        Shape s4 = new Square(6.6);
        
        System.out.println(s4);
        System.out.println(s4.getArea());
        System.out.println(s4.getColor());
        
        Rectangle r2 = (Rectangle)s4;
        
        System.out.println(r2);
        System.out.println(r2.getArea());
        System.out.println(r2.getColor());
        System.out.println(r2.getLength());
        
        Square sq1 = (Square)r2;
        
        System.out.println(sq1);
        System.out.println(sq1.getArea());
        System.out.println(sq1.getColor());
        System.out.println(sq1.getSide());
        System.out.println(sq1.getLength());
        
	}

}