import java.io.*;

public class Test
{
	public static void main(String args[])
	{
		try
		{
			BufferedWriter bw = new BufferedWriter(new FileWriter("file.txt"));

			bw.write("baris\n");
			bw.write("ayyildiz\n");
			bw.write(String.valueOf(true) + "\n");
			bw.write(String.valueOf(2) + "\n");

			

			bw.close();

			String s;

			BufferedReader br = new BufferedReader(new FileReader("file.txt"));

			while((s = br.readLine()) != null)
			{
				System.out.println(s.length());
			}


		}catch(Exception ex)
		{

		}



	}
}
