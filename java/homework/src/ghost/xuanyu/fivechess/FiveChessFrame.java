package ghost.xuanyu.fivechess;

import java.awt.BorderLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class FiveChessFrame extends JFrame implements ActionListener,MouseListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private JButton jbu_start=new JButton("开始");
	private JButton jbu_back=new JButton("悔棋");
	private JButton jbu_help=new JButton("AI");
	private JCheckBox jcheck_first=new JCheckBox("先手");
	private FiveChessMap map=new FiveChessMap();
	
	private FiveChessPanel jp_game=new FiveChessPanel();

	private JTextField jt_info=new JTextField("游戏尚未开始",16);
	
	private int x,y;
	
	private int player;
	private int computer;
	private boolean status=false;
	private FiveChessAI ai=new FiveChessAI();
	private FiveChessTemp temp_map=new FiveChessTemp();
	
	
	FiveChessFrame()
	{
		super("五子棋单机版——CSDN游戏部        玄雨制作");
		Toolkit tool = Toolkit.getDefaultToolkit();
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		int width = 505, height = 593;
		this.setSize(width, height);
		this.setResizable(false);
		this.setLocation((tool.getScreenSize().width - width) / 2,
				(tool.getScreenSize().height - height) / 2);
		this.setLayout(new BorderLayout());
		add_buttons();
		add_game_panel();
		add_tittle();
		
	}
	
	private void add_tittle()
	{
		JPanel jp=new JPanel();
		jp.add(new JLabel("五子棋——单机版"));
		this.add(jp,BorderLayout.NORTH);
	}
	
	private void add_game_panel()
	{
		JPanel jp=new JPanel();
		jp.setLayout(new BorderLayout());
		jp.add(jp_game);
		jp_game.setdata(map.getmap());
		jp_game.addMouseListener(this);
		this.add(jp,BorderLayout.CENTER);
	}
	
	private void add_buttons()
	{
		JPanel jp=new JPanel();
		JPanel jp_center=new JPanel();
		JPanel jp_west=new JPanel();
		jp.add(jp_west,BorderLayout.WEST);
		jp_west.add(new JLabel("状态："));
		jp_west.add(jt_info);
		jt_info.setEnabled(false);
		jp_center.add(jcheck_first);
		jcheck_first.setSelected(true);
		jp_center.add(jbu_start);
		jp_center.add(jbu_back);
		jp_center.add(jbu_help);
		jp.add(jp_center,BorderLayout.CENTER);
		jbu_back.setEnabled(false);
		jbu_help.setEnabled(false);
		jbu_start.addActionListener(this);
		jbu_back.addActionListener(this);
		jbu_help.addActionListener(this);
		this.add(jp,BorderLayout.SOUTH);
	}
	
	private void start()
	{
		map.clear();
		status=true;
		if(jcheck_first.isSelected())
		{
			player=1;
			computer=2;
		}
		else
		{
			player=2;
			computer=1;
			map.set_point(7, 7, computer);
		}
		jbu_back.setEnabled(true);
		jbu_help.setEnabled(true);
		jbu_start.setEnabled(false);
		jcheck_first.setEnabled(false);
		jt_info.setText("游戏已经开始请落子!");
		jp_game.setdata(map.data);
		jp_game.update();
	}
	
	private boolean temp_use()
	{
		for(int i=0;i<15;++i)
		{
			for(int j=0;j<15;++j)
			{
				if(map.data[i][j]!=0)
				{
					return false;
				}
			}
		}
		return true;
	}
	
	private void regret()
	{
		map.set_data(temp_map.pop().getmap());
		if(temp_use())
		{
			if(!jcheck_first.isSelected())
			{
				map.set_point(7, 7, computer);
			}
		}
		jp_game.setdata(map.getmap());
		jp_game.update();
	}
	
	private void aihelp()
	{
		ai.judge(player, map);
		ai.find();
		map.set_point(ai.getx(), ai.gety(), player);
		jt_info.setText("电脑帮你落子为x："+ai.getx()+"y:"+ai.gety());
		jp_game.setdata(map.getmap());
		jp_game.update();
		if(ai.judge_result(ai.getx(), ai.gety(), player, map))
		{
			jt_info.setText("玩家胜利");
			gameover();
		}
		ai.judge(computer, map);
		ai.find();
		map.set_point(ai.getx(), ai.gety(), computer);
		jt_info.setText("电脑落子为x："+ai.getx()+"y:"+ai.gety());
		jp_game.setdata(map.data);
		jp_game.update();
		temp_map.push(map);
		if(ai.judge_result(ai.getx(), ai.gety(), computer, map))
		{
			jt_info.setText("电脑胜利");
			gameover();
		}
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		switch(e.getActionCommand())
		{
		case "开始":
			start();
			break;
		case "悔棋":
			regret();
			break;
		case "AI":
			aihelp();
			break;
		case "再来":
			start();
			break;
		}
	}
	
	private boolean setpoint(int getx,int gety)
	{
		if(getx<=15||getx>=483||gety<=17||gety>=485)
		{
			return false;
		}
		x=(int) ((Double.valueOf(getx)-15)/31.5);
		y=(int) ((Double.valueOf(gety)-17)/31.5);
		return true;
	}
	
	private void gameover()
	{
		jbu_start.setText("再来");
		jbu_start.setEnabled(true);
		jbu_back.setEnabled(false);
		jbu_help.setEnabled(false);
		jcheck_first.setEnabled(true);
		status=false;
	}
	
	private void clicked(int getx,int gety)
	{
		if(status&&setpoint(getx,gety))
		{
			if(map.getmap()[x][y]==0)
			{
				map.set_point(x, y, player);
				jt_info.setText("玩家落子为x："+x+"y:"+y);
				jp_game.setdata(map.data);
				jp_game.update();
				if(ai.judge_result(x, y, player, map))
				{
					jt_info.setText("玩家胜利");
					gameover();
				}
				ai.judge(computer, map);
				ai.find();
				map.set_point(ai.getx(), ai.gety(), computer);
				jt_info.setText("电脑落子为x："+ai.getx()+"y:"+ai.gety());
				jp_game.setdata(map.data);
				jp_game.update();
				temp_map.push(map);
				if(ai.judge_result(ai.getx(), ai.gety(), computer, map))
				{
					jt_info.setText("电脑胜利");
					gameover();
				}
			}
			else
			{
				jt_info.setText("当前位置不能落子");
			}
		}
		else
		{
			jt_info.setText("游戏尚未开始");
		}
	}
	
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		clicked(e.getX(),e.getY());
		
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
	}
}
