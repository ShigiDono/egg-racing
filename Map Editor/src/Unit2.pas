unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm2 = class(TForm)
    Edit1: TEdit;
    Label1: TLabel;
    ComboBox1: TComboBox;
    ComboBox2: TComboBox;
    Label2: TLabel;
    Button1: TButton;
    Button2: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation

uses Unit1;

{$R *.dfm}

procedure TForm2.Button1Click(Sender: TObject);
var
  i:integer;
  _r:TRect;
  c:char;
  s:string;
  d,d1,_w,_h,j:integer;
begin
  _w:=8;
  _h:=8;
  for i:=0 to combobox1.ItemIndex do begin
    _w:=_w*2;
  end;
  for i:=0 to combobox2.ItemIndex do begin
    _h:=_h*2;
  end;
  w:=_w;
  h:=_h;
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
  hbitmap.Canvas.Brush.Color:=0;
  hbitmap.Canvas.FillRect(_r);
  cbitmap.Canvas.Brush.Color:=Colors[1];
  cbitmap.Canvas.FillRect(_r);
  form1.Enabled:=true;
  form1.Edit2.text:=edit1.text;
  form1.ComboBox2.ItemIndex:=combobox1.ItemIndex;
  form1.ComboBox3.ItemIndex:=combobox2.ItemIndex;
  dx:=0;
  dy:=0;
  zoom:=1;
  DoodCount:=0;
  DoodIndC:=0;
  form1.repaint;
  Hide;
  form1.pagecontrol1.Enabled:=true;
end;

procedure TForm2.Button2Click(Sender: TObject);
begin
  form1.Enabled:=true;
  Hide;
end;

end.
