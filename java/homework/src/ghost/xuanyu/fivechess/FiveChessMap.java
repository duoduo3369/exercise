package ghost.xuanyu.fivechess;

public class FiveChessMap {
	public int data[][]=new int[15][15];
	
	FiveChessMap()
	{
		for(int i=0;i<15;++i)
		{
			for(int j=0;j<15;++j)
			{
				data[i][j]=0;
			}
		}
	}
	
	public void set_point(int x,int y,int player)
	{
		data[x][y]=player;
	}
	
	public void set_data(int [][]data)
	{
		this.data=data;
	}
	
	public void clear()
	{
		for(int i=0;i<15;++i)
		{
			for(int j=0;j<15;++j)
			{
				data[i][j]=0;
			}
		}
	}
	
	public int[][] getmap()
	{
		return data;
	}
}
