unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Menus, Spin;

type
  TForm1 = class(TForm)
    OpenDialog1: TOpenDialog;
    Button1: TButton;
    ListBox1: TListBox;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    SaveDialog1: TSaveDialog;
    PopupMenu1: TPopupMenu;
    Sort1: TMenuItem;
    MoveUp1: TMenuItem;
    MoveDown1: TMenuItem;
    Remove1: TMenuItem;
    Doit1: TMenuItem;
    Add1: TMenuItem;
    SelectAll1: TMenuItem;
    SpinEdit1: TSpinEdit;
    SpinEdit2: TSpinEdit;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Sort1Click(Sender: TObject);
    procedure SelectAll1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    function getsel:integer;
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}
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

procedure TForm1.Button1Click(Sender: TObject);
var
  i:integer;
begin
  if opendialog1.Execute then begin
    if opendialog1.Files.Count=0 then
    exit;
    for i:=0 to opendialog1.Files.Count-1 do begin
      listbox1.Items.Add(opendialog1.Files.Strings[i]);
    end;
  end;
end;

procedure TForm1.Button2Click(Sender: TObject);
var
  i,j,c:integer;
begin
  j:=0;
  for i:=0 to listbox1.Items.Count-1 do begin
    if listbox1.Selected[i+j] then begin
      listbox1.items.Delete(i+j);dec(j);
    end;
    if i+j>listbox1.Items.Count-1 then exit;
    if i+1+j>listbox1.Items.Count-1 then exit;
  end;
end;

procedure TForm1.Button3Click(Sender: TObject);
var
  i:integer;
  s:string;
begin
  i:=getsel();
  if i<=0 then exit;
  s:=listbox1.Items.Strings[i-1];
  listbox1.Items.Strings[i-1]:=listbox1.Items.Strings[i];
  listbox1.Selected[i-1]:=true;
  listbox1.Items.Strings[i]:=s;

end;

procedure TForm1.Button4Click(Sender: TObject);
var
  i:integer;
  s:string;
begin
  i:=getsel();
  if i<0 then exit;
  if i>= listbox1.Items.Count-1 then exit;
  s:=listbox1.Items.Strings[i+1];
  listbox1.Items.Strings[i+1]:=listbox1.Items.Strings[i];
  listbox1.Selected[i+1]:=true;
  listbox1.Items.Strings[i]:=s;
end;

procedure TForm1.Button5Click(Sender: TObject);
var
  btm1,resbtm:TBitmap;
  s:string;
  w,h,wt,ht,x,y,c:integer;
  dr,sr:TRect;
begin
  if savedialog1.Execute then begin
    s:=savedialog1.filename;
    s:=changefileext(s,'.bmp');
    savedialog1.FileName:=s;
    btm1:=tbitmap.Create;
    resbtm:=tbitmap.Create;

    btm1.LoadFromFile(listbox1.Items.Strings[0]);
    w:=btm1.Width;
    h:=btm1.Height;

    wt:=spinedit1.Value;
    ht:=spinedit2.Value;
    resbtm.Width:=w*wt;
    resbtm.Height:=h*ht;
    c:=0;
    sr.Left:=0;
    sr.Top:=0;
    sr.Bottom:=h-1;
    sr.Right:=w-1;
    for y:=0 to ht-1 do begin
      for x:=0 to wt-1 do begin
        if c<listbox1.Items.Count then begin
          btm1.LoadFromFile(listbox1.Items.Strings[c]);
          dr.Left:=x*w;
          dr.Top:=y*h;
          dr.Right:=dr.Left+w;
          dr.Bottom:=dr.Top+h;
          resbtm.Canvas.CopyRect(dr,btm1.Canvas,sr);
          c:=c+1;
        end;
      end;
    end;
    resbtm.SaveToFile(savedialog1.FileName);
    btm1.Destroy;
    resbtm.Destroy;
  end;
end;

procedure TForm1.Sort1Click(Sender: TObject);
begin
  listbox1.Sorted:=true;
  listbox1.Sorted:=false;
end;

procedure TForm1.SelectAll1Click(Sender: TObject);
begin
  listbox1.SelectAll;
end;

end.
