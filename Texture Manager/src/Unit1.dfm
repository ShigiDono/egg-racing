object Form1: TForm1
  Left = 302
  Top = 389
  Width = 201
  Height = 313
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Texture manager'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 24
    Width = 56
    Height = 13
    Caption = 'Diffuse map'
  end
  object Label2: TLabel
    Left = 108
    Top = 100
    Width = 7
    Height = 13
    Caption = 'X'
  end
  object Shape1: TShape
    Left = 176
    Top = 48
    Width = 17
    Height = 17
    OnMouseDown = Shape1MouseDown
  end
  object Label4: TLabel
    Left = 108
    Top = 236
    Width = 7
    Height = 13
    Caption = 'X'
  end
  object Shape2: TShape
    Left = 176
    Top = 184
    Width = 17
    Height = 17
    OnMouseDown = Shape2MouseDown
  end
  object Label5: TLabel
    Left = 0
    Top = 4
    Width = 28
    Height = 13
    Caption = 'Name'
  end
  object Edit1: TEdit
    Left = 64
    Top = 24
    Width = 129
    Height = 21
    TabOrder = 1
  end
  object CheckBox1: TCheckBox
    Left = 0
    Top = 72
    Width = 193
    Height = 17
    Caption = 'Tiling enable'
    TabOrder = 3
  end
  object SpinEdit1: TSpinEdit
    Left = 32
    Top = 96
    Width = 73
    Height = 22
    MaxValue = 512
    MinValue = 1
    TabOrder = 4
    Value = 32
    OnChange = SpinEdit1Change
  end
  object SpinEdit2: TSpinEdit
    Left = 120
    Top = 96
    Width = 73
    Height = 22
    MaxValue = 512
    MinValue = 1
    TabOrder = 5
    Value = 32
    OnChange = SpinEdit2Change
  end
  object CheckBox2: TCheckBox
    Left = 0
    Top = 48
    Width = 169
    Height = 17
    Caption = 'Color key'
    TabOrder = 2
  end
  object Edit2: TEdit
    Left = 0
    Top = 152
    Width = 193
    Height = 21
    TabOrder = 8
    OnChange = Edit2Change
  end
  object CheckBox3: TCheckBox
    Left = 0
    Top = 208
    Width = 193
    Height = 17
    Caption = 'Tiling enable'
    TabOrder = 10
    OnClick = CheckBox3Click
  end
  object SpinEdit3: TSpinEdit
    Left = 32
    Top = 232
    Width = 73
    Height = 22
    MaxValue = 512
    MinValue = 1
    TabOrder = 11
    Value = 32
    OnChange = SpinEdit3Change
  end
  object SpinEdit4: TSpinEdit
    Left = 120
    Top = 232
    Width = 73
    Height = 22
    MaxValue = 512
    MinValue = 1
    TabOrder = 12
    Value = 32
    OnChange = SpinEdit4Change
  end
  object CheckBox4: TCheckBox
    Left = 0
    Top = 184
    Width = 169
    Height = 17
    Caption = 'Color key'
    TabOrder = 9
    OnClick = CheckBox4Click
  end
  object Button1: TButton
    Left = 0
    Top = 256
    Width = 97
    Height = 25
    Caption = 'Save'
    TabOrder = 13
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 96
    Top = 256
    Width = 97
    Height = 25
    Caption = 'Load'
    TabOrder = 14
    OnClick = Button2Click
  end
  object CheckBox5: TCheckBox
    Left = 0
    Top = 128
    Width = 73
    Height = 17
    Caption = 'Glow Map'
    TabOrder = 6
  end
  object CheckBox6: TCheckBox
    Left = 96
    Top = 128
    Width = 97
    Height = 17
    Caption = 'Same as diffuse'
    TabOrder = 7
    OnClick = CheckBox6Click
  end
  object Edit3: TEdit
    Left = 64
    Top = 0
    Width = 129
    Height = 21
    TabOrder = 0
  end
  object ColorDialog1: TColorDialog
    Left = 96
    Top = 80
  end
  object OpenDialog1: TOpenDialog
    Filter = 'PIE TexTure|*.ptt'
    Left = 64
    Top = 96
  end
  object SaveDialog1: TSaveDialog
    Filter = 'PIE TexTure|*.ptt'
    Left = 80
    Top = 40
  end
end
