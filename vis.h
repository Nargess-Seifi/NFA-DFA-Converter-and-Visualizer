#include <bits/stdc++.h>
#include <graphics.h>
#define PI 3.14159265
using namespace std;

void addEdge(vector< pair<int,int> > [],int,int,int);
void diplayGraph(vector< pair<int,int> > [],int);
vector< pair<int,int> > getCoords(int);
vector< pair<int,int> > getCoords2(int);
vector<string> names;
set<string> finals;


//int main()
//{
//    int n,e;
//    cout<<"Enter the no. of Vertices: ";cin>>n;
//    cout<<"Enter the no. of Edges: ";cin>>e;
//    vector< pair<int,int> > arr[n];
//    int c1,c2,weight;
//    cout<<"Enter connection as in ' a,b,weight ' and remember node starts from 0:-"<<endl;//or 'from A:-'
//    for (int i=0;i<e;i++)
//    {
//        scanf("%d,%d,%d",&c1,&c2,&weight);
//        addEdge(arr,c1,c2,weight);
//    }
//
//    //////////////////
//
//    int gd=DETECT,gm;
//    initgraph(&gd, &gm, ""); //or  "C:\\TC\\BGI"
//    diplayGraph(arr,n);
//    getch();
//    closegraph();
//    return 0;
//}

void getNames(vector<string> v, set<string> s){
	names.clear();
	names = v;
	finals.clear();
	finals = s;
}
void addEdge(vector< pair<int,char> > arr[],int u, int v,char weight){
    arr[u].push_back(make_pair(v,weight));  //arr[u-'A'].push_back(v-'A') if you decide to enter letters, also change below line
//    arr[v].push_back(make_pair(u,weight));  //comment this line for directed graph from u to v
}

void diplayGraph(vector< pair<int,char> > arr[],int n)
{
    vector< pair<int,int> > coords = getCoords(n); //this returns coords in circular form
   // vector< pair<int,int> > coords = getCoords2(n);   //this returns coords in random manner,
   //uncomment line above and comment line above the above line to use this

    //  Time to draw Edges
    vector< pair<int,char> >::iterator i;
    char str[5];
    map<int, int> mp;
    for(int f=0;f<n;f++)//this is just printing all edges from each node no., therefore it can be further optimized
    {
    	mp.clear();
        for(i = arr[f].begin();i <  arr[f].end();i++) //f can be acknowledged as from
        {
        	
        	if(mp.find((*i).first)==mp.end()){
        		mp[(*i).first] = -15;
        	}
        	mp[(*i).first]+=15;
        	int ofset = mp[(*i).first];
        	
        	if((*i).first==f){
        		circle(coords[f].first+20,coords[f].second+20,10);
        		sprintf(str,"%c",(*i).second);
        		if(ofset>0) outtextxy(coords[f].first+30+ofset-5, coords[f].second+30, ",");
        		outtextxy(coords[f].first+30+ofset, coords[f].second+30, str);
        		outtextxy(coords[f].first+25, coords[f].second+25, "*");
        		continue;
        	}
        	
        	
            line(coords[f].first,coords[f].second,coords[(*i).first].first,coords[(*i).first].second);
           	sprintf(str,"%c",(*i).second);
           	if(ofset>0) outtextxy(((coords[f].first - coords[(*i).first].first))/3 + coords[(*i).first].first - 5 + ofset-5,((coords[f].second - coords[(*i).first].second))/3 + coords[(*i).first].second -7,",");
            outtextxy(((coords[f].first - coords[(*i).first].first))/3 + coords[(*i).first].first - 5 + ofset,((coords[f].second - coords[(*i).first].second))/3 + coords[(*i).first].second -7,str); //5 and 7 are random no. to relocate acc. to perfect viewing
            outtextxy((5*coords[(*i).first].first + coords[f].first)/6,(5*coords[(*i).first].second + coords[f].second)/6,"*");
            //uncomment above line for directed graph, this is section formula (co-ordinate geometry)
        }
    }

    //  Time to draw Points
    char symbol[1];
    strcpy(symbol,"A");// or "A"
//    setbkcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    for(int i=0;i<coords.size();i++)
    {
        setcolor(LIGHTGRAY);
    	if(finals.find(names[i])!=finals.end()){
    		circle(coords[i].first,coords[i].second,20);
//    		floodfill(coords[i].first+1,coords[i].second+1,GREEN);
    	}
        circle(coords[i].first,coords[i].second,15);//you can take any radius; a hollow circle of light-gray color is formed
//        floodfill(coords[i].first+1,coords[i].second+1,LIGHTGRAY); //fill every thing except light-gray,thus forming boundary
        setcolor(WHITE);
        outtextxy(coords[i].first-5,coords[i].second-7,&names[i][0]);//5 and 7 are random no. to relocate acc. to perfect viewing
        *symbol+=1;     //increments the ASCII first char of symbol array i.e. symbol itself
    }
}

vector< pair<int,int> > getCoords(int n)
{
    int cenX=getmaxx()/2,cenY=getmaxy()/2; //finding center
    vector< pair<int,int> > coords; //Co-ordinates
    int x,y;
    x=0;
    y=(25*n); //25 is just a no. it could be anything.
    coords.push_back(make_pair(x+cenX,cenY+y));      //A.K.A. Translation of Origin (geometry)
   for(int i=1;i<n;i++)
   {
    int newX=(x*cos(2*PI/n) - y*sin(2*PI/n));       //counter-clock-wise rotation
    y=(y*cos(2*PI/n) + x*sin(2*PI/n));
    x=newX;
    coords.push_back(make_pair(x+cenX,cenY+y));
   }
   return coords;
}


vector< pair<int,int> > getCoords2(int n)
{
    int maxX=getmaxx()-30,maxY=getmaxy()-30; //-30 to create bottom and right boundary, +15 later
    vector< pair<int,int> > coords; //Co-ordinates
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
    	coords.push_back(make_pair((rand()%maxX)+15,(rand()%maxY)+15));//+15 to create top and left boundary
    //since radius is 15 so boundary are made to keep them inside screen
	}
    return coords;
}
