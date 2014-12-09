unit FileBin;

interface

uses
  Windows, SysUtils, Classes;
type
  CFile=class
    filename:string;
    public
      //
      function Open(fname:string;read:boolean):boolean;
      procedure Close;
      function Size:DWORD;
      function GetHandle:THandle;
      procedure WriteString(str:string);
      procedure ReadString(len:integer;var str:string);
      procedure WriteNullTerminatedString(str:string);
      procedure ReadNullTerminatedString(var str:string);
      procedure WriteBool(b:boolean);
      procedure ReadBool(var b:boolean);
      procedure WriteWord(w:Word);
      procedure ReadWord(var w:Word);
      procedure WriteInt(i:integer);
      procedure ReadInt(var i:integer);
      procedure WriteFloat(s:Single);
      procedure ReadFloat(var s:Single);
      procedure WriteChar(c:Char);
      procedure ReadChar(var c:Char);
      procedure WriteDouble(d:Double);
      procedure ReadDouble(var d:Double);
      procedure WriteBuf(const Buffer;size : integer);
      procedure ReadBuf(var Buffer;size : integer);
      constructor Create;
      procedure SkipBytes(bcount : integer);
      //procedure BeginFileMapping();
      //procedure EndFileMapping();
//      procedure Write(Buffer:Untyped;
    private
      //
      Handle, Map: THandle;
      _Read: boolean;
  end;
var
  wr:Cardinal;


implementation

{ CFile }

{procedure CFile.BeginFileMapping;
begin
(*  if _Read then
    CreateFileMapping(Handle, nil, PAGE_READONLY, 0, 0, nil)
  else  *)
  CreateFileMapping(Handle, nil, PAGE_READWRITE, 0, 0, nil);
end; }

procedure CFile.Close;
begin
  CloseHandle(Handle);
  //if Map <> nil then
//    CloseHandle(Map);
//  Map := nil;
end;

constructor CFile.Create;
begin
  //do something
end;

{procedure CFile.EndFileMapping;
begin
  CloseHandle(Map);
  Map := nil;
end;}

function CFile.GetHandle: THandle;
begin
  Result:=Handle;
end;

function CFile.Open(fname: string; read: boolean): boolean;
begin
  if (not FileExists(fname)) and (read) then
  begin
    result:=false;
    exit;
  end;
  if read then
    Handle:=CreateFile(PANSICHAR(FNAME),GENERIC_READ,FILE_SHARE_READ,nil,
      OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0)
  else
    Handle:=CreateFile(PANSICHAR(FNAME),GENERIC_WRITE,FILE_SHARE_WRITE,nil,
      OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
  if Handle=INVALID_HANDLE_VALUE then
    Result:=false
  else
    Result:=true;
    filename:=fname;
  _Read := read;
end;

procedure CFile.ReadBool(var b: boolean);
var
  c:char;
begin
  ReadChar(c);
  b:=false;
  if ord(c)<>0 then b:=true;
end;

procedure CFile.ReadBuf(var Buffer; size: integer);
begin
  ReadFile(Handle,Buffer,size,wr,nil);
end;

procedure CFile.ReadChar(var c: Char);
var
  t:char;
begin
  ReadFile(Handle,t,1,wr,nil);
  c:=t;
end;

procedure CFile.ReadDouble(var d: Double);
var
  t:double;
begin
  ReadFile(Handle,t,8,wr,nil);
  d:=t;
end;

procedure CFile.ReadFloat(var s: Single);
var
  t:single;
begin
  ReadFile(Handle,t,4,wr,nil);
  s:=T;
end;

procedure CFile.ReadInt(var i: integer);
var
  t:integer;
begin
  ReadFile(Handle,t,4,wr,nil);
  i:=t;
end;

procedure CFile.ReadNullTerminatedString(var str: string);
var
  b:char;
begin
  b:=#1;
  str:='';
  while b<>#0 do begin
    ReadChar(b);
    if b<>#0 then str:=str+b;
  end;
end;

procedure CFile.ReadString(len:integer;var str:string);
var
  b:char;
  i:integer;
begin
  b:=#1;
  str:='';
  for i:=1 to len do begin
    ReadChar(b);
    str:=str+b;
  end;
end;

procedure CFile.ReadWord(var w: Word);
var
  t:Word;
begin
  ReadFile(Handle,t,2,wr,nil);
  w:=t;
end;

function CFile.Size: DWORD;
begin
  Result:=GetFileSize(Handle,nil);
end;

procedure CFile.SkipBytes(bcount: integer);
begin
  SetFilePointer(Handle,bcount,Nil,FILE_CURRENT);
end;

procedure CFile.WriteBool(b: boolean);
begin
  if b then WriteChar(#1) else WriteChar(#0);
end;

procedure CFile.WriteBuf(const Buffer; size: integer);
begin
    WriteFile(Handle,Buffer,size,wr,nil);
end;

procedure CFile.WriteChar(c: Char);
var
  t:char;
begin
    t:=c;
    WriteFile(Handle,t,1,wr,nil);
end;

procedure CFile.WriteDouble(d: Double);
var
  t:double;
begin
    t:=d;
    WriteFile(Handle,t,8,wr,nil);
end;

procedure CFile.WriteFloat(s: Single);
var
  t:single;
begin
    t:=s;
    WriteFile(Handle,t,4,wr,nil);
end;

procedure CFile.WriteInt(i: integer);
var
  t:integer;
begin
    t:=i;
    WriteFile(Handle,t,4,wr,nil);
end;

procedure CFile.WriteNullTerminatedString(str: string);
begin
  WriteString(str);
  WriteChar(#0);
end;

procedure CFile.WriteString(str: string);
var
  b:char;
  i:integer;
begin
  for i:=1 to length(str) do begin
    b:=str[i];
    WriteChar(b);
  end;
end;

procedure CFile.WriteWord(w: Word);
var
  t:WORD;
begin
    t:=w;
    WriteFile(Handle,t,2,wr,nil);
end;



end.
