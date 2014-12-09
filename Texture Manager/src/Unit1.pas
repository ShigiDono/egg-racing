unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Spin, FileBin;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    Edit1: TEdit;
    CheckBox1: TCheckBox;
    SpinEdit1: TSpinEdit;
    SpinEdit2: TSpinEdit;
    Label2: TLabel;
    Shape1: TShape;
    CheckBox2: TCheckBox;
    Edit2: TEdit;
    CheckBox3: TCheckBox;
    SpinEdit3: TSpinEdit;
    SpinEdit4: TSpinEdit;
    Label4: TLabel;
    Shape2: TShape;
    CheckBox4: TCheckBox;
    Button1: TButton;
    Button2: TButton;
    CheckBox5: TCheckBox;
    ColorDialog1: TColorDialog;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    CheckBox6: TCheckBox;
    Edit3: TEdit;
    Label5: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Shape1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Shape2MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure SpinEdit1Change(Sender: TObject);
    procedure SpinEdit2Change(Sender: TObject);
    procedure Edit2Change(Sender: TObject);
    procedure CheckBox4Click(Sender: TObject);
    procedure CheckBox3Click(Sender: TObject);
    procedure SpinEdit3Change(Sender: TObject);
    procedure SpinEdit4Change(Sender: TObject);
    procedure CheckBox6Click(Sender: TObject);
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
  str:string;
begin
  if savedialog1.Execute then begin
    str:=savedialog1.FileName;
    str:=ChangeFileExt(str,'.ptt');
    savedialog1.FileName:=str;
    if (fileexists(str)) and (application.MessageBox(PANSICHAR('File with name '+str+' exists. Overwrite?'),PANSICHAR('Warning!'),mb_YesNo)<>6) then
      exit;
    f:=CFile.Create;
    if not f.Open(str,false) then begin
      f.Close;
      exit;
    end;
    f.WriteString('PTT');
    f.WriteNullTerminatedString(edit3.Text);
    f.WriteNullTerminatedString(edit1.Text);
    f.WriteBool(checkbox2.Checked);
    if  checkbox2.Checked then
      f.WriteInt(shape1.Brush.Color);
    f.WriteBool(checkbox1.Checked);
    if  checkbox1.Checked then begin
      f.WriteInt(spinedit1.Value);
      f.WriteInt(spinedit2.Value);
    end;
    f.WriteBool(checkbox5.Checked);
    if  checkbox5.Checked then begin
      f.WriteBool(checkbox6.Checked);
      if not checkbox6.Checked then begin
        f.WriteNullTerminatedString(edit2.Text);
        f.WriteBool(checkbox4.Checked);
        if  checkbox4.Checked then
          f.WriteInt(shape2.Brush.Color);
        f.WriteBool(checkbox3.Checked);
        if  checkbox3.Checked then begin
          f.WriteInt(spinedit3.Value);
          f.WriteInt(spinedit4.Value);
        end;
      end;
    end;
    f.Close;
    f.Destroy;
  end;
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  f:CFile;
  str:string;
  i:integer;
  b:boolean;
begin
if opendialog1.Execute then begin
  f:=CFile.Create;
  if not f.Open(opendialog1.FileName,true) then
  begin
    f.Close;
    exit;
  end;
  f.ReadString(3,str);
  if str<>'PTT' then begin
    showmessage('Error!!!!!!');
    f.Close;
    exit;
  end;
    f.ReadNullTerminatedString(str);
    edit3.Text:=str;
    f.ReadNullTerminatedString(str);
    edit1.Text:=str;
    f.ReadBool(b);
    checkbox2.Checked:=b;
    if  b then begin
      f.ReadInt(i);
      shape1.Brush.Color:=i;
    end;
    f.ReadBool(b);
    checkbox1.Checked:=b;
    if  b then begin
      f.ReadInt(i);
      spinedit1.Value:=i;
      f.ReadInt(i);
      spinedit2.Value:=i;
    end;
    f.ReadBool(b);
    checkbox5.Checked:=b;
    if b then begin
      f.ReadBool(b);
      checkbox6.Checked:=b;
      if b then begin
        f.ReadNullTerminatedString(str);
        edit2.Text:=str;
        f.ReadBool(b);
        checkbox4.Checked:=b;
        if  b then begin
          f.ReadInt(i);
          shape2.Brush.Color:=i;
        end;
        f.ReadBool(b);
        checkbox3.Checked:=b;
        if  b then begin
          f.ReadInt(i);
          spinedit3.Value:=i;
          f.ReadInt(i);
          spinedit4.Value:=i;
        end;
      end;
    end;
  f.Close;
  f.Destroy;
end;
end;

procedure TForm1.Shape1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
   colordialog1.Color:=shape1.Brush.Color;
   if colordialog1.Execute then begin
    shape1.Brush.Color:=colordialog1.Color;
    checkbox2.Checked:=true;
   end;
end;

procedure TForm1.Shape2MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
   colordialog1.Color:=shape2.Brush.Color;
   if colordialog1.Execute then begin
    shape2.Brush.Color:=colordialog1.Color;
    checkbox4.Checked:=true;
    checkbox5.Checked:=true;
   end;
end;

procedure TForm1.SpinEdit1Change(Sender: TObject);
begin
  checkbox1.Checked:=true;
end;

procedure TForm1.SpinEdit2Change(Sender: TObject);
begin
  checkbox1.Checked:=true;
end;

procedure TForm1.Edit2Change(Sender: TObject);
begin
  checkbox5.Checked:=true; 
end;

procedure TForm1.CheckBox4Click(Sender: TObject);
begin
  checkbox5.Checked:=true;
end;

procedure TForm1.CheckBox3Click(Sender: TObject);
begin
  checkbox5.Checked:=true;
end;

procedure TForm1.SpinEdit3Change(Sender: TObject);
begin
  checkbox5.Checked:=true;
  checkbox3.Checked:=true;
end;

procedure TForm1.SpinEdit4Change(Sender: TObject);
begin
  checkbox5.Checked:=true;
  checkbox3.Checked:=true;
end;

procedure TForm1.CheckBox6Click(Sender: TObject);
begin
  checkbox5.Checked:=true;
end;

end.
