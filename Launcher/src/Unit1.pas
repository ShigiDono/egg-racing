unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, IniUtils;

type
  TForm1 = class(TForm)
    ComboBox1: TComboBox;
    CheckBox1: TCheckBox;
    ComboBox2: TComboBox;
    CheckBox2: TCheckBox;
    ListBox1: TListBox;
    Memo1: TMemo;
    Button1: TButton;
    Button2: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    GroupBox1: TGroupBox;
    Edit1: TEdit;
    Edit2: TEdit;
    Label5: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure ListBox1Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  Resolution : array[0..100,0..1] of integer;
  Freq: array[0..100] of integer;
  cnt:integer=0;
  cnt1:integer=0;
  Pa:TStringList;

implementation

{$R *.dfm}
procedure AddRes(w,h:integer);
var
  i:integer;
begin
  for i:=0 to cnt-1 do begin
    if i>=cnt then break;
    if (Resolution[i,0]=w) and (Resolution[i,1]=h) then exit;
  end;
      Resolution[cnt,0]:=w;
      Resolution[cnt,1]:=h;
      form1.combobox1.Items.Add(inttostr(resolution[i,0])+'x'+inttostr(resolution[i,1]));
      inc(cnt);

end;
procedure AddFreq(f:integer);
var
  i:integer;
begin
  for i:=0 to cnt1-1 do begin
    if i>=cnt then break;
    if (Freq[i]=f)  then exit;
  end;
      Freq[cnt1]:=f;
      form1.combobox2.Items.Add(inttostr(Freq[i])+'Hz');
      inc(cnt1);

end;
function strtobool(s:string):boolean;
begin
  if length(s)=0 then begin
    Result:=false;
    exit;
  end;
  if s[1]='1' then Result:=true else Result:=false;
end;
function booltostr(b:boolean):string;
begin
  if b then Result:='1' else Result:='0';
end;

procedure TForm1.FormCreate(Sender: TObject);
var
i: Integer;
    modes:array[0..255] of TDevMode;
    w,h:integer;
    ww,hh,ff,aa,wi:string;
  Found, Attr: Integer;
  SearchRec: TSearchRec;
  PlugDir,Nm,Cm,Ds,fn:string;
  EName:string[255];
begin
//  ListBox1.Items.Clear;
  i := 0;
  while EnumDisplaySettings(nil, i, Modes[i]) do
  begin
    if (Modes[i].dmPelsWidth>=640) and (Modes[i].dmPelsHeight>=400) then begin
      AddRes(Modes[i].dmPelsWidth,Modes[i].dmPelsHeight);
    end;
    if Modes[i].dmDisplayFrequency>10 then
    AddFreq(Modes[i].dmDisplayFrequency);
    Inc(i);
  end;
  combobox1.ItemIndex:=0;
  combobox2.ItemIndex:=0;
    ww:=getstring('VIDEO','Width');
    hh:=getstring('VIDEO','Height');
    ff:=getstring('VIDEO','Refresh_Rate');
    aa:=getstring('VIDEO','Antialias');
    wi:=getstring('VIDEO','Windowed');
    edit1.Text:=getstring('SCREENSHOT','Directory');
    edit2.Text:=getstring('SCREENSHOT','FileName');
    checkbox1.Checked:=strtobool(aa);
    checkbox2.Checked:=strtobool(wi);
  for i:=0 to cnt-1 do begin
    if (ww='') or (hh='') then begin
      break;
    end;
    if (Resolution[i,0]=strtoint(ww)) and (Resolution[i,1]=strtoint(hh)) then begin
      combobox1.ItemIndex:=i;
      break;
    end;

  end;
  for i:=0 to cnt-1 do begin
    if (ff='') then begin
      break;
    end;
    if (Freq[i]=strtoint(ff)) then begin
      combobox2.ItemIndex:=i;
      break;
    end;
  end;

  Pa:=TStringList.Create;
//Cl:=TStrings.Create;
//Dl:=TStrings.Create;
  PlugDir := ExtractFilePath (Application. ExeName) + 'data\maps\';
  Attr := faReadOnly or faHidden or faSysFile or faArchive;
  Found := FindFirst(PlugDir+'*.pm', Attr, SearchRec);
  while Found = 0 do begin
      fn:=ExtractFileName(SearchRec.Name);
      listbox1.Items.Add(fn);
      Pa.Add(PlugDir+SearchRec.Name);
      Found:=FindNext(SearchRec);
  end;
end;

procedure TForm1.ListBox1Click(Sender: TObject);
var
  i:integer;
  desf:string;
begin
  for i:=0 to listbox1.items.count-1 do begin
    if listbox1.Selected[i] then begin
      break;
    end;
  end;
  desf:=ChangeFileExt(Pa.Strings[i],'.ion');
  memo1.Lines.Clear;
  if fileexists(desf) then begin
    memo1.Lines.LoadFromFile(desf);
  end;
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  ind1,ind2,ind3,i:integer;
  s,s1,s2:string;
begin
    ind1:=combobox1.ItemIndex;
    ind2:=combobox2.ItemIndex;
    ind3:=-1;
  for i:=0 to listbox1.items.count-1 do begin
    if listbox1.Selected[i] then begin
      ind3:=i;
      break;
    end;
  end;
  if ind3=-1 then begin
    showmessage('No map was selected!');
    exit;
  end;
    _WriteString('VIDEO','Width',inttostr(Resolution[ind1,0]));
    _WriteString('VIDEO','Height',inttostr(Resolution[ind1,1]));
    _WriteString('VIDEO','Refresh_Rate',inttostr(Freq[ind2]));
    _WriteString('VIDEO','Antialias',booltostr(checkbox1.Checked));
    _WriteString('VIDEO','Windowed',booltostr(checkbox2.Checked));
    _WriteString('SCREENSHOT','Directory',edit1.Text);
    _WriteString('SCREENSHOT','FileName',edit2.Text);
    s1:=ExtractFilePath (Application. ExeName);
    s:=Pa.Strings[ind3];//
    s2:='';
    for i:=1 to length(s)-length(s1) do
      s2:=s2+s[i+length(s1)];
    _WriteString('MAP','FileName',Pa.Strings[ind3]);
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  ind1,ind2,ind3,i:integer;
  s,s1,s2:string;
begin
    ind1:=combobox1.ItemIndex;
    ind2:=combobox2.ItemIndex;
    ind3:=-1;
  for i:=0 to listbox1.items.count-1 do begin
    if listbox1.Selected[i] then begin
      ind3:=i;
      break;
    end;
  end;
  if ind3=-1 then begin
    showmessage('No map was selected!');
    exit;
  end;
    _WriteString('VIDEO','Width',inttostr(Resolution[ind1,0]));
    _WriteString('VIDEO','Height',inttostr(Resolution[ind1,1]));
    _WriteString('VIDEO','Refresh_Rate',inttostr(Freq[ind2]));
    _WriteString('VIDEO','Antialias',booltostr(checkbox1.Checked));
    _WriteString('VIDEO','Windowed',booltostr(checkbox2.Checked));
    _WriteString('SCREENSHOT','Directory',edit1.Text);
    _WriteString('SCREENSHOT','FileName',edit2.Text);
    s1:=ExtractFilePath (Application. ExeName);
    s:=Pa.Strings[ind3];//
    s2:='';
    for i:=1 to length(s)-length(s1) do
      s2:=s2+s[i+length(s1)];
    _WriteString('MAP','FileName',s2);
//  CreateProcess(PANSICHAR(ExtractFilePath (Application. ExeName)+'EggRacing.exe'),nil,nil,nil,true,HIGH_PRIORITY_CLASS	,nil,PANSICHAR(ExtractFilePath (Application. ExeName)),nil,nil);
  winExec(PANSICHAR(ExtractFilePath (Application. ExeName)+'EggRacing.exe'),SW_SHOW);
  application.Terminate;
end;

end.
