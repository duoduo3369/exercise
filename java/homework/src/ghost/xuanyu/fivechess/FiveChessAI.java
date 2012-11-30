package ghost.xuanyu.fivechess;

public class FiveChessAI {
	private int data_a[][] = new int[5][3];// 用于储存进攻值
	private int data_d[][] = new int[5][3];// 用于储存防守值

	FiveChessAI() {
		// 进攻值的初始化
		data_a[1][1] = 2;
		data_a[1][2] = 3;
		data_a[2][1] = 10;
		data_a[2][2] = 110;
		data_a[3][1] = 2500;
		data_a[3][2] = 3000;
		data_a[4][1] = 99999;
		data_a[4][2] = 99999;
		// 防守值的初始化
		data_d[1][1] = 1;
		data_d[1][2] = 2;
		data_d[2][1] = 1;
		data_d[2][2] = 100;
		data_d[3][1] = 100;
		data_d[3][2] = 500;
		data_d[4][1] = 20000;
		data_d[4][2] = 50000;
	}

	private FiveChessMap g1 = new FiveChessMap();
	private int x, y;

	void find()// 查找最大值
	{
		int max = 0;
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (max < g1.data[i][j]) {
					max = g1.data[i][j];
				}
			}
		}
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				if (max == g1.data[i][j]) {
					x = i;
					y = j;
					return;
				}
			}
		}
	}

	int getx()// 返回x坐标值
	{
		return x;
	}

	int gety()// 返回y坐标值
	{
		return y;
	}

	boolean judge_result(int x, int y, int who, FiveChessMap gm)// 判断胜负
	{
		int m, n, i, lianzi = 0;
		for (m = -1; m <= 1; m++)
			for (n = -1; n <= 1; n++) {
				if (m != 0 || n != 0) {
					for (i = 1; i <= 4; i++) {
						if (x + i * m >= 0 && x + i * m < 15 && y + i * n >= 0
								&& y + i * n < 15
								&& gm.data[x + i * m][y + i * n] == who) {
							lianzi++;
						} else {
							break;
						}
					}
					for (i = -1; i >= -4; i--) {
						if (x + i * m >= 0 && x + i * m < 15 && y + i * n >= 0
								&& y + i * n < 15
								&& gm.data[x + i * m][y + i * n] == who) {
							lianzi++;
						} else {
							break;
						}
					}
					if (lianzi >= 4)

					{
						return true;
					} else {
						lianzi = 0;
					}
				}
			}
		return false;
	}

	void judge(int a, FiveChessMap gm)// 判断全局攻守值
	{
		g1.clear();
		int b = 3 - a;
		int continues1 = 0, continues2 = 0, free = 0;
		for (int x = 0; x < 15; ++x) {
			for (int y = 0; y < 15; ++y) {
				if (gm.data[x][y] == 0) {
					for (int m = -1; m <= 1; ++m) {
						for (int n = -1; n <= 1; ++n) {
							if (m != 0 || n != 0) {
								for (int i = 1; i <= 4; ++i) {
									if (x + i * m < 15
											&& y + i * n < 15
											&& x + i * m >= 0
											&& y + i * n >= 0
											&& gm.data[x + i * m][y + i * n] == a) {
										continues1++;
									} else {
										if (x + i * m < 15
												&& y + i * n < 15
												&& x + i * m >= 0
												&& y + i * n >= 0
												&& gm.data[x + i * m][y + i
														* n] == 0) {
											free++;
										}
										i = 5;
										break;
									}
								}
								for (int i = -1; i >= -4; --i) {
									if (x + i * m < 15
											&& y + i * n < 15
											&& x + i * m >= 0
											&& y + i * n >= 0
											&& gm.data[x + i * m][y + i * n] == a) {
										continues1++;
									} else {
										if (x + i * m < 15
												&& y + i * n < 15
												&& x + i * m >= 0
												&& y + i * n >= 0
												&& gm.data[x + i * m][y + i
														* n] == 0) {
											free++;
										}
										i = -5;
										break;
									}
								}
								if (continues1 == 1) {
									if (free == 1) {
										g1.data[x][y] += data_a[1][1];
									} else if (free >= 2) {
										g1.data[x][y] += data_a[1][2];
									}
								} else if (continues1 == 2) {
									if (free == 1) {
										g1.data[x][y] += data_a[2][1];
									} else if (free >= 2) {
										g1.data[x][y] += data_a[2][2];
									}
								} else if (continues1 == 3) {
									if (free == 1) {
										g1.data[x][y] += data_a[3][1];
									} else if (free >= 2) {
										g1.data[x][y] += data_a[3][2];
									}
								} else if (continues1 >= 4) {
									if (free >= 0) {
										g1.data[x][y] += data_a[4][1];
									} else if (free >= 2) {
										g1.data[x][y] += data_a[4][2];
									}
								}
								free = 0;
								// ///////////////////////进攻////////////////////////////////////
								for (int i = 1; i <= 4; ++i) {
									if (x + i * m < 15
											&& y + i * n < 15
											&& x + i * m >= 0
											&& y + i * n >= 0
											&& gm.data[x + i * m][y + i * n] == b) {
										continues2++;
									} else {
										if (x + i * m < 15
												&& y + i * n < 15
												&& x + i * m >= 0
												&& y + i * n >= 0
												&& gm.data[x + i * m][y + i
														* n] == 0) {
											free++;
										}
										i = 5;
										break;
									}
								}
								for (int i = -1; i >= -4; --i) {
									if (x + i * m < 15
											&& y + i * n < 15
											&& x + i * m >= 0
											&& y + i * n >= 0
											&& gm.data[x + i * m][y + i * n] == b) {
										continues2++;
									} else {
										if (x + i * m < 15
												&& y + i * n < 15
												&& x + i * m >= 0
												&& y + i * n >= 0
												&& gm.data[x + i * m][y + i
														* n] == 0) {
											free++;
										}
										i = -5;
										break;
									}
								}
								if (continues2 == 1) {
									if (free == 1) {
										g1.data[x][y] += data_d[1][1];
									} else if (free >= 2) {
										g1.data[x][y] += data_d[1][2];
									}
								} else if (continues2 == 2) {
									if (free == 1) {
										g1.data[x][y] += data_d[2][1];
									} else if (free >= 2) {
										g1.data[x][y] += data_d[2][2];
									}
								} else if (continues2 == 3) {
									if (free == 1) {
										g1.data[x][y] += data_d[3][1];
									} else if (free >= 2) {
										g1.data[x][y] += data_d[3][2];
									}
								} else if (continues2 >= 4) {
									if (free >= 0) {
										g1.data[x][y] += data_d[4][1];
									} else if (free >= 2) {
										g1.data[x][y] += data_d[4][2];
									}
								}
								continues1 = 0;
								continues2 = 0;
								free = 0;
								// ////////////////////////防守///////////////////////
							}
						}
					}
					// /////////222222222///////////////////////////////////////////////////////////////////
				}
			}
		}
	}
}
