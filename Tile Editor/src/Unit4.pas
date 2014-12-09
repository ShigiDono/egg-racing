unit Unit4;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm4 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    Button3: TButton;
    procedure Button1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button3Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    x:^byte;
  end;

var
  Form4: TForm4;

implementation

uses Unit1;

{$R *.dfm}
function bti(b:boolean):integer;
begin
  if b then Result:=1 else Result:=0;
end;
function itb(b:integer):boolean;
begin
  if b>0 then Result:=true else Result:=false;
end;

procedure TForm4.Button1Click(Sender: TObject);
begin
  x^:=(bti(checkbox1.Checked) shl 3)+(bti(checkbox2.Checked) shl 2)+
      (bti(checkbox3.Checked) shl 1)+bti(checkbox4.Checked);
  Hide;
  form1.Enabled:=true;
end;

procedure TForm4.FormShow(Sender: TObject);
var
  pp:TPoint;
  i:integer;
begin
  GetCursorPos(PP);
  Left:=pp.X-Width div 2;
  Top:=pp.Y- Height div 2;
  i:=x^;
  checkbox1.Checked:=itb(i shr 3);
  i:=i-(i shr 3) shl 3;
  checkbox2.Checked:=itb(i shr 2);
  i:=i-(i shr 2) shl 2;
  checkbox3.Checked:=itb(i shr 1);
  i:=i-(i shr 1) shl 1;
  checkbox4.Checked:=itb(i);
end;

procedure TForm4.Button2Click(Sender: TObject);
begin
  Hide;
  form1.Enabled:=true;

end;

procedure TForm4.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Hide;
  form1.Enabled:=true;
end;

procedure TForm4.Button3Click(Sender: TObject);
begin
checkbox1.Checked:=true;
checkbox2.Checked:=true;
checkbox3.Checked:=true;
checkbox4.Checked:=true;
end;

end.
