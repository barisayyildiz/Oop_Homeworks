import java.util.*;

public class Test
{
	public static void main(String args[])
	{
		int a1[][] = null;

		a1 = initArray(5);

		// a1 = initArray(12);
		print(a1, 5);
	}

	public static int[][] initArray(int x)
	{
		int temp[][] = new int[x][x];

		for(int i=0; i<x; i++)
		{
			for(int j=0; j<x; j++)
			{
				temp[i][j] = i+j;
			}
		}

		return temp;
	}

	public static void print(int arr[][], int x)
	{
		for(int i=0; i<x; i++)
		{
			for(int j=0; j<x; j++)
			{
				System.out.print(arr[i][j]);
			}
			System.out.println();
		}
	}

}
