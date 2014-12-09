object Form1: TForm1
  Left = 307
  Top = 195
  Width = 361
  Height = 347
  Caption = 'Launcher'
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
    Top = 168
    Width = 26
    Height = 13
    Caption = 'Maps'
  end
  object Label2: TLabel
    Left = 168
    Top = 168
    Width = 53
    Height = 13
    Caption = 'Description'
  end
  object ListBox1: TListBox
    Left = 0
    Top = 184
    Width = 161
    Height = 97
    ItemHeight = 13
    TabOrder = 0
    OnClick = ListBox1Click
  end
  object Memo1: TMemo
    Left = 168
    Top = 184
    Width = 185
    Height = 97
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object Button1: TButton
    Left = 0
    Top = 288
    Width = 161
    Height = 25
    Caption = 'Save'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 168
    Top = 288
    Width = 185
    Height = 25
    Caption = 'Run'
    TabOrder = 3
    OnClick = Button2Click
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 8
    Width = 353
    Height = 153
    Caption = 'General'
    TabOrder = 4
    object Label3: TLabel
      Left = 0
      Top = 56
      Width = 58
      Height = 13
      Caption = 'Refresh rate'
    end
    object Label4: TLabel
      Left = 0
      Top = 24
      Width = 50
      Height = 13
      Caption = 'Resolution'
    end
    object Label5: TLabel
      Left = 8
      Top = 128
      Width = 61
      Height = 13
      Caption = 'ScreenShots'
    end
    object CheckBox1: TCheckBox
      Left = 104
      Top = 88
      Width = 97
      Height = 17
      Caption = 'Antialiasing'
      TabOrder = 0
    end
    object ComboBox1: TComboBox
      Left = 64
      Top = 16
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 1
      Text = 'ComboBox1'
    end
    object ComboBox2: TComboBox
      Left = 64
      Top = 48
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 2
      Text = 'ComboBox2'
    end
    object CheckBox2: TCheckBox
      Left = 0
      Top = 88
      Width = 97
      Height = 17
      Caption = 'Windowed'
      TabOrder = 3
    end
    object Edit1: TEdit
      Left = 96
      Top = 120
      Width = 121
      Height = 21
      TabOrder = 4
    end
    object Edit2: TEdit
      Left = 224
      Top = 120
      Width = 121
      Height = 21
      TabOrder = 5
    end
  end
end
