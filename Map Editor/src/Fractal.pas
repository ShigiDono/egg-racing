unit Fractal;

interface
uses
  Windows,SysUtils,Graphics,Math, Images, Gauges, FileBin, Dialogs;

type
  Vector = Record
    x,y,z:double;
    end;

const
  NoiseDim=100;

var
  l,t,pos:integer;
  h:array[0..512,0..512] of double;
  NoiseTable:array[0..NoiseDim+1,0..NoiseDim+1,0..NoiseDim+1] of double;
  randseed:longint;
  sx,sy,sz,ma,mi:Double;
  cc1,cc2:TColor;
  ix,iy,iz,jx,jy,jz,__w,__h,val1,val2:integer;
  procedure NoiseInit();
  procedure Generate();
  procedure SetParams(v1,v2:integer);
  procedure Render(c:TCanvas);
  procedure Normalise;
  procedure SetWH(www,hhh:integer);
  procedure SetMM(cl1,cl2:TColor);

implementation
  procedure SetParams(v1,v2:integer);
  begin
    val1:=v1;
    val2:=v2;
  end;

  procedure SetMM(cl1,cl2:TColor);
  begin
    cc1:=cl1;
    cc2:=cl2;
  end;

procedure SetWH(www,hhh:integer);
begin
  __w:=www;
  __h:=hhh;
end;
procedure NoiseInit();
var
  i,j,k:integer;
begin
  for i:=0 to NoiseDim do
    for j:=0 to NoiseDim do
      for k:=0 to NoiseDim do
        NoiseTable[i,j,k]:=Random(1000)/1000;
end;

function converttocolor(x:double;c1,c2:TColor):TColor;
begin
  result:=rgb(round(x*getrvalue(c1))+round((1-x)*getrvalue(c2)),round(x*getgvalue(c1))+round((1-x)*getgvalue(c2)),round(x*getbvalue(c1))+round((1-x)*getbvalue(c2)));
end;

Function IntToVector(x,y,z:double):Vector;
var
  res:vector;
begin
  res.x:=x;
  res.y:=y;
  res.z:=z;
  result:=res;
end;

function InvertColor(C:Tcolor):TColor;
begin
  result:=rgb(255-getrvalue(c),255-getgvalue(c),255-getbvalue(c));
end;

procedure Normalise;
var
i,j:integer;
begin
for i:=0 to __w do
  for j:=0 to __h do
    h[i,j]:=(h[i,j]-mi)/(ma-mi);
end;
function ReturnDouble(X:double):Double;
begin
  Result:=X-Round(X);
end;

function FMod(X:double;Y:Double):Double;
begin
  result:=((round(X*1000) mod round(Y*1000)))/1000;
  if X<0 then result:=-result;
end;

Function Mod1(X,Y:Double):Double;
begin
  X:=FMod(X,Y);
  if x<0 then
    Result:=X+Y
  else
    Result:=X;
end;

procedure Small(var k:Integer);
begin
k:=k mod NoiseDim;
end;

Function Spline(t:Double):Double;
begin
  Result:=t*t*(3-2*t);
end;

procedure Render(c:TCanvas);
var
i,j:integer;
begin
  for i:=0 to 256 do
    for j:=0 to 256 do begin
      try
        c.Pen.Color:=ConvertToColor(h[i,j],cc1,cc2);
        c.MoveTo(i,j);
        c.LineTo(i+1,j+1);
      except
        showmessage('Error on '+inttostr(i)+' '+inttostr(j)+' '+floattostr(h[i,j]));
        end;
    end;
end;

Function Noise(p:Vector):Double;
begin
  sx:=Mod1(p.x,NoiseDim);
  sy:=Mod1(p.y,NoiseDim);
  sz:=Mod1(p.z,NoiseDim);
  ix:=Floor(sx);
  iy:=Floor(sy);
  iz:=Floor(sz);
  jx:=ix+1;
  jy:=iy+1;
  jz:=iz+1;
  if jx>=NoiseDim then
    jx:=0;
  if jy>=NoiseDim then
    jy:=0;
  if jz>=NoiseDim then
    jz:=0;
  sx:=Spline(sx-ix);
  sy:=Spline(sy-iy);
  sz:=Spline(sz-iz);
  Result:=(1-sx) * (1-sy) * (1-sz) * NoiseTable[ix,iy,iz]+
          (1-sx) * (1-sy) * sz     * NoiseTable[ix,iy,jz]+
          (1-sx) * sy     * (1-sz) * NoiseTable[ix,jy,iz]+
          (1-sx) * sy     * sz     * NoiseTable[ix,jy,jz]+
          sx     * (1-sy) * (1-sz) * NoiseTable[jx,iy,iz]+
          sx     * (1-sy) * sz     * NoiseTable[jx,iy,jz]+
          sx     * sy     * (1-sz) * NoiseTable[jx,jy,iz]+
          sx     * sy     * sz     * NoiseTable[jx,jy,jz];
end;

procedure SetZero();//????????? ?????? ??????
var
i,j:integer;
begin
  pos:=0;
  for i:=0 to __w do
    for j:=0 to __h do
      h[i,j]:=0;
end;

function Turbulence(p:Vector;Octaves:integer):double;
var
k,res:double;
r:Vector;
i:integer;
begin
  k:=1;
  res:=0;
  r:=p;
  for i:=0 to Octaves do begin
    res:=res+Noise(r)*k;
    r.x:=r.x *2;
    r.y:=r.y *2;
    r.z:=r.z *2;
    k:=k/2;
  end;
  Result:=res;
end;

procedure Generate();
var
i,j:integer;
begin
  ma:=-67;
  mi:=100;
  for i:=0 to __w do
    for j:=0 to __h do begin try
      h[i,j]:=Turbulence(IntToVector(i/val1,j/val1,1),val2);
      if h[i,j]>ma then ma:=h[i,j];
      if h[i,j]<mi then mi:=h[i,j];
      except
        Messagedlg('Error in generating!',mtError,[mbOk],0);
      end;
    end;
Normalise;
end;


end.
