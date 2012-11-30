package ghost.xuanyu.fivechess;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import javax.swing.ImageIcon;
import javax.swing.JPanel;

public class FiveChessPanel extends JPanel{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private Image image_back;
	private Image image_white;
	private Image image_black;
	
	private final Double stat_x=28.5;
	private final Double stat_y=30.0;
	private final Double chess_size=26.0;
	private final Double board_box_size=31.5;
	
	private int[][] data;
	
	public FiveChessPanel()
	{
		image_back=new ImageIcon("board.jpg").getImage();
		image_white=new ImageIcon("white.png").getImage();
		image_black=new ImageIcon("black.png").getImage();
	}
	
	public void setdata(int [][]a)
	{
		data=a;
	}
	
	public void update()
	{
		repaint(10,10,480,480);
	}
	
	public void paint(Graphics g)
	{
		g.drawImage(image_back, 10, 10, 480, 480, null);
		Graphics2D g2d=(Graphics2D)g;
		g2d.translate(stat_x-chess_size/2, stat_y-chess_size/2);
		for(int i=0;i<15;++i)
		{
			for(int j=0;j<15;++j)
			{
				if(data[i][j]!=0)
				{
					g2d.translate(board_box_size*i, board_box_size*j);
					if(data[i][j]==1)
					{
						g2d.drawImage(image_white, 0, 0, null);
					}
					else
					{
						g2d.drawImage(image_black, 0, 0, null);
					}
					g2d.translate(-board_box_size*i, -board_box_size*j);
				}
			}
		}
		
	}

}
