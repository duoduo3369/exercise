package ghost.xuanyu.fivechess;

public class FiveChessTemp {
	FiveChessMap data[]=new FiveChessMap[130];
	int size=0;
	FiveChessTemp()
	{
		
	}
	
	public void clear()
	{
		size=0;
	}
	
	public void push(FiveChessMap map)
	{
		data[size]=new FiveChessMap();
		for(int i=0;i<15;++i)
		{
			for(int j=0;j<15;++j)
			{
				data[size].data[i][j]=map.data[i][j];
			}
		}
		size++;
	}
	
	public FiveChessMap pop()
	{
		if(size==1)
		{
			size=0;
			return new FiveChessMap();
		}
		else if(size==0)
		{
			return new FiveChessMap();
		}
		size--;
		return data[size-1];
	}
}
