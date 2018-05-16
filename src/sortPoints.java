import java.util.ArrayList;
import java.util.Random;

public class sortPoints {
	
	public static boolean classify( ArrayList<Pair> a ) {
		ArrayList<Pair> x = new new ArrayList<>();
		ArrayList<Pair> y = new new ArrayList<>();

		x.add(a.getFirst());
		y.add(a.getSecond());

		for ( int i = 0; i < a.size; i++ ) {
			if (i == 0) {
				continue
			} else {
				int tmpX = a.get(i).getFirst();
				int tmpY = a.get(i).getSecond();
				if (tmpX.getFirst() == a.get(0).getFirst()) 
					a.add(tmpX);
				else 
					return false;
				if (tmpY.getSecond() == a.get(0).getSecond()) 
					a.add(tmpY);
				else 
					return false;
			}
		}
	}

	public static void main( String[] argv ) {
		int size = 10
		Random rand = new Random; 
		Pair tmp; 

		ArrayList<Pair> a = new ArrayList<>(size);
		for ( int i = 0; i < size; i++ ) {
			tmp = new Pair(rand.nextInt(5),rand.nextInt(5));
			a.add(tmp);
		}

		System.out.println(a);
		System.out.println(sortPoints.classify(a));


	}

}