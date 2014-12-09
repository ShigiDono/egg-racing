unit Unit3;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Spin;

type
  TForm3 = class(TForm)
    Label1: TLabel;
    Edit1: TEdit;
    Label2: TLabel;
    Edit2: TEdit;
    Label3: TLabel;
    SpinEdit1: TSpinEdit;
    SpinEdit2: TSpinEdit;
    Label4: TLabel;
    Shape1: TShape;
    ColorDialog1: TColorDialog;
    Label5: TLabel;
    Button1: TButton;
    OpenDialog1: TOpenDialog;
    Button2: TButton;
    Button3: TButton;
    procedure Shape1MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Button1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
  private
    { Private declarations }
  public
    { Public declarations }
    ind:integer;
    procedure Apply();
    procedure Fin();
  end;

var
  Form3: TForm3;

implementation

uses Unit1, Unit2;

{$R *.dfm}

procedure TForm3.Shape1MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  colordialog1.Color:=shape1.Brush.color;
  if colordialog1.Execute then begin
    shape1.Brush.Color:=colordialog1.Color;
  end;
end;

procedure TForm3.Button1Click(Sender: TObject);
begin
  if opendialog1.Execute then
    label5.Caption:=opendialog1.FileName;
end;

procedure TForm3.Apply;
begin
  form1.tiles[ind].name:=edit1.Text;
  form1.tiles[ind].tname:=edit2.Text;
  form1.tiles[ind].tpname:=label5.Caption;
  if label5.Caption<>'' then begin
    form1.Tiles[ind].PMap.LoadFromFile(label5.Caption);
  end;
  if spinedit1.Value=0 then spinedit1.Value:=
      form1.Tiles[ind].PMap.Width div form1.tsize;
  if spinedit2.Value=0 then spinedit2.Value:=
      form1.Tiles[ind].PMap.Height div form1.tsize;
  form1.tiles[ind].Color:=shape1.Brush.Color;
  form1.tiles[ind].Width:=spinedit1.Value;
  form1.tiles[ind].Height:=spinedit2.Value;
  form1.ListBox1.Items.Strings[ind]:=edit1.Text;
  form1.select(ind);
  form1.Repaint;
end;

procedure TForm3.Fin;
begin
  form1.Enabled:=true;
  form3.Hide;
  form1.Repaint;
end;

procedure TForm3.FormShow(Sender: TObject);
begin
  if ind<0 then begin
    Hide;
    exit;
  end;
  left:=form1.Left+(form1.Width-Width) div 2;
  top:=form1.Top+(form1.Height-Height) div 2;
  edit1.Text:=form1.tiles[ind].name;
  edit2.Text:=form1.tiles[ind].tname;
  label5.Caption:=form1.tiles[ind].tpname;
  shape1.Brush.Color:=form1.tiles[ind].Color;
  spinedit1.Value:=form1.tiles[ind].Width;
  spinedit2.Value:=form1.tiles[ind].Height;
end;

procedure TForm3.Button2Click(Sender: TObject);
begin
  Apply();
  Fin();
end;

procedure TForm3.Button3Click(Sender: TObject);
begin
  Fin();
end;

procedure TForm3.FormClose(Sender: TObject; var Action: TCloseAction);
begin
Fin();
end;

end.
