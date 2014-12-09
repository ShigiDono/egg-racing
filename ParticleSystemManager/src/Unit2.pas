unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Spin;
{
      name:string;
      emission:integer;
      sa,sr,sg,sb:single;
      ea,er,eg,eb:single;
      va,vr,vg,vb:single;
      ssize,esize,vsize:single;
      sspeed,espeed,vspeed:single;
      elife,plife,plifev:single;
      animcount:shortint;
      anim,un:boolean;
      bc:byte;
      //Fuck!
      x,y,z:single;//dir vector
      tname:string;

  f.ReadNullTerminatedString(name);
  f.ReadNullTerminatedString(tname);
  f.ReadBool(anim);
  f.ReadChar(c);
  animcount:=ord(c);
  f.ReadBool(un);
  f.ReadChar(c);
  bc:=ord(c);
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
  f.ReadFloat(vb);
}

type
  TForm2 = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Edit2: TEdit;
    Edit1: TEdit;
    CheckBox1: TCheckBox;
    Label3: TLabel;
    SpinEdit1: TSpinEdit;
    CheckBox2: TCheckBox;
    SpinEdit2: TSpinEdit;
    Label4: TLabel;
    Label5: TLabel;
    Edit3: TEdit;
    Label6: TLabel;
    Edit4: TEdit;
    Label7: TLabel;
    Edit5: TEdit;
    Label8: TLabel;
    Edit6: TEdit;
    Label9: TLabel;
    Edit7: TEdit;
    Label10: TLabel;
    Edit8: TEdit;
    Label11: TLabel;
    Edit9: TEdit;
    Label12: TLabel;
    Edit10: TEdit;
    Label13: TLabel;
    Edit11: TEdit;
    Label14: TLabel;
    SpinEdit3: TSpinEdit;
    Label15: TLabel;
    SpinEdit4: TSpinEdit;
    Label16: TLabel;
    SpinEdit5: TSpinEdit;
    Label17: TLabel;
    Label18: TLabel;
    SpinEdit6: TSpinEdit;
    SpinEdit7: TSpinEdit;
    Label19: TLabel;
    SpinEdit8: TSpinEdit;
    Label20: TLabel;
    Label21: TLabel;
    SpinEdit9: TSpinEdit;
    SpinEdit10: TSpinEdit;
    Label22: TLabel;
    SpinEdit11: TSpinEdit;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Shape1: TShape;
    Shape2: TShape;
    Shape3: TShape;
    Edit12: TEdit;
    Label26: TLabel;
    Edit13: TEdit;
    Label27: TLabel;
    Edit14: TEdit;
    Label28: TLabel;
    Button1: TButton;
    Button2: TButton;
    SpinEdit12: TSpinEdit;
    Label29: TLabel;
    SpinEdit13: TSpinEdit;
    Label30: TLabel;
    SpinEdit14: TSpinEdit;
    ColorDialog1: TColorDialog;
    Label32: TLabel;
    SpinEdit15: TSpinEdit;
    Label33: TLabel;
    SpinEdit16: TSpinEdit;
    Label31: TLabel;
    procedure SpinEdit3Change(Sender: TObject);
    procedure SpinEdit6Change(Sender: TObject);
    procedure SpinEdit9Change(Sender: TObject);
    procedure Shape1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Shape2MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Shape3MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
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

procedure TForm2.SpinEdit3Change(Sender: TObject);
begin
    shape1.Brush.Color:=rgb(spinedit3.Value,spinedit4.Value,spinedit5.Value);
end;

procedure TForm2.SpinEdit6Change(Sender: TObject);
begin
    shape2.Brush.Color:=rgb(spinedit6.Value,spinedit7.Value,spinedit8.Value);
end;

procedure TForm2.SpinEdit9Change(Sender: TObject);
begin
    shape3.Brush.Color:=rgb(spinedit9.Value,spinedit10.Value,spinedit11.Value);
end;

procedure TForm2.Shape1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
    colordialog1.Color:=shape1.Brush.Color;
    if colordialog1.Execute then begin
        spinedit3.Value:=getrvalue(colordialog1.Color);
        spinedit4.Value:=getgvalue(colordialog1.Color);
        spinedit5.Value:=getbvalue(colordialog1.Color);
        shape1.Brush.Color:=colordialog1.Color;
    end;
end;

procedure TForm2.Shape2MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
    colordialog1.Color:=shape2.Brush.Color;
    if colordialog1.Execute then begin
        spinedit6.Value:=getrvalue(colordialog1.Color);
        spinedit7.Value:=getgvalue(colordialog1.Color);
        spinedit8.Value:=getbvalue(colordialog1.Color);
        shape2.Brush.Color:=colordialog1.Color;
    end;
end;

procedure TForm2.Shape3MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
    colordialog1.Color:=shape3.Brush.Color;
    if colordialog1.Execute then begin
        spinedit9.Value:=getrvalue(colordialog1.Color);
        spinedit10.Value:=getgvalue(colordialog1.Color);
        spinedit11.Value:=getbvalue(colordialog1.Color);
        shape3.Brush.Color:=colordialog1.Color;
    end;
end;

procedure TForm2.Button1Click(Sender: TObject);
begin
    form1.apply();
    form2.Hide;
    form1.Enabled:=true;
end;

procedure TForm2.Button2Click(Sender: TObject);
begin
    form2.Hide;
    form1.Enabled:=true;
end;

procedure TForm2.FormClose(Sender: TObject; var Action: TCloseAction);
begin
    form2.Hide;
    form1.Enabled:=true;
end;

end.
