package il.co.ilrd.ws4_enum;

public enum EWeekDay {
	SUNDAY	 (1),
	MONDAY   (2),
	TUESDAY  (3),
	WEDNESDAY(4),
	THURSDAY (5),
	FRIDAY 	 (6),
	SATURDAY (7)
	;
	
	private final int intValue;
	
	private EWeekDay(int intValue) {
		this.intValue = intValue;
	}
	
	public int getIntValue() {
		return this.intValue;
	}
	
	public static EWeekDay fromValue(int intValue) {
		
		EWeekDay[] eWeekDayValues = EWeekDay.values();
		return eWeekDayValues[intValue];
	}
	
	public static void printAllValues() {
		
		for (EWeekDay day : EWeekDay.values()) {
			System.out.println(day);
		}
	}
}