
import java.net.*;
import java.io.*;

/**
 * @author  yeeku.H.lee kongyeeku@163.com
 * @version  1.0
 * <br>Copyright (C), 2005-2008, yeeku.H.Lee
 * <br>This program is protected by copyright laws.
 * <br>Program Name:
 * <br>Date: 
 */
public class MyClient
{
    public static void main(String[] args)
		throws IOException 
    {
		Socket s = s = new Socket("127.0.0.1" , 30000);
		//客户端启动ClientThread线程不断读取来自服务器的数据
		new Thread(new ClientThread(s)).start();
		//获取该Socket对应的输出流
		PrintStream ps = new PrintStream(s.getOutputStream());
		String line = null;
		//不断读取键盘输入
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while ((line = br.readLine()) != null)
		{
			//将用户的键盘输入内容写入Socket对应的输出流
			ps.println(line);
		}
    }
}
