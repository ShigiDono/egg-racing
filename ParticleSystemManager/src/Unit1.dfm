object Form1: TForm1
  Left = 442
  Top = 134
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Particle System Manager'
  ClientHeight = 241
  ClientWidth = 249
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 224
    Width = 152
    Height = 13
    Caption = 'P.S.M. Particle System Manager'
  end
  object ListBox1: TListBox
    Left = 0
    Top = 0
    Width = 169
    Height = 193
    ItemHeight = 13
    TabOrder = 0
  end
  object Button1: TButton
    Left = 168
    Top = 0
    Width = 81
    Height = 41
    Caption = '_Add_'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 168
    Top = 40
    Width = 81
    Height = 41
    Caption = '_Edit_'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 168
    Top = 80
    Width = 81
    Height = 41
    Caption = '_Remove_'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 168
    Top = 120
    Width = 81
    Height = 41
    Caption = 'Dublicate'
    TabOrder = 4
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 0
    Top = 192
    Width = 169
    Height = 33
    Caption = 'Clear'
    TabOrder = 5
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 168
    Top = 160
    Width = 81
    Height = 41
    Caption = 'Save'
    TabOrder = 6
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 168
    Top = 200
    Width = 81
    Height = 41
    Caption = 'Load'
    TabOrder = 7
    OnClick = Button7Click
  end
  object SaveDialog1: TSaveDialog
    Filter = 'Pie particle system|*.pps'
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Pie particle system|*.pps'
    Left = 32
  end
end
