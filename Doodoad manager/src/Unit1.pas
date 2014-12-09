unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, ComCtrls, FileBin, Menus;

type
  Vector3=record
    x,y,z:single;
  end;
  Model=record
    path:string;
    pos,sc,rot:Vector3;
  end;
  StaticDoodoad=class
    name:String;
    Color:integer;
    Models:array[0..100] of Model;
    ModelCount:integer;
  public
    constructor Create;
    procedure Write(f:CFile);
    procedure Read(f:cfile);
    procedure AddModel(name,px,py,pz,sx,sy,sz,rx,ry,rz:string);
    procedure GetModel(var name,px,py,pz,sx,sy,sz,rx,ry,rz:string);

  private

  end;
  TForm1 = class(TForm)
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    PageControl1: TPageControl;
    Image1: TImage;
    Image2: TImage;
    ListBox1: TListBox;
    ListBox2: TListBox;
    Button1: TButton;
    Button2: TButton;
    GroupBox1: TGroupBox;
    Button3: TButton;
    Button4: TButton;
    Edit1: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Shape1: TShape;
    ListBox3: TListBox;
    Label3: TLabel;
    Edit2: TEdit;
    Button5: TButton;
    GroupBox2: TGroupBox;
    Button6: TButton;
    Label4: TLabel;
    Label5: TLabel;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Label6: TLabel;
    Edit6: TEdit;
    Edit7: TEdit;
    Edit8: TEdit;
    Label7: TLabel;
    Edit9: TEdit;
    Edit10: TEdit;
    Edit11: TEdit;
    Button7: TButton;
    Button8: TButton;
    Button9: TButton;
    PopupMenu1: TPopupMenu;
    Edit12: TMenuItem;
    Clear1: TMenuItem;
    Remove1: TMenuItem;
    PopupMenu2: TPopupMenu;
    Edit13: TMenuItem;
    Clear2: TMenuItem;
    Remove2: TMenuItem;
    Button10: TButton;
    ColorDialog1: TColorDialog;
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    Open1: TMenuItem;
    Save1: TMenuItem;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    procedure Button8Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Edit12Click(Sender: TObject);
    procedure Edit13Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Shape1MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Open1Click(Sender: TObject);
    procedure Save1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    function getfirst(l:TListBox):integer;
    procedure EditModel(m:Model);
    procedure ApplyModel();
    procedure EditSDoodoad(d:StaticDoodoad);
    procedure ApplySDood();
    procedure Deselect(l:TListbox);
    procedure Select(i:integer;l:TListbox);
  end;

var
  Form1: TForm1;
  EModel:Model;
  smi:integer;
  ESDood:StaticDoodoad;
  sdind,smie:integer;
  isesd,isesm:boolean;
  SDoodoads:array[0..1000] of StaticDoodoad;

implementation

{$R *.dfm}

procedure WriteV3(f:CFile;v:Vector3 );
begin
  f.WriteFloat(v.x);
  f.WriteFloat(v.y);
  f.WriteFloat(v.z);
end;

procedure ReadV3(f:CFile ;var v:Vector3);
begin
  f.ReadFloat(v.x);
  f.ReadFloat(v.y);
  f.ReadFloat(v.z);
end;

{ StaticDoodoad }

procedure StaticDoodoad.AddModel(name, px, py, pz, sx, sy, sz, rx, ry,
  rz: string);
begin
  Models[ModelCount].path:=name;
  Models[ModelCount].pos.x:=strtofloat(px);
  Models[ModelCount].pos.y:=strtofloat(py);
  Models[ModelCount].pos.z:=strtofloat(pz);
  Models[ModelCount].sc.x:=strtofloat(sx);
  Models[ModelCount].sc.y:=strtofloat(sy);
  Models[ModelCount].sc.z:=strtofloat(sz);
  Models[ModelCount].rot.x:=strtofloat(rx);
  Models[ModelCount].rot.y:=strtofloat(ry);
  Models[ModelCount].rot.z:=strtofloat(rz);
end;

constructor StaticDoodoad.Create;
var
  i:integer;
begin
  name:='No name';
  ModelCount:=0;
  for i:=0 to 100 do begin
    Models[i].sc.x:=1;
    Models[i].sc.y:=1;
    Models[i].sc.z:=1;
  end;

end;

procedure StaticDoodoad.GetModel(var name, px, py, pz, sx, sy, sz, rx, ry,
  rz: string);
begin
name := Models[ModelCount].path;
px := FloatToStr(Models[ModelCount].pos.x);
py := FloatToStr(Models[ModelCount].pos.y);
pz := FloatToStr(Models[ModelCount].pos.z);
sx := FloatToStr(Models[ModelCount].sc.x);
sy := FloatToStr(Models[ModelCount].sc.y);
sz := FloatToStr(Models[ModelCount].sc.z);
rx := FloatToStr(Models[ModelCount].rot.x);
ry := FloatToStr(Models[ModelCount].rot.y);
rz := FloatToStr(Models[ModelCount].rot.z);
end;

procedure StaticDoodoad.Read(f: cfile);
var
  i:integer;
begin
  f.ReadNullTerminatedString(name);
  f.ReadInt(Color);
  f.readInt(ModelCount);
  for i:=0 to ModelCount-1 do begin
    f.ReadNullTerminatedString( Models[i].path);
    Readv3(f,Models[i].pos);
    Readv3(f,Models[i].sc);
    Readv3(f,Models[i].rot);
  end;
end;

procedure StaticDoodoad.Write(f: CFile);
var
  i:integer;
begin
  f.WriteNullTerminatedString(name);
  f.WriteInt(Color);
  f.WriteInt(ModelCount);
  for i:=0 to ModelCount-1 do begin
    f.WriteNullTerminatedString( Models[i].path);
    Writev3(f,Models[i].pos);
    Writev3(f,Models[i].sc);
    Writev3(f,Models[i].rot);
  end;
end;

{ TForm1 }

procedure TForm1.ApplyModel;
begin
//Emodel:=m;
isesm:=false;
listbox3.Items.Strings[smie]:=edit2.Text;
ESDood.Models[smie].path := edit2.Text;
ESDood.Models[smie].pos.x := StrToFloat(edit3.Text);
ESDood.Models[smie].pos.y := StrToFloat(edit4.Text);
ESDood.Models[smie].pos.z := StrToFloat(edit5.Text);
ESDood.Models[smie].sc.x := StrToFloat(edit6.Text);
ESDood.Models[smie].sc.y := StrToFloat(edit7.Text);
ESDood.Models[smie].sc.z := StrToFloat(edit8.Text);
ESDood.Models[smie].rot.x := StrToFloat(edit9.Text);
ESDood.Models[smie].rot.y := StrToFloat(edit10.Text);
ESDood.Models[smie].rot.z := StrToFloat(edit11.Text);
end;

procedure TForm1.ApplySDood;
var
i:integer;
begin
isesd:=false;
listbox1.Items.Strings[smi]:=edit1.Text;
SDoodoads[smi].name := edit1.Text;
SDoodoads[smi].Color := shape1.Brush.Color;
end;

procedure TForm1.EditModel(m: Model);
begin
Emodel:=ESDood.Models[smie];
isesm:=true;
listbox3.Enabled:=false;
button8.Enabled:=true;
edit2.Text:=Emodel.path;
edit3.Text := FloatToStr(Emodel.pos.x);
edit4.Text := FloatToStr(Emodel.pos.y);
edit5.Text := FloatToStr(Emodel.pos.z);
edit6.Text := FloatToStr(Emodel.sc.x);
edit7.Text := FloatToStr(Emodel.sc.y);
edit8.Text := FloatToStr(Emodel.sc.z);
edit9.Text := FloatToStr(Emodel.rot.x);
edit10.Text := FloatToStr(Emodel.rot.y);
edit11.Text := FloatToStr(Emodel.rot.z);
end;

procedure TForm1.EditSDoodoad(d: StaticDoodoad);
var
i:integer;
begin
  ESdood:=d;
  button9.Enabled:=true;
  isesd:=true;
listbox1.Enabled:=false;
  edit1.Text:=d.name;
  shape1.Brush.Color:=d.Color;
  listbox3.Clear;
  if d.ModelCount<>0 then
  for i:=0 to d.ModelCount-1 do begin
    listbox3.Items.Add(d.models[i].path)
  end;

end;

function TForm1.getfirst(l: TListBox): integer;
var
  i:integer;
begin
  Result:=-1;
  if l.Items.Count=0 then exit;
  for i:=0 to l.Items.Count-1 do
    if l.Selected[i] then begin
      Result:=i;
      exit;
    end;
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
  button8.Enabled:=false;
  listbox3.Enabled:=true;
  form1.ApplyModel;
end;

procedure TForm1.Button9Click(Sender: TObject);
begin
  button9.Enabled:=false;
  listbox1.Enabled:=true;
  form1.ApplySDood;
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  SDoodoads[listbox1.Items.Count]:=StaticDoodoad.Create;
  listbox1.Items.Add('No name');
  Deselect(listbox1);
  select(listbox1.Items.Count-1,listbox1);
  button7.Click;
end;

procedure TForm1.Edit12Click(Sender: TObject);
var
  x:integer;
begin
  x:=form1.getfirst(listbox1);
  if x=-1 then exit; smi:=x;
  form1.EditSDoodoad(SDoodoads[x]);
end;

procedure TForm1.Edit13Click(Sender: TObject);
var
  x:integer;
begin
  x:=form1.getfirst(listbox3);
  if x=-1 then exit;
  if not isesd then exit;
  smie:=x;
  form1.EditModel(ESDood.Models[x]);
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
  inc(ESDood.ModelCount);
  listbox3.Items.Add('<no path>');
  Deselect(listbox3);
  select(listbox3.Items.Count-1,listbox3);
  button10.Click;
end;

procedure TForm1.Shape1MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if colordialog1.Execute then shape1.Brush.Color:=colordialog1.Color;
end;

procedure TForm1.Deselect(l: TListbox);
var
  i:integer;
begin
  if l.Items.Count=0 then exit;
  for i:=0 to l.Items.Count-1 do
    l.Selected[i]:=false;
end;

procedure TForm1.Select(i: integer; l: TListbox);
begin
  l.Selected[i]:=true;
end;

procedure TForm1.Open1Click(Sender: TObject);
var
  f:CFile;
  s:string;
  n,i:integer;
begin
  if opendialog1.Execute then begin
    f:=CFile.Create;
    f.Open(opendialog1.FileName,true);
    f.ReadString(3,s);//header
    if s<>'PID' then begin
      showmessage('File '+opendialog1.FileName+ ' has unknown format or damaged.');
      f.Close;
      exit;
    end;
    f.ReadInt(n);
    if  listbox1.Items.Count<>0 then
      for i:=0 to listbox1.Items.Count-1 do
        SDoodoads[i].Destroy;
    listbox1.Items.Clear;
    if n=0 then begin
      f.Close;
      exit;
    end;
    for i:=0 to n-1 do begin
      SDoodoads[i]:=StaticDoodoad.Create;
      SDoodoads[i].Read(f);
      listbox1.Items.Add(SDoodoads[i].name);
    end;
    f.Close();
  end;

end;

procedure TForm1.Save1Click(Sender: TObject);
var
  f:CFile;
  s:string;
  n,i:integer;
begin
  if savedialog1.Execute then begin
    s:=savedialog1.FileName;
    s:=changefileext(s,'.pd');
    if fileexists(s) then
      if application.MessageBox(pansichar('File with name '+s+' exists. Overwrite?'),'Warning',mb_Yesno)=7 then
        exit;
    f:=CFile.Create;
    f.Open(s,false);
    f.WriteString('PID');//header
    f.WriteInt(listbox1.Items.Count);
    for i:=0 to listbox1.Items.Count-1 do begin
      SDoodoads[i].Write(f);
    end;
    f.Close();
  end;

end;

end.
