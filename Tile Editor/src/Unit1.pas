unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, DXDraws, DXClass, Math, ComCtrls, Spin;

type
  TTile   = class
    name    : string;
    Color   : TColor;
    PMap    : TBitmap;
    tpname  : string;
    tname   : string;
    data    : array[0..32,0..32] of byte;
    Width   : DWORD;
    Height  : DWORD;
    private
      //
    public
      //something here
      constructor Create;
      procedure Save(F:THandle);
      procedure Load(F:THandle);
      procedure _Export(F:THandle);
      procedure _Import(F:THandle);
  end;



  TForm1 = class(TForm)
    DXDraw1: TDXDraw;
    Panel1: TPanel;
    ListBox1: TListBox;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    Button9: TButton;
    Timer1: TTimer;
    StatusBar1: TStatusBar;
    SpinEdit1: TSpinEdit;
    SpinEdit2: TSpinEdit;
    Button10: TButton;
    SaveDialog1: TSaveDialog;
    OpenDialog1: TOpenDialog;
    procedure FormCreate(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure ListBox1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure DXDraw1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure DXDraw1MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Button2Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    _name:string;
    Tiles:array[0..100] of TTile;
    tsize,tcount:DWORD;
    function GetSelection():integer;
    procedure TProp();
    procedure SetC();
    procedure _new;
    procedure EditTSet(Ind:integer);
    procedure Select(ind:integer);
    procedure SetBnds();
    procedure swap(x,y:integer);
  end;

var
  Form1: TForm1;
  dw   : Cardinal;
  ctile: integer=0;

implementation

uses Unit2, Unit3, Unit4;

{$R *.dfm}

{ TForm1 }

function TForm1.GetSelection: integer;
var
  i:integer;
begin
  Result:=0;
  if listbox1.Items.Count=0 then
  begin
    Result:=-1;
    exit;
  end;
  for i:=0 to listbox1.Items.Count-1 do begin
    if listbox1.Selected[i] then
    begin
      Result:=i;
      exit;
    end;
  end;
  Result:=-1;
  exit;
end;

procedure TForm1.TProp;
begin
  form2.show;
  form1.Enabled:=false;
  form2.Edit1.Text:=form1._name;
  form2.SpinEdit1.Value:=form1.tsize;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  i:integer;
begin
  _name:='Unnamed';
  tsize:=64;
  SetC();
  for i:=0 to 100 do
    Tiles[i]:=TTile.Create;
end;

procedure TForm1.SetC;
begin
  form1.Caption:='TileSet Editor - ["'+_name+'" tile size='+inttostr(tsize)+']';
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
  _new;
  TProp;
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
  TProp;
end;

procedure TForm1._new;
begin
  //do something
  _name:='Unnamed';
  tsize:=64;
  tcount:=0;
  listbox1.Items.Clear;
  SetC();
end;

procedure TForm1.EditTSet(Ind: integer);
begin
  form1.Enabled:=false;
  form3.ind:=Ind;
  form3.Show;
end;

{ Tile }

procedure TTile._Export(F: THandle);
var
  b:byte;
  i,j:integer;
begin
  for i:=1 to length(name) do
    WriteFile(f,name[i],1,dw,nil);
  b:=0;
  WriteFile(f,b,1,dw,nil);
  WriteFile(f,Width,4,dw,nil);
  WriteFile(f,Height,4,dw,nil);
  for i:=1 to length(tname) do
    WriteFile(f,tname[i],1,dw,nil);
  b:=0;
  WriteFile(f,b,1,dw,nil);
  WriteFile(f,Color,4,dw,nil);
  for i:=0 to Height-1 do
    for j:=0 to Width-1 do
      WriteFile(f,data[j,i],1,dw,nil);
end;

procedure TTile._Import(F: THandle);
var
  b:char;
  i,j:integer;
begin
  name:='';
  tname:='';
  tpname:='';
  b:=#1;
  while b<>#0 do begin
    ReadFile(f,b,1,dw,nil);
    if b>#0 then
      name:=name+b;
  end;
  ReadFile(f,Width,4,dw,nil);
  ReadFile(f,Height,4,dw,nil);
  b:=#1;
  while b<>#0 do begin
    ReadFile(f,b,1,dw,nil);
    if b>#0 then
      tname:=tname+b;
  end;
  ReadFile(f,Color,4,dw,nil);
  for i:=0 to Height-1 do
    for j:=0 to Width-1 do
      ReadFile(f,data[j,i],1,dw,nil);
end;

constructor TTile.Create;
begin
  PMap:=TBitmap.Create;
end;

procedure TTile.Load(F: THandle);
var
  b:char;
  i,j:integer;
begin
  name:='';
  tname:='';
  tpname:='';
  b:=#1;
  while b<>#0 do begin
    ReadFile(f,b,1,dw,nil);
    if b>#0 then
      name:=name+b;
  end;
  ReadFile(f,Width,4,dw,nil);
  ReadFile(f,Height,4,dw,nil);
  b:=#1;
  while b<>#0 do begin
    ReadFile(f,b,1,dw,nil);
    if b>#0 then
      tpname:=tpname+b;
  end;
  if (fileExists(tpname)) then
    PMap.LoadFromFile(tpname);
  b:=#1;
  while b<>#0 do begin
    ReadFile(f,b,1,dw,nil);
    if b>#0 then
      tname:=tname+b;
  end;
  ReadFile(f,Color,4,dw,nil);
  for i:=0 to Width-1 do
    for j:=0 to Height-1 do
      ReadFile(f,data[i,j],1,dw,nil);
end;

procedure TTile.Save(F: THandle);
var
  b:byte;
  i,j:integer;
begin
  for i:=1 to length(name) do
    WriteFile(f,name[i],1,dw,nil);
  b:=0;
  WriteFile(f,b,1,dw,nil);
  WriteFile(f,Width,4,dw,nil);
  WriteFile(f,Height,4,dw,nil);
  for i:=1 to length(tpname) do
    WriteFile(f,tpname[i],1,dw,nil);
  b:=0;
  WriteFile(f,b,1,dw,nil);
  for i:=1 to length(tname) do
    WriteFile(f,tname[i],1,dw,nil);
  b:=0;
  WriteFile(f,b,1,dw,nil);
  WriteFile(f,Color,4,dw,nil);
  for i:=0 to Width-1 do
    for j:=0 to Height-1 do
      WriteFile(f,data[i,j],1,dw,nil);
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  tiles[tcount].name:='New tile';
  tiles[tcount].tname:='';
  tiles[tcount].tpname:='';
  Tcount:=tcount+1;
  EditTSet(listbox1.Items.Add('New tile'));
end;

procedure TForm1.Button3Click(Sender: TObject);
var
  ind:integer;
begin
  ind:= GetSelection();
  if ind=-1 then exit;
  EditTSet(ind);
end;

procedure TForm1.ListBox1Click(Sender: TObject);
var
  ind:integer;
begin
  ind:=GetSelection;
  if ind<0 then
    exit;
  ctile:=ind;
  DXDraw1.Width:=tiles[ind].Width*tsize;
  DXDraw1.Height:=tiles[ind].Height*tsize;
  panel1.Left:=DXDraw1.Width+7;
  ClientWidth:=panel1.Left+panel1.Width;
  ClientHeight:=panel1.Top+panel1.Height+statusbar1.Height;
  repaint;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var
  r1,r2:TRect;
  i:integer;
begin
  r1.Left:=0;
  r1.Top:=0;
  r1.Right:=DXDraw1.Width-1;
  r1.Bottom:=DXDraw1.Height-1;
  DXDraw1.Surface.Canvas.Brush.Color:=tiles[ctile].Color;
  DXDraw1.Surface.Canvas.FillRect(r1);
  r1.Left:=0;
  r2.Left:=0;
  r1.Top:=0;
  r2.Top:=0;
  r1.Right:=tiles[ctile].PMap.Width;
  r2.Right:=tiles[ctile].PMap.Width;
  r1.Bottom:=tiles[ctile].PMap.Height;
  r2.Bottom:=tiles[ctile].PMap.Height;
  if length(tiles[ctile].tpname)>3 then
    DXDraw1.Surface.Canvas.CopyRect(r1,tiles[ctile].PMap.Canvas,r2);
  DXDraw1.Surface.Canvas.Pen.Color:=RGB(255-getrvalue(tiles[ctile].Color),255-getgvalue(tiles[ctile].Color),255-getbvalue(tiles[ctile].Color));
  DXDraw1.Surface.Canvas.Pen.Width:=1;
  for i:=0 to tiles[ctile].width do
    begin
      if i=0 then begin
        DXDraw1.Surface.Canvas.MoveTo(i*tsize,0);
        DXDraw1.Surface.Canvas.LineTo(i*tsize,DXDraw1.Height);
      end
      else
      begin
        DXDraw1.Surface.Canvas.MoveTo(i*tsize,0);
        DXDraw1.Surface.Canvas.LineTo(i*tsize,DXDraw1.Height);
      end;
    end;
  for i:=0 to tiles[ctile].Height do
    begin
      if i=0 then begin
        DXDraw1.Surface.Canvas.MoveTo(0,i*tsize);
        DXDraw1.Surface.Canvas.LineTo(DXDraw1.Width,i*tsize);
      end
      else begin
        DXDraw1.Surface.Canvas.MoveTo(0,i*tsize);
        DXDraw1.Surface.Canvas.LineTo(DXDraw1.Width,i*tsize);
      end;
    end;
  DXDraw1.Surface.Canvas.Release;
  DXDraw1.Flip;
end;

procedure TForm1.Select(ind: integer);
begin
  DXDraw1.Width:=tiles[ind].Width*tsize;
  DXDraw1.Height:=tiles[ind].Height*tsize;
  panel1.Left:=DXDraw1.Width+7;
  ClientWidth:=panel1.Left+panel1.Width;
  ClientHeight:=panel1.Top+panel1.Height+statusbar1.Height;
  repaint;
end;

procedure TForm1.DXDraw1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var
  i,j:integer;
begin
  if listbox1.Items.Count>0 then begin
    i:=floor(X/tsize);
    j:=floor(Y/tsize);
    form4.x:=@tiles[ctile].data[i,j];
    SetBnds();
  end;
end;

procedure TForm1.SetBnds;
begin
  form1.Enabled:=false;
  form4.Show;
end;

procedure TForm1.DXDraw1MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
  statusbar1.Panels.Items[0].Text:=inttostr(X)+';'+inttostr(Y)+
  ';'+inttostr(floor(X/tsize))+';'+inttostr(floor(Y/tsize));
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  ind:integer;
begin
  ind:=  GetSelection();
  if ind=-1 then
  exit;
  swap(ind,tcount);
  listbox1.Items.Delete(tcount-1);
  dec(tcount);
end;

procedure TForm1.swap(x, y: integer);
var
  Buff:TTile;
  b:string;
begin
  Buff:=tiles[x];
  tiles[x]:=tiles[y];
  tiles[y]:=Buff;
  b:=listbox1.Items.Strings[x];
  listbox1.Items.Strings[x]:=listbox1.Items.Strings[y];
  listbox1.Items.Strings[y]:=b;
end;

procedure TForm1.Button10Click(Sender: TObject);
begin
  if tcount=0 then exit;
  swap(spinedit1.Value mod tcount,spinedit2.Value mod tcount);
end;

procedure TForm1.Button5Click(Sender: TObject);
var
  f:THandle;
  i:integer;
  b:char;
begin
  if savedialog1.Execute then begin
    f:=CreateFile(PANSICHAR(savedialog1.filename),GENERIC_WRITE,FILE_SHARE_WRITE,
      nil,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    b:='P';
    WriteFile(f,b,1,dw,nil);
    b:='T';
    WriteFile(f,b,1,dw,nil);
    b:='S';
    WriteFile(f,b,1,dw,nil);
    for i:=1 to length(_name) do
      WriteFile(f,_name[i],1,dw,nil);
    b:=#0;
    WriteFile(f,b,1,dw,nil);
    WriteFile(f,tcount,4,dw,nil);
    WriteFile(f,tsize,4,dw,nil);
    for i:=0 to tcount-1 do begin
      tiles[i].Save(f);
    end;
    CloseHandle(f);
  end;
end;

procedure TForm1.Button8Click(Sender: TObject);
var
  f:THandle;
  i:integer;
  b:char;
begin
  if opendialog1.Execute then begin
    _new;
    _name:='';
    f:=CreateFile(PANSICHAR(opendialog1.filename),GENERIC_READ,FILE_SHARE_READ,
      nil,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    b:='P';
    ReadFile(f,b,1,dw,nil);
    if b<>'P' then exit;
    ReadFile(f,b,1,dw,nil);
    if b<>'T' then exit;
    ReadFile(f,b,1,dw,nil);
    if b<>'S' then exit;
    while b<>#0 do begin
      ReadFile(f,b,1,dw,nil);
      if b<>#0 then
        _name:=_name+b;
    end;
    ReadFile(f,tcount,4,dw,nil);
    ReadFile(f,tsize,4,dw,nil);
    for i:=0 to tcount-1 do begin
      tiles[i].Load(f);
      listbox1.Items.Add(tiles[i].name)
    end;
    CloseHandle(f);
  end;
end;

procedure TForm1.Button6Click(Sender: TObject);
var
  f:THandle;
  i:integer;
  b:char;
begin
  if savedialog1.Execute then begin
    f:=CreateFile(PANSICHAR(savedialog1.filename),GENERIC_WRITE,FILE_SHARE_WRITE,
      nil,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
    b:='P';
    WriteFile(f,b,1,dw,nil);
    b:='T';
    WriteFile(f,b,1,dw,nil);
    b:='S';
    WriteFile(f,b,1,dw,nil);
    for i:=1 to length(_name) do
      WriteFile(f,_name[i],1,dw,nil);
    b:=#0;
    WriteFile(f,b,1,dw,nil);
    WriteFile(f,tcount,4,dw,nil);
    WriteFile(f,tsize,4,dw,nil);
    for i:=0 to tcount-1 do begin
      tiles[i]._Export(f);
    end;
    CloseHandle(f);
  end;
end;

procedure TForm1.Button9Click(Sender: TObject);
var
  f:THandle;
  i:integer;
  b:char;
begin
  if opendialog1.Execute then begin
    _new;
    _name:='';
    f:=CreateFile(PANSICHAR(opendialog1.filename),GENERIC_READ,FILE_SHARE_READ,
      nil,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    b:='P';
    ReadFile(f,b,1,dw,nil);
    if b<>'P' then exit;
    ReadFile(f,b,1,dw,nil);
    if b<>'T' then exit;
    ReadFile(f,b,1,dw,nil);
    if b<>'S' then exit;
    while b<>#0 do begin
      ReadFile(f,b,1,dw,nil);
      if b<>#0 then
        _name:=_name+b;
    end;
    ReadFile(f,tcount,4,dw,nil);
    ReadFile(f,tsize,4,dw,nil);
    for i:=0 to tcount-1 do begin
      tiles[i]._import(f);
      listbox1.Items.Add(tiles[i].name)
    end;
    CloseHandle(f);
  end;
end;

end.
