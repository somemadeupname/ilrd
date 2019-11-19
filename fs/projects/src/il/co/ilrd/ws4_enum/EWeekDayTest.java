package il.co.ilrd.ws4_enum;

public class EWeekDayTest {

	public static void main(String[] args) {
		
		EWeekDay.printAllValues();
		System.out.println(EWeekDay.fromValue(5));
		
		EWeekDay day = EWeekDay.SUNDAY;
		System.out.println(day.getIntValue());
		
	}   
        
}       
        