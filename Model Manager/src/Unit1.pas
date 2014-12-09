unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, StdCtrls, FileBin;

type
  TForm1 = class(TForm)
    PageControl1: TPageControl;
    Model: TTabSheet;
    Mesh: TTabSheet;
    Texture: TTabSheet;
    PS: TTabSheet;
    Edit1: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Edit2: TEdit;
    Edit3: TEdit;
    Label3: TLabel;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    Label4: TLabel;
    Edit4: TEdit;
    Label5: TLabel;
    Edit5: TEdit;
    Label6: TLabel;
    Edit6: TEdit;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    CheckBox5: TCheckBox;
    Edit7: TEdit;
    Edit8: TEdit;
    Label7: TLabel;
    Label8: TLabel;
    Edit9: TEdit;
    Label9: TLabel;
    Label10: TLabel;
    Edit10: TEdit;
    Button1: TButton;
    Button2: TButton;
    Label11: TLabel;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
f:CFile;
s:string;
begin
  if savedialog1.Execute then begin
    s:=savedialog1.FileName;
    s:=changefileext(s,'.pmd');
    if fileexists(s) then
      if application.MessageBox(pansichar('File with name '+s+' exists. Overwrite?'),'Warning',mb_Yesno)=7 then
        exit;
    f:=CFile.Create;
    f.Open(s,false);
    f.WriteString('PMD');
    f.WriteNullTerminatedString(edit1.Text);
    f.WriteNullTerminatedString(edit2.Text);
    f.WriteNullTerminatedString(edit3.Text);
    f.WriteNullTerminatedString(edit9.Text);
    f.WriteBool(checkbox1.Checked);
    f.WriteBool(checkbox2.Checked);
    f.WriteFloat(strtofloat(edit4.Text));
    f.WriteFloat(strtofloat(edit5.Text));
    f.WriteFloat(strtofloat(edit6.Text));
    f.WriteBool(checkbox4.Checked);
    f.WriteBool(checkbox3.Checked);
    f.WriteBool(checkbox5.Checked);
    f.WriteNullTerminatedString(edit7.Text);
    f.WriteNullTerminatedString(edit8.Text);
    f.WriteNullTerminatedString(edit10.Text);
    f.Close();
  end;
end;

procedure TForm1.Button2Click(Sender: TObject);
var
f:CFile;
s:string;
b:boolean;
fl:single;
begin
  if opendialog1.Execute then begin
    s:=opendialog1.FileName;
    f:=CFile.Create;
    f.Open(s,true);
    f.ReadString(3,s);
    if s<>'PMD' then begin
      showmessage('file has unknown format or damaged.');
      f.Close;
      exit;
    end;
    f.ReadNullTerminatedString(s);
    edit1.Text:=s;
    f.ReadNullTerminatedString(s);
    edit2.Text:=s;
    f.ReadNullTerminatedString(s);
    edit3.Text:=s;
    f.ReadNullTerminatedString(s);
    edit9.Text:=s;
    f.ReadBool(b);
    checkbox1.Checked:=b;
    f.ReadBool(b);
    checkbox2.Checked:=b;
    f.ReadFloat(fl);
    edit4.Text:=floattostr(fl);
    f.ReadFloat(fl);
    edit5.Text:=floattostr(fl);
    f.ReadFloat(fl);
    edit6.Text:=floattostr(fl);
    f.ReadBool(b);
    checkbox4.Checked:=b;
    f.ReadBool(b);
    checkbox3.Checked:=b;
    f.ReadBool(b);
    checkbox5.Checked:=b;
    f.ReadNullTerminatedString(s);
    edit7.Text:=s;
    f.ReadNullTerminatedString(s);
    edit8.Text:=s;
    f.ReadNullTerminatedString(s);
    edit10.Text:=s;
    f.Close();
  end;
end;

end.
