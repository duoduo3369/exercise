package just_for_fun;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;

public class CopyFile {
	/**
	 * nio����
	 * 
	 * @param inFile
	 *            Դ�ļ�
	 * @param outFile
	 *            Ŀ���ļ�
	 * @return
	 * @throws Exception
	 */
	public static long FileChannelCopy(String inFile, String outFile)
			throws Exception {
		long begin = System.currentTimeMillis();
		File in = new File(inFile);
		File out = new File(outFile);
		FileInputStream fin = new FileInputStream(in);
		FileOutputStream fout = new FileOutputStream(out);
		FileChannel inc = fin.getChannel();
		FileChannel outc = fout.getChannel();
		int bufferLen = 1024 * 1024 * 2; //2M
		ByteBuffer bb = ByteBuffer.allocateDirect(bufferLen);
		while (true) {
			int ret = inc.read(bb);
			if (ret == -1) {
				fin.close();
				fout.flush();
				fout.close();
				break;
			}
			bb.flip();
			outc.write(bb);
			bb.clear();
		}
		long end = System.currentTimeMillis();
		long runtime = 0;
		if (end > begin)
			runtime = end - begin;
		return runtime;

	}

	/**
	 * io����
	 * 
	 * @param inFile
	 *            Դ�ļ�
	 * @param outFile
	 *            Ŀ���ļ�
	 * @return
	 * @throws Exception
	 */
	public static long FileStraeamCopy(String inFile, String outFile)
			throws Exception {
		long begin = System.currentTimeMillis();

		File in = new File(inFile);
		File out = new File(outFile);
		FileInputStream fin = new FileInputStream(in);
		FileOutputStream fout = new FileOutputStream(out);

		int length = 1024 * 1024 * 2;// 2m�ڴ�
		byte[] buffer = new byte[length];

		while (true) {
			int ins = fin.read(buffer);
			if (ins == -1) {
				fin.close();
				fout.flush();
				fout.close();
				break;

			} else
				fout.write(buffer, 0, ins);

		}
		long end = System.currentTimeMillis();
		long runtime = 0;
		if (end > begin)
			runtime = end - begin;
		return runtime;

	}

	static public void main(String args[]) throws Exception {
		String inFile = "D:/��Ӱ/[��Ӱ����www.dy2018.net].��Ӱ����4.720p.BD��Ӣ˫��Ļ.rmvb"; // Դ�ļ�
		///*
		String outFile = "F:/copymovie1.rmvb"; // ����ļ�1		
		long runtime1;
		runtime1 = FileChannelCopy(inFile, outFile);
		System.out.println("FileChannelCopy running time:" + runtime1);
		//*/
		/*
		long runtime2;
		String outFile2 = "F:/copymovie2.rmvb"; // ����ļ�2
		runtime2 = FileStraeamCopy(inFile, outFile2);
		System.out.println("FileStraeamCopy running time:" + runtime2);
		//*/
	}
}