int _tmp_iMoveLocX[9][37] = {
	// 0
	{0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	// 1
	{0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,16,17,18,19,
	20,-1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	//2
	{0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,16,17,18,19,
	20,20,20,20,20,20,20,20,20,20,
	20,20,20,20,20,20,-1},
	//3
	{20,20,20,20,20,20,20,20,20,20,
	20,20,20,20,20,20,-1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	//4
	{20,20,20,20,20,20,20,20,20,20,
	20,20,20,20,20,20,19,18,17,16,
	15,14,13,12,11,10,9,8,7,6,
	5,4,3,2,1,0,-1},
	//5
	{0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,16,17,18,19,
	20,-1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	//6
	{0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,2,3,4,
	5,6,7,8,9,10,11,12,13,14,
	15,16,17,18,19,20,-1},
	//7
	{0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,-1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	//8
	{0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,2,3,4,
	5,6,7,8,9,10,11,12,13,14,
	15,16,17,18,19,20,-1}
};

int _tmp_iMoveLocY[9][37] = {
	// 0
	{0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	//1
	{0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,-1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	//2
	{0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,-1},
	//3
	{0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,-1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	//4
	{0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,15,15,15,15,
	15,15,15,15,15,15,15,15,15,15,
	15,15,15,15,15,15,-1},
	//5
	{15,15,15,15,15,15,15,15,15,15,
	15,15,15,15,15,15,15,15,15,15,
	15,-1,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	//6
	{0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,15,15,15,15,
	15,15,15,15,15,15,15,15,15,15,
	15,15,15,15,15,15,-1},
	//7
	{0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,15,-1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0},
	// 8
	{15,14,13,12,11,10,9,8,7,6,
	5,4,3,2,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,-1}
};


char _tmp_cTmpDirX[9] = { 0, 0, 1,1,1,0,-1,-1,-1 };
char _tmp_cTmpDirY[9] = { 0,-1,-1,0,1,1, 1, 0,-1 };
