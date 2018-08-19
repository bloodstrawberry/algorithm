int parent[5000];
int level[5000];

int Find(int x)
{
	if (x == parent[x]) return x;
	else return parent[x] = Find(parent[x]);
}

void Union(int x, int y)
{
	x = Find(x);
	y = Find(y);
	if (x == y) return;
 
  //더 높은 트리에 더 작은 트리를 넣어야 트리의 높이가 늘지 않는다.
	if (level[x] > level[y])
	{
		int tmp = x;
		x = y;
		y = tmp;
	}
  
	parent[x] = y;

  // 같은 높이의 트리를 합친다면 레벨을 증가시켜준다.
	if (level[x] == level[y]) ++level[y];
}
