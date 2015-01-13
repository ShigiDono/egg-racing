unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, DXDraws, ComCtrls, ExtCtrls, SCControl, SCColorControls,
  StdCtrls, Spin, Math, Images, Gauges, FileBin,Fractal;

type
  TForm1 = class(TForm)
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    Edit1: TMenuItem;
    N1: TMenuItem;
    New1: TMenuItem;
    Open1: TMenuItem;
    Save1: TMenuItem;
    Exit1: TMenuItem;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    TabSheet3: TTabSheet;
    TabSheet4: TTabSheet;
    DXDraw1: TDXDraw;
    DXDraw2: TDXDraw;
    DXDraw3: TDXDraw;
    PageControl2: TPageControl;
    TabSheet5: TTabSheet;
    TabSheet6: TTabSheet;
    TabSheet7: TTabSheet;
    Label1: TLabel;
    SpinEdit1: TSpinEdit;
    Label2: TLabel;
    Label3: TLabel;
    StatusBar1: TStatusBar;
    Button1: TButton;
    Button2: TButton;
    SpinEdit2: TSpinEdit;
    Shape1: TShape;
    Label4: TLabel;
    SpinEdit3: TSpinEdit;
    CheckBox1: TCheckBox;
    Button3: TButton;
    Gauge1: TGauge;
    Label5: TLabel;
    SpinEdit4: TSpinEdit;
    ComboBox1: TComboBox;
    Label6: TLabel;
    Label7: TLabel;
    OpenDialog1: TOpenDialog;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    Button9: TButton;
    Button10: TButton;
    Shape2: TShape;
    Shape3: TShape;
    Timer1: TTimer;
    Button11: TButton;
    SaveDialog1: TSaveDialog;
    Shape4: TShape;
    Shape5: TShape;
    Button12: TButton;
    Button13: TButton;
    Button14: TButton;
    Button15: TButton;
    Button16: TButton;
    Button17: TButton;
    Button18: TButton;
    SaveDialog2: TSaveDialog;
    OpenDialog2: TOpenDialog;
    ComboBox2: TComboBox;
    Label8: TLabel;
    Edit2: TEdit;
    ComboBox3: TComboBox;
    Label9: TLabel;
    Label10: TLabel;
    CheckBox2: TCheckBox;
    Export1: TMenuItem;
    GroupBox1: TGroupBox;
    Label11: TLabel;
    Shape6: TShape;
    ColorDialog1: TColorDialog;
    View1: TMenuItem;
    Redraw1: TMenuItem;
    Edit3: TEdit;
    Edit4: TEdit;
    Shape7: TShape;
    Shape8: TShape;
    ComboBox4: TComboBox;
    Button19: TButton;
    Button20: TButton;
    Button21: TButton;
    Button22: TButton;
    Button23: TButton;
    Button24: TButton;
    Button25: TButton;
    SpinEdit5: TSpinEdit;
    Label12: TLabel;
    Label13: TLabel;
    CheckBox3: TCheckBox;
    Edit5: TEdit;
    Label14: TLabel;
    CheckBox4: TCheckBox;
    SaveDialog3: TSaveDialog;
    GroupBox2: TGroupBox;
    Button26: TButton;
    SpinEdit6: TSpinEdit;
    Label15: TLabel;
    Label16: TLabel;
    SpinEdit7: TSpinEdit;
    SpinEdit8: TSpinEdit;
    Label17: TLabel;
    SpinEdit9: TSpinEdit;
    Label18: TLabel;
    CheckBox5: TCheckBox;
    Button27: TButton;
    Panel1: TPanel;
    GroupBox3: TGroupBox;
    Edit6: TEdit;
    Label19: TLabel;
    Edit7: TEdit;
    procedure FormCreate(Sender: TObject);
    procedure DXDraw1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure DXDraw1MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure DXDraw1MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure FormPaint(Sender: TObject);
    procedure SpinEdit2Change(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure DXDraw2MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button11Click(Sender: TObject);
    procedure DXDraw2MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure DXDraw2MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure New1Click(Sender: TObject);
    procedure Save1Click(Sender: TObject);
    procedure Open1Click(Sender: TObject);
    procedure Edit2Change(Sender: TObject);
    procedure ComboBox3Change(Sender: TObject);
    procedure ComboBox2Change(Sender: TObject);
    procedure Export1Click(Sender: TObject);
    procedure Shape6MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Redraw1Click(Sender: TObject);
    procedure DXDraw3MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure DXDraw3MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure DXDraw3MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Button26Click(Sender: TObject);
    procedure Button27Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
  CRect=record
    c1,c2,c3,c4:TColor;
    seed:byte;
  end;
const
  defrad=5;
var
  Form1: TForm1;
  bract,bract1,bract2:boolean;
  hbitmap,cbitmap:tbitmap;
  w,h,x1,y1,x2,y2,dx,dy,ts,wd,hd:integer;
  xx:array[1..2] of integer;
  yy:array[1..2] of integer;
  ss:array[0..300] of string; //texture path...
  nms:array[0..300] of string; //model path...
  mp:array[0..300,0..100] of string; //model path...
//  coord:array[0..300,0..300] of single;
  scmi:array[0..300,0..100] of single;
  scma:array[0..300,0..100] of single;
  cn:array[0..300] of integer; //count
  ic:array[0..300] of integer; //this is for temporary saving of tile indices
  hw:array[0..300,0..1] of integer; //width/height
  bb:array[0..300,0..64] of char; //indicates tile components
  Colors:array[1..65535] of TColor;
  SColors:array[1..65535] of TColor;
  Doods:array[0..65535] of word;
  Sc:array[0..65535] of single;
  Coord:array[0..65535,0..1] of single;
  Rot:array[0..65535] of single;
  ng:array[0..65535] of boolean;
  DoodCount:integer=0;
  DoodIndC:integer=0;
  zoom:double=1;
  DoodInd:array[0..300,0..1] of word;
  rcts:array[0..1024] of CRect;
  aipoints:array[0..1024,0..1] of single;
  rcnt,nic,aic:integer;

implementation

uses Unit2;

{$R *.dfm}
procedure removeDoods(x,y:single);
var
  rad,dist:single;
  i,de:integer;
begin
  rad:=sqr(form1.SpinEdit5.Value*zoom);
  de:=0;
  if doodcount=0 then exit;
  for i:=0 to doodcount-1 do begin
    if i+de>doodcount-1 then break;
    dist:=sqr(x-Coord[i+de,0])+sqr(y-Coord[i+de,1]);
    if dist<rad then
    begin
      Doods[i+de]:=Doods[DoodCount-1];
      coord[i+de,0]:=coord[DoodCount-1,0];
      coord[i+de,1]:=coord[DoodCount-1,1];
      Rot[i+de]:=Rot[DoodCount-1];
      ng[i+de]:=ng[DoodCount-1];
      sc[i+de]:=sc[DoodCount-1];
      dec(de);
      dec(DoodCount);
    end;
  end;
//  form1.Repaint;
end;
procedure RefreshDood();
var
  act:array[0..300] of boolean;
  i,de,j:integer;
begin
  for i:=0 to 300 do begin
    act[i]:=false;
  end;
  for i:=0 to DoodCount-1 do begin
    if i>DoodCount-1 then break;
    act[Doods[i]]:=true;
  end;
  de:=0;
  if Doodindc>0 then begin
    for i:=0 to Doodindc-1 do
    begin
      if (de<>0) and (act[i+de]) then begin
        if doodcount<>0 then
          for j:=0 to doodcount-1 do begin
            if doods[j]=i then doods[j]:=doods[j]-de;
          end;
      end;
      if i+de>Doodindc-1 then break;
      if not act[i+de] then begin
        Doodind[i+de,0]:=Doodind[Doodindc-1,0];
        Doodind[i+de,1]:=Doodind[Doodindc-1,1];
        de:=de-1;
        dec(doodindc);
      end;
    end;
  end;
end;

function __add(i1,i2:integer):word;
var
  i:integer;
begin
  Result:=0;
  if DoodIndC<>0 then begin
    for i:=0 to DoodIndC-1 do begin
      if (DoodInd[i,0]=i1) and (DoodInd[i,1]=i2) then begin
        Result:=i;
        exit;
      end;
    end;
  end;
  Result:=doodindc;
  DoodInd[doodindc,0]:=i1;
  DoodInd[doodindc,1]:=i2;
  inc(doodindc);
end;

procedure CreateDoodoad(x,y:single);
var
  s,sss,rtt:single;
  ii,r:integer;
begin
  ii:=form1.ComboBox4.ItemIndex;
  r:=random(cn[ii]);
  sss:=random(1000);
  if form1.CheckBox3.Checked then
  rtt:=pi*2*random(1000)/1000
  else
  rtt:=strtofloat(form1.Edit5.Text)*pi/180;
  rot[doodcount]:=rtt;
  ng[doodcount]:=form1.CheckBox4.Checked;
  s:=(scma[form1.ComboBox4.ItemIndex,0]-scmi[form1.ComboBox4.ItemIndex,0])*sss/1000+scmi[form1.ComboBox4.ItemIndex,0];
  sc[DoodCount]:=s;
  Doods[DoodCount]:=__add(ii,r);
  Coord[doodcount,0]:=x;
  Coord[doodcount,1]:=y;

  inc(DoodCount);
  form1.repaint;
end;

function indbycol(c:Tcolor):word;
begin
  Result:=1;
  while Colors[Result]<>c do inc(Result);
end;
function maxseed(c:Tcolor):integer;
var
  i,j:integer;
begin
  i:=indbycol(c);
  Result:=0;
  for j:=0 to hw[i-1,0]*hw[i-1,1]-1 do begin
    if bb[i-1,j]=#15 then inc(Result);
  end;
end;

function indbyseed(x,d:integer):integer;
var
  i,j:integer;
begin
  i:=0;
  Result:=0;
  for j:=0 to hw[x-1,0]*hw[x-1,1]-1 do begin
    if (bb[x-1,j]=#15) then inc(i);
    if i=d then begin
      Result:=j;
      exit;
    end;
  end;
end;

function indbytile(x:integer;d:byte):integer;
var
  j:integer;
begin
  Result:=0;
  for j:=0 to hw[x-1,0]*hw[x-1,1]-1 do begin
    if bb[x-1,j]=chr(d) then begin
      Result:=j;
      exit;
    end;
  end;
end;
procedure AddAIPoint(x,y:single);
begin
  aipoints[aic,0]:=x;
  aipoints[aic,1]:=y;
  inc(aic);
end;
function Add(c1,c2,c3,c4:TColor):word;
var
  i,s:integer;
begin
  if (((c1=c2) and (c2=c3)) and (c3=c4)) then
  s:=random(maxseed(c1))
  else
  s:=0;
  for i:=0 to rcnt do begin
    if (((rcts[i].c1=c1) and (rcts[i].c2=c2))
    and ((rcts[i].c3=c3) and (rcts[i].c4=c4))) and (rcts[i].seed=s) then begin
      Result:=i;
      exit;
    end;
  end;
  rcts[rcnt].c1:=c1;
  rcts[rcnt].c2:=c2;
  rcts[rcnt].c3:=c3;
  rcts[rcnt].c4:=c4;
  rcts[rcnt].seed:=s;
  result:=rcnt;
  inc(rcnt);
end;

function _add(x:integer):word;
var
  i:integer;
begin
  for i:=0 to nic-1 do
    if ic[i]=x then begin
      Result:=i;
      exit;
    end;
  ic[nic]:=x;
  Result:=nic;
  inc(nic);
end;

procedure _Write(f:CFile);
var
  st,_w,_h,i,j,k,mc:integer;
  tcol:Tcolor;
  tmask:byte;
  masks:array[0..4] of byte;
  marked:array[0..4] of boolean;
  cols:array[0..4] of TColor;
begin
  st:=1;
  while st<rcnt do st:=st*2;
  _w:=round(sqrt(st));
  while st mod _w<>0 do begin
    dec(_w);
  end;
  _h:=st div _w;
  f.WriteInt(ts);
  f.WriteInt(_w);
  f.WriteInt(_h);
  if rcnt>1024 then begin
    showmessage('Error! Limit of tiles was exceded! File '+f.filename+' was not saved!'+#13+#10+'-Possible ways-'+#13+#10+'-Try to remove some tiles from the map.'+#13+#10+'-Change size of the map.');
    exit;
  end;
  f.WriteInt(rcnt);
  nic:=0;
  for i:=0 to rcnt-1 do begin
    mc:=0;
    marked[0]:=false;
    marked[1]:=false;
    marked[2]:=false;
    marked[3]:=false;
    with rcts[i] do begin
      marked[0]:=true;
      mc:=1;
      cols[0]:=c1;
      masks[0]:=1 shl 3;
      //1
      if c1=c2 then begin
        masks[0]:=masks[0]+1 shl 2;
        marked[1]:=true;
      end;
      if c1=c3 then begin
        masks[0]:=masks[0]+1 shl 1;
        marked[2]:=true;
      end;
      if c1=c4 then begin
        masks[0]:=masks[0]+1;
        marked[3]:=true;
      end;
      //2
      if not marked[1] then begin
        mc:=mc+1;
        cols[mc-1]:=c2;
        masks[mc-1]:=1 shl 2;
        if (c2=c3) and not(marked[2]) then begin
          masks[mc-1]:=masks[mc-1]+1 shl 1;
          marked[2]:=true;
        end;
        if (c2=c4) and not(marked[3]) then begin
          masks[mc-1]:=masks[mc-1]+1;
          marked[3]:=true;
        end;
      end;
      //3
      if not marked[2] then begin
        mc:=mc+1;
        cols[mc-1]:=c3;
        masks[mc-1]:=1 shl 1;
        if (c3=c4) and not(marked[3]) then begin
          masks[mc-1]:=masks[mc-1]+1;
          marked[3]:=true;
        end;
      end;
      //4
      if not marked[3] then begin
        mc:=mc+1;
        cols[mc-1]:=c4;
        masks[mc-1]:=1;
      end;
    end;
    f.WriteChar(chr(mc));
    if rcts[i].seed>0 then begin
      f.WriteWord(_add(indbycol(rcts[i].c1)));//cols[j-1])));//word(indbycol(rcts[i].c1)));
      f.WriteWord(word(indbyseed(indbycol(rcts[i].c1),rcts[i].seed)));
    end
    else
    begin
      for j:=1 to mc do begin
        for k:=j+1 to mc do begin
          if k>mc then exit;
          if indbycol(cols[j-1])>indbycol(cols[k-1]) then begin
            tcol:=cols[j-1];
            cols[j-1]:=cols[k-1];
            cols[k-1]:=tcol;
            tmask:=masks[j-1];
            masks[j-1]:=masks[k-1];
            masks[k-1]:=tmask;
          end;
        end;
      end;
      for j:=1 to mc do begin
        f.WriteWord(_add(indbycol(cols[j-1])));
        f.WriteWord(word(indbytile(indbycol(cols[j-1]),masks[j-1])));
      end;
    end;
  end;
{
  for i:=0 to rcnt-1 do begin
    if ((rcts[i].c1=rcts[i].c2) and (rcts[i].c2=rcts[i].c3)) and (rcts[i].c3=rcts[i].c4) then
    begin
      break;
    end;
  end;
}
  k:=ic[0]-1;
  f.WriteInt(k);
  for j:=0 to hw[k,0]*hw[k,1]-1 do begin
    if bb[k,j]=#15 then begin
      f.WriteInt(j);
      break;
    end;
  end;

{    f.WriteWord(indbycol(rcts[i].c1)-1);
    f.WriteWord(indbycol(rcts[i].c2)-1);
    f.WriteWord(indbycol(rcts[i].c3)-1);
    f.WriteWord(indbycol(rcts[i].c4)-1);
    f.WriteChar(chr(rcts[i].seed));}
  f.WriteInt(nic);
  for i:=1 to nic do begin
    f.WriteNullTerminatedString(ss[ic[i-1]-1]);
  end;
end;

procedure Lift();
var
  x,y:integer;
  c,d,d1,d2,d3:double;
  c1,c2,c3,c4,cc:byte;
begin
{  if (x1>w) then x1:=w;
  if (x2>w) then x2:=w;
  if (y1>h) then y1:=h;
  if (y2>h) then y2:=h;
  if (x1<0) then x1:=0;
  if (x2<0) then x2:=0;
  if (y1<0) then y1:=0;
  if (y2<0) then y2:=0;}
  c1:=getrvalue(hbitmap.Canvas.Pixels[x1,y1]);
  c2:=getrvalue(hbitmap.Canvas.Pixels[x2,y2]);
  if (x1<0) or (x1>=w) then c1:=0;
  if (y1<0) or (y1>=h) then c1:=0;
  if (x2<0) or (x2>=w) then c2:=0;
  if (y2<0) or (y2>=h) then c2:=0;
  for x:=max(min(x1,x2),0)-form1.SpinEdit3.Value div 2 to min(max(x1,x2),w)+1+form1.SpinEdit3.Value div 2 do begin
    for y:=max(min(y1,y2),0)-form1.SpinEdit3.Value div 2 to min(max(y1,y2),h)+1+form1.SpinEdit3.Value div 2 do begin
      if (x=x1) and (y=y1) then begin
        c:=1;
      end
      else
      begin
        if (x=x2) and (y=y2) then begin
          c:=1;
        end
        else
        begin
          c:=((x-x1)*(x2-x1)+(y-y1)*(y2-y1))/(sqrt(sqr(x2-x1)+sqr(y2-y1))*sqrt(sqr(x-x1)+sqr(y-y1)));
        end;
      end;
      d2:=c*sqrt(sqr(x-x1)+sqr(y-y1));
      if (c<0) then
        d2:=0;
      d3:=d2/sqrt(sqr(x2-x1)+sqr(y2-y1));
      if d3>1 then
        d3:=1;
      c3:=round(Blend(c2,c1,d3));
      if (c<0) then begin
        c:=0;
      end;
      c:=sin(arccos(c));
      d:=c*sqrt(sqr(x-x1)+sqr(y-y1));
      if (d3=1) then
        d:=sqrt(sqr(x-x2)+sqr(y-y2));
      d1:=abs(d*2/form1.spinedit3.value);
      if d1<1 then begin
        d1:=sqr(d1);
        c4:=getrvalue(hbitmap.Canvas.Pixels[x,y]);
        if form1.CheckBox1.Checked then begin
          cc:=round(Blend(c4,c3,d1));
          hbitmap.Canvas.Pixels[x,y]:=rgb(cc,cc,cc);
        end
        else
        begin
          hbitmap.Canvas.Pixels[x,y]:=rgb(c3,c3,c3);
        end;
      end;
    end;
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  i:integer;
  _r:TRect;
  f:cfile;
  c:char;
  s:string;
  d,d1,_w,_h,j,n,cl:integer;
  ttt:single;
begin
  randseed:=0;
  NoiseInit();
    showmessage('Welcome to the PIE map editor'+#13+#10+'v 1.1! It''s demo project,'+#13+#10+'but it''s not for a long time.');
  hbitmap:=tbitmap.Create;
  hbitmap.Width:=512;
  hbitmap.Height:=512;
  cbitmap:=tbitmap.Create;
  cbitmap.Width:=512;
  cbitmap.Height:=512;
  w:=512;
  h:=512;
    _r.Left:=0;
    _r.Top:=0;
    _r.Right:=w;
    _r.Bottom:=h;
  hbitmap.Canvas.Brush.Color:=0;
  hbitmap.Canvas.FillRect(_r);
  f:=cfile.Create;
  f.Open('Data\main.tst',true);
  f.ReadChar(c);
  f.ReadChar(c);
  f.ReadChar(c);
  f.ReadNullTerminatedString(s);
  label7.Caption:=s;
  f.ReadInt(d);
  f.ReadInt(ts);
  for i:=1 to d do begin
    f.ReadNullTerminatedString(s);
    combobox1.Items.Add(s);
    f.ReadInt(_w);
    hw[i-1,0]:=_w;
    f.ReadInt(_h);
    hw[i-1,1]:=_h;
    f.ReadNullTerminatedString(s);
    ss[i-1]:=s;
    f.ReadInt(d1);
    Colors[i]:=d1;
    for j:=1 to _w*_h do
      f.ReadChar(bb[i-1,j-1]);
  end;
  cbitmap.Canvas.Brush.Color:=Colors[1];
  cbitmap.Canvas.FillRect(_r);
  combobox1.ItemIndex:=0;
  f.Close;
  f.Open('data\main.pd',true);
  f.ReadString(3,s);
  if s<>'PID' then begin
    showmessage('File with scenery data is damaged or has unknown format!'+#13+#10+'Now exiting.');
    application.Terminate;
  end;
  f.ReadInt(n);
  for i:=0 to n-1 do begin
    f.ReadNullTerminatedString(nms[i]);
    combobox4.Items.Add(nms[i]);
    f.ReadInt(d);
    scolors[i]:=d;
    f.ReadInt(cn[i]);
    for j:=0 to cn[i]-1 do begin
      f.ReadNullTerminatedString(mp[i,j]);
      f.ReadFloat(scmi[i,j]);
      f.ReadFloat(scma[i,j]);
      f.ReadFloat(ttt);
      f.ReadFloat(ttt);
      f.ReadFloat(ttt);
      f.ReadFloat(ttt);
      f.ReadFloat(ttt);
      f.ReadFloat(ttt);
      f.ReadFloat(ttt);
    end;
  end;
  combobox4.ItemIndex:=0;
  f.Close;
  f.Destroy;
  xx[1]:=0;
  xx[2]:=w;
  yy[1]:=0;
  yy[2]:=h;
  repaint;
end;

procedure TForm1.DXDraw1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  bract:=true;
  if PageControl2.ActivePageIndex=0 then begin
    hbitmap.Canvas.Pen.Color:=shape1.Brush.Color;
    hbitmap.Canvas.Pen.Width:=spinedit1.Value;
    hbitmap.Canvas.MoveTo(round(x*zoom),round(y*zoom));
    hbitmap.Canvas.LineTo(round(x*zoom),round(y*zoom));
    hbitmap.Canvas.MoveTo(round(x*zoom),round(y*zoom));
    repaint;
  end;
  if PageControl2.ActivePageIndex=1 then begin
    x1:=round(x*zoom);
    y1:=round(y*zoom);

  end;
end;

procedure TForm1.DXDraw1MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if not bract then exit;
  if PageControl2.ActivePageIndex=0 then begin
    hbitmap.Canvas.LineTo(round(x*zoom),round(y*zoom));
    hbitmap.Canvas.MoveTo(round(x*zoom),round(y*zoom));
  end;
  if PageControl2.ActivePageIndex=1 then begin
    x2:=round(x*zoom+dx);
    y2:=round(y*zoom+dy);
    bract:=false;
    Lift();
  end;
  bract:=false;
  repaint;
end;

procedure TForm1.DXDraw1MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
var
  c:TPoint;
  s:string;
  d:integer;
begin
  //if brush
  d:=0;
  if bract then d:=1;
  s:=format('X:%4d;Y%4d;Color:%4d;Current Color:%4d;%d',[x,y,getrvalue(dxdraw1.Surface.Canvas.Pixels[x,y]),spinedit2.Value,d]);
  statusbar1.Panels.Items[0].Text:=s;
  if not bract then exit;
  if PageControl2.ActivePageIndex=0 then begin
    hbitmap.Canvas.LineTo(round(x*zoom),round(y*zoom));
    hbitmap.Canvas.MoveTo(round(x*zoom),round(y*zoom));
    repaint;
  end;
  if PageControl2.ActivePageIndex=1 then begin
    x2:=round(x*zoom);
    y2:=round(y*zoom);
    repaint;
  end;
end;

procedure TForm1.FormPaint(Sender: TObject);
var
  _r:trect;
  _r1:trect;
  x,y,i,xx1,yy1,ind1,ind2,xx2,yy2:integer;
  _xx,_yy,_xx1,_yy1:single;
  r,g,b,c:byte;
  clr:TColor;
begin
//  wd:=min(512,wd);
//  hd:=min(512,wd);
  wd:=round(w/zoom);
  hd:=round(h/zoom);
  if wd=0 then wd:=w;if hd=0 then hd:=h;
  if dxdraw1.width<>wd then
    dxdraw1.Width:=wd;
  dxdraw1.Height:=hd;
  dxdraw2.Width:=wd;
  dxdraw2.Height:=hd;
  dxdraw3.Width:=wd;
  dxdraw3.Height:=hd;
  dxdraw1.Left:=dx;
  dxdraw1.Top:=dy;
  dxdraw2.Left:=dx;
  dxdraw2.Top:=dy;
  dxdraw3.Left:=dx;
  dxdraw3.Top:=dy;
  if pagecontrol1.ActivePageIndex=0 then begin
    _r.Left:=0;
    _r.Top:=0;
    _r.Right:=wd;
    _r.Bottom:=hd;
    _r1.Left:=0;
    _r1.Top:=0;
    _r1.Right:=w;
    _r1.Bottom:=h;
    dxdraw1.Surface.Canvas.Pen.Color:=clRed;
    dxdraw1.Surface.Canvas.Pen.Width:=round(spinedit3.Value/zoom);
    dxdraw1.Surface.Canvas.CopyRect(_r,hbitmap.Canvas,_r1);
    if (PageControl2.ActivePageIndex=1) and (bract) then begin
      dxdraw1.Surface.Canvas.MoveTo(round((x1-dx)/zoom),round((y1-dy)/zoom));
      dxdraw1.Surface.Canvas.LineTo(round((x2-dx)/zoom),round((y2-dy)/zoom));
    end;
    DXDraw1.Surface.Canvas.Release;
    DXDraw1.Flip;
    shape2.Width:=w div 4;
    shape2.Height:=h div 4;
    shape3.Width:=round(w*zoom) div 4;
    shape3.Height:=round(h*zoom) div 4;
    shape3.Left:=shape2.Left+dx div 4;
    shape3.Top:=shape2.top+dy div 4;
  end;
  if pagecontrol1.ActivePageIndex=1 then  begin
    _r.Left:=0;
    _r.Top:=0;
    _r.Right:=wd;
    _r.Bottom:=hd;
    _r1.Left:=0;
    _r1.Top:=0;
    _r1.Right:=w;
    _r1.Bottom:=h;
    if (bract1) or not (checkbox2.Checked) then begin
      dxdraw2.Surface.Canvas.CopyRect(_r,cbitmap.Canvas,_r1);
    end
    else
    begin
    for x:=max(xx[1],0) to min(xx[2],w) do begin
      for y:=max(yy[1],0) to min(yy[2],h) do begin
        c:=getrvalue(hbitmap.Canvas.Pixels[x,y]);
        r:=round(blend(c,getrvalue(cbitmap.Canvas.Pixels[x,y]),0.7));
        g:=round(blend(c,getgvalue(cbitmap.Canvas.Pixels[x,y]),0.7));
        b:=round(blend(c,getbvalue(cbitmap.Canvas.Pixels[x,y]),0.7));
        dxdraw2.Surface.Canvas.Pixels[x,y]:=rgb(r,g,b);
      end;
    end;
    end;
    DXDraw2.Surface.Canvas.Release;
    DXDraw2.Flip;
    shape4.Width:=w div 4;
    shape4.Height:=h div 4;
    shape5.Width:=round(w*zoom) div 4;
    shape5.Height:=round(h*zoom) div 4;
    shape5.Left:=shape4.Left+dx div 4;
    shape5.Top:=shape4.top+dy div 4;
  end;
  if pagecontrol1.ActivePageIndex=2 then  begin
    _r.Left:=0;
    _r.Top:=0;
    _r.Right:=wd;
    _r.Bottom:=hd;
    _r1.Left:=0;
    _r1.Top:=0;
    _r1.Right:=w;
    _r1.Bottom:=h;
      dxdraw3.Surface.Canvas.CopyRect(_r,cbitmap.Canvas,_r1);
    shape8.Width:=w div 4;
    shape8.Height:=h div 4;
    shape7.Width:=round(w*zoom) div 4;
    shape7.Height:=round(h*zoom) div 4;
    shape7.Left:=shape8.Left+dx div 4;
    shape7.Top:=shape8.top+dy div 4;
    if DoodCount<>0 then
      for i:=0 to DoodCount-1 do begin
        ind1:=DoodInd[Doods[i],0];
        ind2:=DoodInd[Doods[i],1];
        DxDraw3.Surface.Canvas.Pen.Width:=1;
        DxDraw3.Surface.Canvas.Pen.Color:=RGB(255-Getrvalue(SColors[ind1]),255-Getgvalue(SColors[ind1]),255-Getbvalue(SColors[ind1]));
        DxDraw3.Surface.Canvas.Brush.Color:=SColors[ind1];
        _xx:=coord[i,0];
        _yy:=coord[i,1];
        clr:=DxDraw3.Surface.Canvas.Pen.Color;
        if ng[i] then clr:=clred;
        _xx1:=_xx+cos(rot[i])*sc[i]*defrad;
        _yy1:=_yy-sin(rot[i])*sc[i]*defrad;
        xx1:=round((_xx-sc[i]*defrad)/zoom);
        yy1:=round((_yy-sc[i]*defrad)/zoom);
        xx2:=round((_xx+sc[i]*defrad)/zoom);
        yy2:=round((_yy+sc[i]*defrad)/zoom);
        DxDraw3.Surface.Canvas.Ellipse(xx1,yy1,xx2,yy2);
        _xx:=_xx/zoom;
        _yy:=_yy/zoom;
        _xx1:=_xx1/zoom;
        _yy1:=_yy1/zoom;
        DxDraw3.Surface.Canvas.Pen.Color:=clr;
        DxDraw3.Surface.Canvas.MoveTo(round(_xx),round(_yy));
        DxDraw3.Surface.Canvas.LineTo(round(_xx1),round(_yy1));
      end;
      DxDraw3.Surface.Canvas.Brush.Color:=0;
      DxDraw3.Surface.Canvas.Pen.Color:=clWhite;
      DxDraw3.Surface.Canvas.Pen.Width:=1;
      DxDraw3.Surface.Canvas.Pen.Style:=psDot;
      DxDraw3.Surface.Canvas.Font.Color:=clWhite;
      if aic>0 then begin
        DxDraw3.Surface.Canvas.MoveTo(round(aipoints[aic-1,0]/zoom),round(aipoints[aic-1,1]/zoom));

        for x:=0 to aic-1 do begin
          //
          DxDraw3.Surface.Canvas.LineTo(round(aipoints[x,0]/zoom),round(aipoints[x,1]/zoom));
          DxDraw3.Surface.Canvas.TextOut(round(aipoints[x,0]/zoom),round(aipoints[x,1]/zoom),inttostr(x));
          DxDraw3.Surface.Canvas.MoveTo(round(aipoints[x,0]/zoom),round(aipoints[x,1]/zoom));
        end;
      end;
      DxDraw3.Surface.Canvas.Pen.Style:=psSolid;
      DxDraw3.Surface.Canvas.Pen.Color:=clred;
      DxDraw3.Surface.Canvas.Brush.Color:=clred;
      if bract2 then
      DxDraw3.Surface.Canvas.Ellipse(round(x1/zoom-spinedit5.Value),round(y1/zoom-spinedit5.Value),round(x1/zoom+spinedit5.Value),round(y1/zoom+spinedit5.Value));
    DXDraw3.Surface.Canvas.Release;
    DXDraw3.Flip;
  end;
end;


procedure TForm1.SpinEdit2Change(Sender: TObject);
begin
  shape1.Brush.Color:=rgb(spinedit2.Value,spinedit2.Value,spinedit2.Value);
end;

procedure TForm1.Button3Click(Sender: TObject);
var
  x,y:integer;
  c:byte;
begin
  for x:=0 to w do begin
    for y:=0 to h do
    begin
      c:=getrvalue(hbitmap.Canvas.Pixels[x,y]);
      if c<> 0 then begin
        c:=round(sqr(c/255)*255);
        hbitmap.Canvas.Pixels[x,y]:=rgb(c,c,c);
      end;
      gauge1.Progress:=round((x*h+y)*100/(w*h));
    end;
    if x mod 8 = 0 then repaint;
  end;
  repaint;
end;

procedure TForm1.DXDraw2MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
var
  c:TPoint;
  s:string;
begin
  //if brush
  s:=format('X:%4d;Y%4d',[x,y]);
  statusbar1.Panels.Items[0].Text:=s;
  if not bract1 then exit;
    cbitmap.Canvas.LineTo(round(x*zoom),round(y*zoom));
    cbitmap.Canvas.MoveTo(round(x*zoom),round(y*zoom));
{  xx[1]:=min(xx[1],round(x*zoom+dx)-spinedit4.Value div 2-1);
  yy[1]:=min(yy[1],round(y*zoom+dy)-spinedit4.Value div 2-1);
  xx[2]:=max(xx[2],round(x*zoom+dx)+spinedit4.Value div 2+1);
  yy[2]:=max(yy[2],round(y*zoom+dy)+spinedit4.Value div 2+1);}
  repaint;

end;

procedure TForm1.Button2Click(Sender: TObject);
begin
if opendialog1.Execute then begin
  hbitmap.LoadFromFile(opendialog1.FileName);
  hbitmap.Width:=w;
  hbitmap.Height:=h;
  repaint;
end;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
zoom:=zoom/1.2;
wd:=round(w/zoom);
hd:=round(h/zoom);
repaint;
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
zoom:=zoom*1.2;
wd:=round(w/zoom);
hd:=round(h/zoom);
repaint;
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
  dy:=dy-10;
  if dy<-h+h*zoom then dy:=round(-h+h*zoom);
repaint;
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
  dx:=dx-10;
  if dx<-w+w*zoom then dx:=round(-w+w*zoom);
repaint;
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
  dy:=dy+10;
  if dy>0 then dy:=0;
repaint;
end;

procedure TForm1.Button9Click(Sender: TObject);
begin
  dx:=dx+10;
  if dx>0 then dx:=0;
repaint;
end;

procedure TForm1.Button10Click(Sender: TObject);
begin
  zoom:=1;
  dx:=0;
  dy:=0;
  repaint;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
repaint;
end;

procedure TForm1.Button11Click(Sender: TObject);
begin
if savedialog1.Execute then
  hbitmap.SaveToFile(savedialog1.FileName);
end;

procedure TForm1.DXDraw2MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  bract1:=true;
  cbitmap.Canvas.Pen.Color:=Colors[combobox1.ItemIndex+1];
  cbitmap.Canvas.Pen.Width:=spinedit4.Value;
{  xx[1]:=round(x*zoom+dx)-spinedit4.Value div 2-1;
  xx[2]:=round(x*zoom+dx)+spinedit4.Value div 2+1;
  yy[1]:=round(y*zoom+dy)-spinedit4.Value div 2-1;
  yy[2]:=round(y*zoom+dy)+spinedit4.Value div 2+1;}
    cbitmap.Canvas.MoveTo(round(x*zoom),round(y*zoom));
    cbitmap.Canvas.LineTo(round(x*zoom),round(y*zoom));
    cbitmap.Canvas.MoveTo(round(x*zoom),round(y*zoom));
    repaint;

end;

procedure TForm1.DXDraw2MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if not bract1 then exit;
    cbitmap.Canvas.LineTo(round(x*zoom),round(y*zoom));
    cbitmap.Canvas.MoveTo(round(x*zoom),round(y*zoom));
{  xx[1]:=min(xx[1],round(x*zoom+dx)-spinedit4.Value div 2-1);
  yy[1]:=min(yy[1],round(y*zoom+dy)-spinedit4.Value div 2-1);
  xx[2]:=max(xx[2],round(x*zoom+dx)+spinedit4.Value div 2+1);
  yy[2]:=max(yy[2],round(y*zoom+dy)+spinedit4.Value div 2+1);}
  bract1:=false;
  repaint;
end;

procedure TForm1.New1Click(Sender: TObject);
begin
  form1.Enabled:=false;
  form2.Show;
end;

procedure TForm1.Save1Click(Sender: TObject);
var
f:CFile;
s:string;
x,y,iii:TColor;
begin
  if savedialog2.Execute then begin
    s:=savedialog2.FileName;
    s:=changefileext(s,'.~pm');
    if fileexists(s) then
      if application.MessageBox(pansichar('File with name '+s+' exists. Overwrite?'),'Warning',mb_Yesno)=7 then
        exit;
    f:=CFile.Create;
    f.Open(s,false);
    f.WriteString('PMP');
    f.WriteNullTerminatedString(Edit2.Text);
    f.WriteInt(w);
    f.WriteInt(h);
    //writing height data
    for x:=0 to w-1 do
      for y:=0 to h-1 do
        f.WriteChar(chr(getrvalue(hbitmap.Canvas.Pixels[x,y])));
    for x:=0 to w-1 do
      for y:=0 to h-1 do begin
        iii:=cbitmap.Canvas.Pixels[x,y];
        f.WriteChar(chr(getrvalue(iii)));
        f.WriteChar(chr(getgvalue(iii)));
        f.WriteChar(chr(getbvalue(iii)));
      end;
    f.WriteNullTerminatedString(edit3.Text);
    f.WriteInt(shape6.Brush.Color);
    f.WriteInt(DoodIndC);
    if DoodIndC<>0 then
      for x:=0 to DoodIndC-1 do begin
        f.WriteWord(DoodInd[x,0]);
        f.WriteWord(DoodInd[x,1]);
      end;
    f.WriteInt(DoodCount);
    if DoodCount<>0 then
      for x:=0 to Doodcount-1 do begin
        f.writeword(doods[x]);
        f.WriteFloat(coord[x,0]);
        f.WriteFloat(coord[x,1]);
        f.WriteFloat(sc[x]);
        f.WriteFloat(Rot[x]);
        f.WriteBool(ng[x]);
      end;
      f.WriteFloat(strtofloat(edit6.Text));
      f.WriteFloat(strtofloat(edit7.Text));
      f.WriteInt(Integer(shape6.Brush.Color));
      f.WriteFloat(strtofloat(edit3.Text));
      f.WriteFloat(strtofloat(edit4.Text));
    f.Close;
  end;
end;

procedure TForm1.Open1Click(Sender: TObject);
var
f:CFile;
s:string;
x,y,ii:integer;
_c:char;
_r:trect;
r,g,b:char;
ww,hh,i:integer;
fff:single;
begin
  if opendialog2.Execute then begin
    s:=opendialog2.FileName;
    f:=cfile.Create;
    f.Open(s,true);
    f.ReadString(3,s);
    if s<>'PMP' then begin
      showmessage('File has unknown format or damaged!');
      f.Close;
      exit;
    end;
    f.ReadNullTerminatedString(s);
    Edit2.Text:=s;
    f.ReadInt(w);
    f.ReadInt(h);
  _r.Left:=0;
  _r.Top:=0;
  _r.Right:=w;
  _r.Bottom:=h;
  Zoom:=1;
  dx:=0;
  dy:=0;
  form1.DXDraw1.Width:=w;
  form1.DXDraw1.Height:=h;
  form1.DXDraw2.Width:=w;
  form1.DXDraw2.Height:=h;
  form1.DXDraw3.Width:=w;
  form1.DXDraw3.Height:=h;
  hbitmap.Width:=w;
  hbitmap.Height:=h;
  cbitmap.Width:=w;
  cbitmap.Height:=h;
  ww:=0;
  i:=16;
  while i<>w do begin
    i:=i*2;
    ww:=ww+1;
  end;
  hh:=0;
  i:=16;
  while i<>h do begin
    i:=i*2;
    hh:=hh+1;
  end;
  combobox2.ItemIndex:=ww;
  combobox3.ItemIndex:=hh;
  hbitmap.Canvas.Brush.Color:=0;
  hbitmap.Canvas.FillRect(_r);
  cbitmap.Canvas.Brush.Color:=Colors[1];
  cbitmap.Canvas.FillRect(_r);
    for x:=0 to w-1 do
      for y:=0 to h-1 do begin
        f.ReadChar(_c);
        hbitmap.Canvas.Pixels[x,y]:=rgb(ord(_c),ord(_c),ord(_c));
      end;
    for x:=0 to w-1 do
      for y:=0 to h-1 do begin
        f.ReadChar(r);
        f.ReadChar(g);
        f.ReadChar(b);
        cbitmap.Canvas.Pixels[x,y]:=rgb(ord(r),ord(g),ord(b));
      end;
    f.ReadNullTerminatedString(s);
    edit3.Text:=s;
    f.ReadInt(ii);
    shape6.Brush.Color:=ii;
    f.ReadInt(DoodIndC);
    if DoodIndC<>0 then
      for x:=0 to DoodIndC-1 do begin
        f.ReadWord(DoodInd[x,0]);
        f.ReadWord(DoodInd[x,1]);
      end;
    f.ReadInt(DoodCount);
    if DoodCount<>0 then
      for x:=0 to Doodcount-1 do begin
        f.Readword(doods[x]);
        f.ReadFloat(coord[x,0]);
        f.ReadFloat(coord[x,1]);
        f.ReadFloat(sc[x]);
        f.ReadFloat(Rot[x]);
        f.ReadBool(ng[x]);
      end;
      f.ReadFloat(fff);
      edit6.Text:=floattostr(fff);
      f.ReadFloat(fff);
      edit7.Text:=floattostr(fff);
      f.ReadInt(i);
      shape6.Brush.Color:=i;
      f.ReadFloat(fff);
      edit3.Text:=floattostr(fff);
      f.ReadFloat(fff);
      edit4.Text:=floattostr(fff);
    f.Close;
  pagecontrol1.Enabled:=true;
  repaint;
  end;
end;

procedure TForm1.Edit2Change(Sender: TObject);
begin
//  form2.Edit1.text:=edit2.text;
//  form2.ComboBox1.ItemIndex:=combobox2.ItemIndex;
//  form2.ComboBox2.ItemIndex:=combobox3.ItemIndex;

end;

procedure TForm1.ComboBox3Change(Sender: TObject);
var
  i:integer;
  d,d1,_w,_h,j:integer;
begin
//  form2.Edit1.text:=edit2.text;
//  form2.ComboBox1.ItemIndex:=combobox2.ItemIndex;
//  form2.ComboBox2.ItemIndex:=combobox3.ItemIndex;
  _w:=8;
  _h:=8;
  for i:=0 to combobox2.ItemIndex do begin
    _w:=_w*2;
  end;
  for i:=0 to combobox3.ItemIndex do begin
    _h:=_h*2;
  end;
  w:=_w;
  h:=_h;
  form1.DXDraw1.Width:=w;
  form1.DXDraw1.Height:=h;
  form1.DXDraw2.Width:=w;
  form1.DXDraw2.Height:=h;
  form1.DXDraw3.Width:=w;
  form1.DXDraw3.Height:=h;
  hbitmap.Width:=w;
  hbitmap.Height:=h;
  cbitmap.Width:=w;
  cbitmap.Height:=h;

end;

procedure TForm1.ComboBox2Change(Sender: TObject);
var
  i:integer;
  d,d1,_w,_h,j:integer;
begin
//  form2.Edit1.text:=edit2.text;
//  form2.ComboBox1.ItemIndex:=combobox2.ItemIndex;
//  form2.ComboBox2.ItemIndex:=combobox3.ItemIndex;
  _w:=8;
  _h:=8;
  for i:=0 to combobox2.ItemIndex do begin
    _w:=_w*2;
  end;
  for i:=0 to combobox3.ItemIndex do begin
    _h:=_h*2;
  end;
  w:=_w;
  h:=_h;
  form1.DXDraw1.Width:=w;
  form1.DXDraw1.Height:=h;
  form1.DXDraw2.Width:=w;
  form1.DXDraw2.Height:=h;
  form1.DXDraw3.Width:=w;
  form1.DXDraw3.Height:=h;
  hbitmap.Width:=w;
  hbitmap.Height:=h;
  cbitmap.Width:=w;
  cbitmap.Height:=h;
end;

procedure TForm1.Export1Click(Sender: TObject);
var
f:CFile;
s:string;
x,y,x1,x2:integer;
begin
  if savedialog3.Execute then begin
    s:=savedialog3.FileName;
    s:=changefileext(s,'.pm');
    if fileexists(s) then
      if application.MessageBox(pansichar('File with name '+s+' exists. Overwrite?'),'Warning',mb_Yesno)=7 then
        exit;
    f:=CFile.Create;
    f.Open(s,false);
    f.WriteString('PMP');
    f.WriteNullTerminatedString(Edit2.Text);
    f.WriteInt(w);
    f.WriteInt(h);
      f.WriteFloat(strtofloat(edit6.Text));//hSCale
      f.WriteFloat(strtofloat(edit7.Text));//VScale
      f.WriteInt(Integer(shape6.Brush.Color));//Fog color
      f.WriteFloat(strtofloat(edit3.Text));//fog near
      f.WriteFloat(strtofloat(edit4.Text));//fog far
    //writing height data
    for x:=0 to w-1 do
      for y:=0 to h-1 do
        f.WriteChar(chr(getrvalue(hbitmap.Canvas.Pixels[x,y])));
    rcnt:=0;
    for y:=0 to h-1 do
      for x:=0 to w-1 do begin
        x1:=x+1;
        y1:=y+1;
        if x1>=w then x1:=w-1;
        if y1>=h then y1:=h-1;
        f.WriteWord(Add(cbitmap.Canvas.Pixels[x,y],cbitmap.Canvas.Pixels[x1,y],
            cbitmap.Canvas.Pixels[x,y1],cbitmap.Canvas.Pixels[x1,y1]));
      end;
    _Write(f);
    //Sky
    f.WriteInt(DoodIndC);
    if DoodIndC<>0 then
      for x:=0 to DoodIndC-1 do begin
        f.WriteNullTerminatedString(mp[DoodInd[x,0],DoodInd[x,1]]);
      end;
    f.WriteInt(DoodCount);
    if DoodCount<>0 then
      for x:=0 to Doodcount-1 do begin
        f.writeword(doods[x]);
        f.WriteFloat(coord[x,0]);
        f.WriteFloat(coord[x,1]);
        f.WriteFloat(sc[x]);
        f.WriteFloat(-Rot[x]);
        f.WriteBool(ng[x]);
      end;
    f.WriteNullTerminatedString(edit3.Text);
    f.WriteInt(shape6.Brush.Color);
    f.Close;
  end;
end;

procedure TForm1.Shape6MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if colordialog1.execute then shape6.Brush.Color:=colordialog1.Color;
end;

procedure TForm1.Redraw1Click(Sender: TObject);
begin
  repaint;
end;

procedure TForm1.DXDraw3MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  //Creating doodoad))
  if not checkbox5.checked then begin
  if not bract2 then   CreateDoodoad(x*zoom,y*zoom);

  if bract2 then begin
    bract2:=false;
    RefreshDood();
    x1:=round(x*zoom);
    y1:=round(y*zoom);
    RemoveDoods(x*zoom,y*zoom);
    repaint;
  end;
  end
  else
  begin
    AddAIPoint(x*zoom,y*zoom);
    repaint;
  end;
end;

procedure TForm1.DXDraw3MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
  if bract2 then begin
    x1:=round(x*zoom);
    y1:=round(y*zoom);
    RemoveDoods(x*zoom,y*zoom);
    repaint;
  end;
end;

procedure TForm1.DXDraw3MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin

  if Button=mbRight then begin
    bract2:=true;
    x1:=round(x*zoom);
    y1:=round(y*zoom);
    RemoveDoods(x*zoom,y*zoom);
    repaint;
  end;
end;

procedure TForm1.Button26Click(Sender: TObject);
begin
  inc(randseed);
  NoiseInit;
  SetParams(spinedit6.value,spinedit7.value);
  SetWH(w,h);
  SetMM(rgb(spinedit9.value,spinedit9.value,spinedit9.value),
  rgb(spinedit8.value,spinedit8.value,spinedit8.value));
  Generate();
  Render(hbitmap.canvas);
  repaint;
end;

procedure TForm1.Button27Click(Sender: TObject);
begin
  aic:=0;
  repaint;
end;

end.
