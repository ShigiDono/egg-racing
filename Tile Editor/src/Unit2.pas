unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Spin, StdCtrls;

type
  TForm2 = class(TForm)
    Edit1: TEdit;
    Label1: TLabel;
    SpinEdit1: TSpinEdit;
    Label2: TLabel;
    Button1: TButton;
    Button2: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure ApplyChanges();
    procedure CancelChanges();
  end;

var
  Form2: TForm2;

implementation

uses Unit1;

{$R *.dfm}

procedure TForm2.ApplyChanges;
begin
  form1._name:=edit1.Text;
  form1.tsize:=spinedit1.Value;
  form2.Hide;
  form1.Enabled:=true;
  form1.SetC();
end;

procedure TForm2.Button1Click(Sender: TObject);
begin
  ApplyChanges();
end;

procedure TForm2.CancelChanges;
begin
  form2.Hide;
  form1.Enabled:=true;
end;

procedure TForm2.Button2Click(Sender: TObject);
begin
  CancelChanges;
end;

procedure TForm2.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  CancelChanges;
end;

procedure TForm2.FormShow(Sender: TObject);
begin
  left:=form1.Left+(form1.Width-Width) div 2;
  top:=form1.Top+(form1.Height-Height) div 2;
end;

end.
