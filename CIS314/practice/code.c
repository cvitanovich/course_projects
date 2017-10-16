int accum = 0;

int sum(x,y)
int x,y;
{
	int t = x + y;
	accum += t;
	return t;
}
