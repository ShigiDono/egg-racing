unit INIUtils;

interface

uses
 Windows,FileBin,SysUtils;

type

 Initialization_params=record
  datapath,levelpath:string;
  width,
  height,
  bpp : integer;
  fullscreen : boolean;
 end;

 CStrings = array of string;


var
 g_Ip: Initialization_params;
 K_INI_FILE: string            = '/Config.ini';
 CURRENT_PATH: string;

function getstring( section, key : string): string;
procedure writestring( section, key, str : pchar);
procedure _writestring( section, key, str : string);
procedure ChangeINIFile(s:string);
procedure restoreINIfile();

implementation

procedure ObtainCurrentPath();
var
 i : integer;
 path : string;
 f:CFile;
 s:string;
begin
 setlength( path, 1024);
 getcurrentdirectory( 1024, pchar( path));
 i := 1024;
 while i>0 do
  begin
   if ( path[i] = #0) then
    setlength(path,i-1);
   dec( i);
  end;
  s:=path+K_INI_FILE;
 if not FileExists(s) then begin
  f:=Cfile.Create;
  f.open(s,false);
  f.Close;
 end;
 CURRENT_PATH := path;
end;

procedure ChangeINIFile(s:string);
begin
  K_INI_fILE:=s;
end;

procedure restoreINIfile();
begin
  K_INI_FILE:= '/Config.ini';
end;

procedure writestring( section, key, str : pchar);
begin
 WritePrivateProfileString(section, key,str,pchar(CURRENT_PATH+K_INI_FILE));
end;
procedure _writestring( section, key, str : string);
begin
 WritePrivateProfileString(pchar(section), pchar(key),pchar(str),pchar(CURRENT_PATH+K_INI_FILE));
end;

function getstring( section, key : string): string;
var
 buffer : array [0..16383] of char;
 str : string;
 h : cardinal;
begin
 Result := '';
 if Section='' then exit;
 if Key='' then exit;
 if FAILED(GetPrivateProfileString(PChar(section), PChar(key), Pchar(str),
           @buffer, 1024, PChar(CURRENT_PATH+K_INI_FILE))) then
  exit;
 Result:=buffer;
end;

initialization
 ObtainCurrentPath();


end.
