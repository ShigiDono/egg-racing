object Form1: TForm1
  Left = 364
  Top = 145
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Tileset Editor'
  ClientHeight = 372
  ClientWidth = 409
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnPaint = Timer1Timer
  PixelsPerInch = 96
  TextHeight = 13
  object DXDraw1: TDXDraw
    Left = 0
    Top = 0
    Width = 217
    Height = 217
    AutoInitialize = True
    AutoSize = True
    Color = clBtnFace
    Display.FixedBitCount = True
    Display.FixedRatio = True
    Display.FixedSize = False
    Options = [doAllowReboot, doWaitVBlank, doCenter, doDirectX7Mode, doHardware, doSelectDriver]
    SurfaceHeight = 217
    SurfaceWidth = 217
    TabOrder = 0
    OnMouseDown = DXDraw1MouseDown
    OnMouseMove = DXDraw1MouseMove
  end
  object Panel1: TPanel
    Left = 224
    Top = 0
    Width = 185
    Height = 353
    TabOrder = 1
    object ListBox1: TListBox
      Left = 8
      Top = 8
      Width = 169
      Height = 225
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListBox1Click
    end
    object Button1: TButton
      Left = 8
      Top = 240
      Width = 81
      Height = 25
      Caption = 'Add new'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 96
      Top = 240
      Width = 81
      Height = 25
      Caption = 'Remove'
      TabOrder = 2
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 8
      Top = 264
      Width = 41
      Height = 25
      Caption = 'Edit'
      TabOrder = 3
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 8
      Top = 296
      Width = 57
      Height = 25
      Caption = 'New'
      TabOrder = 4
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 64
      Top = 296
      Width = 57
      Height = 25
      Caption = 'Save'
      TabOrder = 5
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 120
      Top = 296
      Width = 57
      Height = 25
      Caption = 'Export'
      TabOrder = 6
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = 8
      Top = 320
      Width = 57
      Height = 25
      Caption = 'Properties'
      TabOrder = 7
      OnClick = Button7Click
    end
    object Button8: TButton
      Left = 64
      Top = 320
      Width = 57
      Height = 25
      Caption = 'Load'
      TabOrder = 8
      OnClick = Button8Click
    end
    object Button9: TButton
      Left = 120
      Top = 320
      Width = 57
      Height = 25
      Caption = 'Import'
      TabOrder = 9
      OnClick = Button9Click
    end
    object SpinEdit1: TSpinEdit
      Left = 56
      Top = 267
      Width = 33
      Height = 22
      MaxValue = 0
      MinValue = 0
      TabOrder = 10
      Value = 0
    end
    object SpinEdit2: TSpinEdit
      Left = 96
      Top = 267
      Width = 33
      Height = 22
      MaxValue = 0
      MinValue = 0
      TabOrder = 11
      Value = 0
    end
    object Button10: TButton
      Left = 136
      Top = 264
      Width = 41
      Height = 25
      Caption = 'Swap'
      TabOrder = 12
      OnClick = Button10Click
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 353
    Width = 409
    Height = 19
    Panels = <
      item
        Bevel = pbRaised
        Width = 100
      end>
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 1
    OnTimer = Timer1Timer
    Left = 40
    Top = 8
  end
  object SaveDialog1: TSaveDialog
    Left = 48
    Top = 136
  end
  object OpenDialog1: TOpenDialog
    Left = 80
    Top = 136
  end
end
