#include <iostream>
#include<windows.h>
#include<math.h>

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
struct pos{
int x,y;
};
struct line{
pos *v1,*v2;
};
int dx=150,dy=40;
pos vertex[100];
int vertexnr=1;
line lines[100];
int linesnr= 0;
bool numbermod;
pos newpos(int x, int y){
pos n;
n.x = x;
n.y = y;
return n;
}

float dis(pos p1,pos p2){
return sqrt(((p1.x-p2.x)*(p1.x-p2.x))+((p1.y-p2.y)*(p1.y-p2.y)));
}

bool pointinline(pos point,pos *t1, pos *t2){
float n,dx,dy;;
pos v1 = *t1;
pos v2 = *t2;
int miny,maxy,minx,maxx;
if(v1.y>=v2.y){
miny= v2.y;
maxy = v1.y;
}else{
miny= v1.y;
maxy = v2.y;
}
if(v1.x>=v2.x){
minx= v2.x;
maxx = v1.x;
}else{
minx= v1.x;
maxx = v2.x;
}
if(v1.x==v2.x){
  if((point.y>miny)&&(point.y<maxy)&&(point.x==maxx)){
    return true;
   }else{
    return false;
   }
}
if(v1.y==v2.y){
  if((point.y==miny)&&(point.x>minx)&&(point.x<maxx)){
    return true;
   }else{
    return false;
   }
}


dx=v1.x-v2.x;
dy=v1.y-v2.y;
if (dy==0||dx==0){
    n=0;
}else{
n = dy/dx;
}

float b = v2.y - (float)(n * v2.x);
float xn = (float)(n*point.x) ;
bool online;
float mn;
if(n>=0){
        mn=n;
}
else{
    mn=-n;
}
float dens = (mn + 0.5f)/1.5f;
if((point.y <= (float)(xn +b+dens))&&(point.y >= (float)(xn+b -dens))){
  online= true;
}else{
    online = false;
}

  if(online&&(point.y>=miny)&&(point.y<=maxy)&&(point.x>=minx)&&(point.x<=maxx)){
    return true;
}else{
    return false;
}
}

int selected[100]={0,1},selectednr=1;
int movespeed = 1;
bool multiselect;
void display(){
system("CLS");
SetConsoleTextAttribute(hConsole, 7);
cout<<"movespeed:"<<movespeed<<"  numbermod:"<<numbermod<<" vertexnr:"<<vertexnr<<" linesnr:"<<linesnr<<"  multiselect:"<<multiselect<<"  selected nr:"<<selectednr;cout<<"  selected:";for(int p=0;p<selectednr;p++){cout<<selected[p];if(p<(selectednr-1))cout<<",";}
pos cur;
bool detect;
for(int i=dy;i>=1;i--){
    for(int j = 1;j<=dx;j++){
        detect=false;
        cur=newpos(j,i);
        for(int l= 0;l<selectednr&&!detect;l++){
        if(cur.x==vertex[selected[l]].x&&cur.y==vertex[selected[l]].y){
            detect=true;
            SetConsoleTextAttribute(hConsole, 4);
            if(!numbermod){
            cout<<"*";
            }else{
            cout<<selected[l];
            }
        }
        }
        if(!detect)
        for(int l= 0;l<=vertexnr&&!detect;l++){
        if(cur.x==vertex[l].x&&cur.y==vertex[l].y){
            detect=true;
            SetConsoleTextAttribute(hConsole, 7);
            if(!numbermod){
            cout<<"*";
            }else{
            cout<<l;
            }
        }
        }
        if(!detect){
        for(int l = 0;l<linesnr&&!detect;l++)
        if(pointinline(cur, lines[l].v1 , lines[l].v2)){
            SetConsoleTextAttribute(hConsole, 7);
            detect=true;
            cout<<"#";
        }
       }
       if(!detect){
        cout<<" ";
       }
    }
    cout<<endl;
}
}


void movevertexe(int mx,int my){
    int sel;
for(int i = 0;i<selectednr;i++){
    sel = selected[i];
    vertex[sel]=newpos(vertex[sel].x+mx,vertex[sel].y+my);
}
}

void makeline(pos *v1,pos *v2){
bool exist=false;
for(int i =0;i<linesnr;i++){
if((lines[i].v1==v1&&lines[i].v2==v2)||(lines[i].v1==v2&&lines[i].v2==v1))exist=true;
}
if(!exist){
linesnr++;
lines[linesnr-1].v1 = v1;
lines[linesnr-1].v2 = v2;
}
}

void deleteline(pos *v1,pos *v2){
int k;
bool exist=false;
for(k =0;k<linesnr;k++){
if((lines[k].v1==v1&&lines[k].v2==v2)||(lines[k].v1==v2&&lines[k].v2==v1)){exist=true;
break;}
}
if(!exist){
linesnr--;
for(int j=k;j<=linesnr;j++){
lines[j].v1 = lines[j+1].v1;
lines[j].v2 = lines[j+1].v2;
}
}
}
void selwithnr(){
int n;
cout<<"how many to select:";cin>>n;
selectednr=n;
for(int i =0;i<n;i++){
cin>>selected[i];
}
}

void addselect(int add){
selectednr++;
selected[selectednr-1]=add;
}


void onlyselected(int only){
selectednr=1;
selected[selectednr-1]=only;
}

void deletevertex(int poz){
int l;
if(poz<=vertexnr){
for(int k=0;k<=vertexnr;k++){
    if(k!=poz)
    deleteline(&vertex[k],&vertex[poz]);
}}
for(l = poz;l<=vertexnr;l++){
    for(int k  =0;k<=vertexnr;k++){
          for(int h =0;h<linesnr;h++){
            if(lines[h].v1==&vertex[l]&&lines[h].v2==&vertex[k])
             lines[h].v1=&vertex[l-1];
            if(lines[h].v1==&vertex[k]&&lines[h].v2==&vertex[l])
             lines[h].v2=&vertex[l-1];
    }
    vertex[l]=vertex[l+1];
  }
}
vertexnr--;
selectednr=0;
}

int detectedvertex(){

}

void help(){
system("CLS");
cout<<"controlls:"<<endl;

Sleep(500);
cout<<"press enter to continue";
cin.get();
}

void extrude(){
int p,j;
j=selectednr;
for(p=0;p<j;p++){
vertexnr++;
vertex[vertexnr]=vertex[selected[p]];
makeline(&vertex[vertexnr],&vertex[selected[p]]);
if(p==0){
onlyselected(vertexnr);
}else{
addselect(vertexnr);
}}
}

void input(){
if(GetKeyState(VK_SHIFT) & 0x8000){
 if(multiselect){
  multiselect=false;
}else{
multiselect=true;
}
}
if(GetKeyState('W') & 0x8000){

}
 if(GetKeyState('A') & 0x8000){

}
 if(GetKeyState('S') & 0x8000){

}
 if(GetKeyState('D') & 0x8000){

}
if(GetKeyState('F') & 0x8000){
    selectednr=1;
    selected[0]++;
    if(selected[0]>vertexnr){
        selected[0]=0;
    }
}

if(GetKeyState(VK_CONTROL) & 0x8000){
    if(!numbermod){
    numbermod=true;
    }else{
    numbermod=false;
    }
}
if(GetKeyState(VK_ADD) & 0x8000){
    movespeed++;
}
if(GetKeyState(VK_SUBTRACT) & 0x8000){
    if(movespeed>0)
    movespeed--;
}
if(GetKeyState(VK_LEFT) & 0x8000){
    movevertexe(movespeed*(-1),0);
}
if(GetKeyState(VK_RIGHT) & 0x8000){
    movevertexe(movespeed,0);
}
if(GetKeyState(VK_UP) & 0x8000){
   movevertexe(0,movespeed);
}
if(GetKeyState(VK_DOWN) & 0x8000){
    movevertexe(0,movespeed*(-1));
}

if(GetKeyState('J') & 0x8000 && selectednr==2){
    makeline(&vertex[selected[0]],&vertex[selected[1]]);
}
if(numbermod && GetKeyState('N') & 0x8000){
    display();
    selwithnr();
}
if(GetKeyState('Q') & 0x8000){
        int x,y;
    cin>>x;cin>>y;
    vertexnr++;
    vertex[vertexnr]=newpos(x,y);
    selectednr=1;
    selected[0] = vertexnr;
}
if(GetKeyState('H') & 0x8000){
    help();
}
if(GetKeyState('E') & 0x8000){
    extrude();
}
if(GetKeyState(VK_DELETE) & 0x8000){
    for(int i=0;i<selectednr;i++)
    deletevertex(selected[i]);
}
if(GetKeyState('K') & 0x8000 && selectednr==2){
    deleteline(&vertex[selected[0]],&vertex[selected[1]]);
}
}

int main()
{
    vertex[0] = newpos(10,10);
    vertex[1] = newpos(15,18);
    makeline(&vertex[0],&vertex[1]);
    while(true){
     input();
     display();
     Sleep(500);
    }
    return 0;
}
