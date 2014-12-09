unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, FileBin;

type
  TForm1 = class(TForm)
    ListBox1: TListBox;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Label1: TLabel;
    Button6: TButton;
    SaveDialog1: TSaveDialog;
    OpenDialog1: TOpenDialog;
    Button7: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    function GetSel():integer;
    procedure apply();
  end;
{
	char				name[32];         //
	int					emission, nedocreated;//
	scalar				sr,sg,sb,sa;          //
	scalar				er,eg,eb,ea;            //
	scalar				vr,vg,vb,va;              //
	scalar				startsize, endsize, sizevar;//
	scalar				sspeed,vspeed,espeed;    //
	scalar				plife, plifevar;          ///
	scalar				life, age;         //
	short				animcount;  //
	bool				animated;     //
	BYTE				BlendKind;         //
	bool				UseNormal;      //
	PTexture			txt;           //
}
  Preset = class
      name:string;
      emission:integer;
      sa,sr,sg,sb:single;
      ea,er,eg,eb:single;
      va,vr,vg,vb:single;
      ssize,esize,vsize:single;
      sspeed,espeed,vspeed:single;
      elife,plife,plifev:single;
      animcount,fcount:shortint;
      anim,un:boolean;
      bc:byte;
      //Fuck!
      x,y,z:single;//dir vector
      tname:string;


  private
      {}
  public
      {}
      procedure Write(f:CFile);
      procedure Read(f:CFile);
  end;

var
  Form1: TForm1;
  pr:array[0..1000] of Preset;
  Count,ed:integer;

implementation

uses Unit2;

{$R *.dfm}
//    str:=ChangeFileExt(str,'.ptt');
procedure Edit(ind:integer);
begin
    //
    form2.Edit1.Text:=pr[ind].name;
    form2.Edit2.Text:=pr[ind].tname;
    form2.CheckBox1.Checked:=pr[ind].anim;
    form2.SpinEdit1.Value:=pr[ind].animcount;
    form2.CheckBox2.Checked:=pr[ind].un;
    form2.SpinEdit2.Value:=pr[ind].bc;
    form2.SpinEdit15.Value:=pr[ind].emission;
    form2.SpinEdit16.Value:=pr[ind].fcount;
    form2.Edit3.Text:=floattostr(pr[ind].plife);
    form2.Edit4.Text:=floattostr(pr[ind].plifev);
    form2.Edit5.Text:=floattostr(pr[ind].elife);
    form2.Edit6.Text:=floattostr(pr[ind].sspeed);
    form2.Edit7.Text:=floattostr(pr[ind].espeed);
    form2.Edit8.Text:=floattostr(pr[ind].vspeed);
    form2.Edit9.Text:=floattostr(pr[ind].x);
    form2.Edit10.Text:=floattostr(pr[ind].y);
    form2.Edit11.Text:=floattostr(pr[ind].z);
    form2.SpinEdit12.Value:=round(pr[ind].sa);
    form2.SpinEdit13.Value:=round(pr[ind].ea);
    form2.SpinEdit14.Value:=round(pr[ind].va);
    form2.SpinEdit3.Value:=round(pr[ind].sr);
    form2.SpinEdit6.Value:=round(pr[ind].er);
    form2.SpinEdit9.Value:=round(pr[ind].vr);
    form2.SpinEdit4.Value:=round(pr[ind].sg);
    form2.SpinEdit7.Value:=round(pr[ind].eg);
    form2.SpinEdit10.Value:=round(pr[ind].vg);
    form2.SpinEdit5.Value:=round(pr[ind].sb);
    form2.SpinEdit8.Value:=round(pr[ind].eb);
    form2.SpinEdit11.Value:=round(pr[ind].vb);
    form2.Edit12.Text:=floattostr(pr[ind].ssize);
    form2.Edit13.Text:=floattostr(pr[ind].esize);
    form2.Edit14.Text:=floattostr(pr[ind].vsize);
    form2.Show;
    form1.Enabled:=false;
    ed:=ind;
end;
procedure Delete(ind:integer);
  var
    i:integer;
    t:Preset;
begin
    form1.ListBox1.Items.Delete(ind);
    for i:=ind to Count-1 do
    begin
        t:=pr[i];
        pr[i]:=pr[i+1];
        pr[i+1]:=t;
    end;
    pr[Count]:=pr[Count-1];
    i:=count;
    pr[i].name:='Preset '+inttostr(i);
    pr[i].emission:=50;
    pr[i].sa:=255;
    pr[i].sr:=255;
    pr[i].sg:=255;
    pr[i].sb:=255;

    pr[i].ea:=0;
    pr[i].er:=0;
    pr[i].eg:=0;
    pr[i].eb:=0;

    pr[i].va:=0;
    pr[i].vr:=0;
    pr[i].vg:=0;
    pr[i].vb:=0;

    pr[i].ssize:=1;
    pr[i].esize:=2;
    pr[i].vsize:=0;

    pr[i].sspeed:=1;
    pr[i].vspeed:=0;
    pr[i].espeed:=1;

    pr[i].elife:=-1;
    pr[i].plife:=3;
    pr[i].plifev:=0.5;
    pr[i].animcount:=0;
    pr[i].fcount:=0;
    pr[i].anim:=true;
    pr[i].un:=true;
    pr[i].tname:='Texture name';
    pr[i].x:=0;
    pr[i].y:=0;
    pr[i].z:=0;
    dec(count);
end;

{ Preset }

procedure Preset.Read(f: CFile);
var
  c:char;
begin
  f.ReadNullTerminatedString(name);
  f.ReadNullTerminatedString(tname);
  f.ReadBool(anim);
  f.ReadChar(c);
  animcount:=ord(c);
  f.ReadChar(c);
  fcount:=ord(c);
  f.ReadBool(un);
  f.ReadChar(c);
  bc:=ord(c);
  f.ReadInt(emission);
  f.ReadFloat(plife);
  f.ReadFloat(plifev);
  f.ReadFloat(elife);
  f.ReadFloat(sspeed);
  f.ReadFloat(espeed);
  f.ReadFloat(vspeed);
  f.ReadFloat(x);
  f.ReadFloat(y);
  f.ReadFloat(z);
  f.ReadFloat(sa);
  f.ReadFloat(sr);
  f.ReadFloat(sg);
  f.ReadFloat(sb);

  f.ReadFloat(ea);
  f.ReadFloat(er);
  f.ReadFloat(eg);
  f.ReadFloat(eb);

  f.ReadFloat(va);
  f.ReadFloat(vr);
  f.ReadFloat(vg);
  f.ReadFloat(vb);

  f.ReadFloat(ssize);
  f.ReadFloat(esize);
  f.ReadFloat(vsize);
//  f.ReadFloat(vb);


//    sa,sr,sg,sb:single;
//    ea,er,eg,eb:single;
//    va,vr,vg,vb:single;
//    ssize,esize,vsize:single;
//    sspeed,espeed,vspeed:single;
//    elife,plife,plifev:single;
//    animcount:smallint;
//    anim,un:boolean;
//    bc:byte;
      //Fuck!
//      x,y,z;single;//dir vector
//      tname:string;

end;

procedure Preset.Write(f: CFile);
var
  c:char;
begin
  f.WriteNullTerminatedString(name);
  f.WriteNullTerminatedString(tname);
  f.WriteBool(anim);
  c:=chr(animcount);
  f.WriteChar(c);
  c:=chr(fcount);
  f.WriteChar(c);
  f.WriteBool(un);
  c:=chr(bc);
  f.WriteChar(c);
  f.WriteInt( emission);
  f.WriteFloat(plife);
  f.WriteFloat(plifev);
  f.WriteFloat(elife);
  f.WriteFloat(sspeed);
  f.WriteFloat(espeed);
  f.WriteFloat(vspeed);
  f.WriteFloat(x);
  f.WriteFloat(y);
  f.WriteFloat(z);
  f.WriteFloat(sa);
  f.WriteFloat(sr);
  f.WriteFloat(sg);
  f.WriteFloat(sb);

  f.WriteFloat(ea);
  f.WriteFloat(er);
  f.WriteFloat(eg);
  f.WriteFloat(eb);

  f.WriteFloat(va);
  f.WriteFloat(vr);
  f.WriteFloat(vg);
  f.WriteFloat(vb);

  f.WriteFloat(ssize);
  f.WriteFloat(esize);
  f.WriteFloat(vsize);
//  f.WriteFloat(vb);
end;

procedure TForm1.FormCreate(Sender: TObject);
  var
    i:integer;
begin
  for i:=0 to 1000 do begin
    pr[i]:=Preset.Create;
    pr[i].name:='Preset '+inttostr(i);
    pr[i].emission:=50;
    pr[i].sa:=255;
    pr[i].sr:=255;
    pr[i].sg:=255;
    pr[i].sb:=255;

    pr[i].ea:=0;
    pr[i].er:=0;
    pr[i].eg:=0;
    pr[i].eb:=0;

    pr[i].va:=0;
    pr[i].vr:=0;
    pr[i].vg:=0;
    pr[i].vb:=0;

    pr[i].ssize:=1;
    pr[i].esize:=2;
    pr[i].vsize:=0;

    pr[i].sspeed:=1;
    pr[i].vspeed:=0;
    pr[i].espeed:=1;

    pr[i].elife:=-1;
    pr[i].plife:=3;
    pr[i].plifev:=0.5;
    pr[i].animcount:=0;
    pr[i].fcount:=0;
    pr[i].anim:=true;
    pr[i].un:=true;
    pr[i].tname:='Texture name';
    pr[i].x:=0;
    pr[i].y:=0;
    pr[i].z:=0;
  end;
  count:=0;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
    listbox1.Items.Add(pr[count].name);
    Edit(count);
    Count:=count+1;
end;

function TForm1.GetSel: integer;
  var
    i:integer;
begin
    Result:=-1;
    for i:=0 to listbox1.Items.Count-1 do
      if listbox1.Selected[i] then
      begin
        Result:=i;
        exit;
      end;
end;

procedure TForm1.Button5Click(Sender: TObject);
  var
    i:integer;
begin
  listbox1.Items.Clear;
  for i:=0 to 1000 do begin
    pr[i].name:='Preset '+inttostr(i);
    pr[i].emission:=50;
    pr[i].sa:=255;
    pr[i].sr:=255;
    pr[i].sg:=255;
    pr[i].sb:=255;

    pr[i].ea:=0;
    pr[i].er:=0;
    pr[i].eg:=0;
    pr[i].eb:=0;

    pr[i].va:=0;
    pr[i].vr:=0;
    pr[i].vg:=0;
    pr[i].vb:=0;

    pr[i].ssize:=1;
    pr[i].esize:=2;
    pr[i].vsize:=0;

    pr[i].sspeed:=1;
    pr[i].vspeed:=0;
    pr[i].espeed:=1;

    pr[i].elife:=-1;
    pr[i].plife:=3;
    pr[i].plifev:=0.5;
    pr[i].animcount:=0;
    pr[i].fcount:=0;
    pr[i].anim:=true;
    pr[i].un:=true;
    pr[i].tname:='Texture name';
    pr[i].x:=0;
    pr[i].y:=0;
    pr[i].z:=0;
  end;
  count:=0;
end;

procedure TForm1.apply;
var
  ind:integer;
begin
  //___This_is_a_free_sample___\\
  ind:=ed;
  pr[ind].name := form2.Edit1.Text;
  listbox1.Items.Strings[ind]:=pr[ind].name;
  pr[ind].tname := form2.Edit2.Text;
  pr[ind].anim := form2.CheckBox1.Checked;
  pr[ind].animcount := form2.SpinEdit1.Value;
  pr[ind].un := form2.CheckBox2.Checked;
  pr[ind].bc := form2.SpinEdit2.Value;
  pr[ind].plife := StrToFloat(form2.Edit3.Text);
  pr[ind].plifev := StrToFloat(form2.Edit4.Text);
  pr[ind].elife := StrToFloat(form2.Edit5.Text);
  pr[ind].sspeed := StrToFloat(form2.Edit6.Text);
  pr[ind].espeed := StrToFloat(form2.Edit7.Text);
  pr[ind].vspeed := StrToFloat(form2.Edit8.Text);
  pr[ind].x := StrToFloat(form2.Edit9.Text);
  pr[ind].y := StrToFloat(form2.Edit10.Text);
  pr[ind].z := StrToFloat(form2.Edit11.Text);
  pr[ind].sa := ROUND(form2.SpinEdit12.Value);
  pr[ind].ea := ROUND(form2.SpinEdit13.Value);
  pr[ind].va := ROUND(form2.SpinEdit14.Value);
  pr[ind].sr := ROUND(form2.SpinEdit3.Value);
  pr[ind].er := ROUND(form2.SpinEdit6.Value);
  pr[ind].vr := ROUND(form2.SpinEdit9.Value);
  pr[ind].sg := ROUND(form2.SpinEdit4.Value);
  pr[ind].eg := ROUND(form2.SpinEdit7.Value);
  pr[ind].vg := ROUND(form2.SpinEdit10.Value);
  pr[ind].sb := ROUND(form2.SpinEdit5.Value);
  pr[ind].eb := ROUND(form2.SpinEdit8.Value);
  pr[ind].vb := ROUND(form2.SpinEdit11.Value);
  pr[ind].ssize := StrToFloat(form2.Edit12.Text);
  pr[ind].esize := StrToFloat(form2.Edit13.Text);
  pr[ind].vsize := StrToFloat(form2.Edit14.Text);
  pr[ind].emission := form2.SpinEdit15.Value;
  pr[ind].fcount := form2.SpinEdit16.Value;
end;

procedure TForm1.Button2Click(Sender: TObject);
  var
    i:integer;
begin
    i:=getsel();
    if i>=0 then begin
      Edit(i);
    end;
end;

procedure TForm1.Button3Click(Sender: TObject);
var
  i:integer;
begin
  i:=getsel();
  if (i>=0) then
    delete(i);
end;

procedure TForm1.Button4Click(Sender: TObject);
var
  i:integer;
begin
  i:=getsel();
  if i=-1 then exit;
//Textures\Particle systems\P_Plazma01.png
  pr[Count].name:=pr[i].name;
  pr[Count].emission:=pr[i].emission;
  pr[Count].sa:=pr[i].sa;
  pr[Count].sr:=pr[i].sr;
  pr[Count].sg:=pr[i].sg;
  pr[Count].sb:=pr[i].sb;
  pr[Count].ea:=pr[i].ea;
  pr[Count].er:=pr[i].er;
  pr[Count].eg:=pr[i].eg;
  pr[Count].eb:=pr[i].eb;
  pr[Count].va:=pr[i].va;
  pr[Count].vr:=pr[i].vr;
  pr[Count].vg:=pr[i].vg;
  pr[Count].vb:=pr[i].vb;
  pr[Count].ssize:=pr[i].ssize;
  pr[Count].esize:=pr[i].esize;
  pr[Count].vsize:=pr[i].vsize;
  pr[Count].sspeed:=pr[i].sspeed;
  pr[Count].espeed:=pr[i].espeed;
  pr[Count].vspeed:=pr[i].vspeed;
  pr[Count].elife:=pr[i].elife;
  pr[Count].plife:=pr[i].plife;
  pr[Count].plifev:=pr[i].plifev;
  pr[Count].animcount:=pr[i].animcount;
  pr[Count].anim:=pr[i].anim;
  pr[Count].fcount:=pr[i].fcount;
  pr[Count].un:=pr[i].un;
  pr[Count].bc:=pr[i].bc;
  pr[Count].x:=pr[i].x;
  pr[Count].y:=pr[i].y;
  pr[Count].z:=pr[i].z;
  pr[Count].tname:=pr[i].tname;
  pr[Count].name:=pr[Count].name+' copy';
  listbox1.Items.Add(pr[Count].name);
  Count:=Count+1;

end;

procedure TForm1.Button6Click(Sender: TObject);
var
  f:CFile;
  str:string;
  i:integer;
begin
  if savedialog1.Execute then begin
    str:=savedialog1.FileName;
    str:=ChangeFileExt(str,'.pps');
    savedialog1.FileName:=str;
    if (fileexists(str)) and (application.MessageBox(PANSICHAR('File with name '+str+' exists. Overwrite?'),PANSICHAR('Warning!'),mb_YesNo)<>6) then
      exit;
    f:=CFile.Create;
    if not f.Open(str,false) then begin
      f.Close;
      exit;
    end;
    f.WriteString('PPS');
    f.WriteWord(listbox1.Items.Count);
    if listbox1.Items.Count<>0 then
    for i:=0 to listbox1.Items.Count-1 do begin
      pr[i].Write(f);
    end;
    f.Close();
  end;
end;


procedure TForm1.Button7Click(Sender: TObject);
var
  f:CFile;
  str,s:string;
  i:integer;
  w:word;
begin
  if opendialog1.Execute then begin
    str:=opendialog1.FileName;
    f:=CFile.Create;
    if not f.Open(str,true) then begin
      f.Close;
      exit;
    end;
    f.ReadString(3,s);
    if s<>'PPS' then begin
      application.MessageBox('Unknown file format!','Error',mb_ok);
      f.Close;
      exit;
    end;
    f.readWord(w);
    Count:=w;
    listbox1.Items.Clear;
    if w<>0 then
    for i:=0 to w-1 do begin
      pr[i].Read(f);
      listbox1.Items.Add(pr[i].name);
    end;
    f.Close();
  end;
end;
end.


