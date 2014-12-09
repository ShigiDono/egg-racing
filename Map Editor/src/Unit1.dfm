object Form1: TForm1
  Left = 278
  Top = 112
  BorderStyle = bsSingle
  Caption = '[PIE] Egg Racing Map Editor'
  ClientHeight = 564
  ClientWidth = 713
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 713
    Height = 545
    ActivePage = TabSheet4
    Enabled = False
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Relief'
      object Label1: TLabel
        Left = 584
        Top = 0
        Width = 41
        Height = 16
        Caption = 'Tools'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Shape2: TShape
        Left = 536
        Top = 384
        Width = 128
        Height = 128
        Brush.Color = clBlack
        Pen.Color = clGreen
      end
      object Shape3: TShape
        Left = 536
        Top = 384
        Width = 128
        Height = 128
        Brush.Style = bsClear
        Pen.Color = clLime
        Pen.Style = psDot
      end
      object DXDraw1: TDXDraw
        Left = 0
        Top = 0
        Width = 512
        Height = 512
        Cursor = crCross
        AutoInitialize = True
        AutoSize = True
        Color = clBtnFace
        Display.BitCount = 32
        Display.FixedBitCount = True
        Display.FixedRatio = True
        Display.FixedSize = False
        Options = [doAllowReboot, doWaitVBlank, doCenter, doDirectX7Mode, doHardware, doSelectDriver]
        SurfaceHeight = 512
        SurfaceWidth = 512
        TabOrder = 0
        OnMouseDown = DXDraw1MouseDown
        OnMouseMove = DXDraw1MouseMove
        OnMouseUp = DXDraw1MouseUp
      end
      object PageControl2: TPageControl
        Left = 520
        Top = 16
        Width = 177
        Height = 297
        ActivePage = TabSheet7
        MultiLine = True
        TabOrder = 1
        TabPosition = tpLeft
        object TabSheet5: TTabSheet
          Caption = 'Brush'
          object Label2: TLabel
            Left = 8
            Top = 16
            Width = 20
            Height = 13
            Caption = 'Size'
          end
          object Label3: TLabel
            Left = 8
            Top = 40
            Width = 24
            Height = 13
            Caption = 'Color'
          end
          object Shape1: TShape
            Left = 40
            Top = 64
            Width = 105
            Height = 25
            Brush.Color = clBlack
          end
          object SpinEdit1: TSpinEdit
            Left = 40
            Top = 8
            Width = 105
            Height = 22
            MaxValue = 512
            MinValue = 1
            TabOrder = 0
            Value = 2
          end
          object SpinEdit2: TSpinEdit
            Left = 40
            Top = 32
            Width = 105
            Height = 22
            MaxValue = 255
            MinValue = 0
            TabOrder = 1
            Value = 0
            OnChange = SpinEdit2Change
          end
        end
        object TabSheet6: TTabSheet
          Caption = 'Lift'
          ImageIndex = 1
          object Label4: TLabel
            Left = 8
            Top = 16
            Width = 20
            Height = 13
            Caption = 'Size'
          end
          object SpinEdit3: TSpinEdit
            Left = 40
            Top = 8
            Width = 105
            Height = 22
            MaxValue = 512
            MinValue = 1
            TabOrder = 0
            Value = 2
          end
          object CheckBox1: TCheckBox
            Left = 40
            Top = 40
            Width = 97
            Height = 17
            Caption = 'Smooth'
            TabOrder = 1
          end
        end
        object TabSheet7: TTabSheet
          Caption = 'Modifiers'
          ImageIndex = 2
          object Gauge1: TGauge
            Left = 8
            Top = 88
            Width = 137
            Height = 17
            Progress = 0
          end
          object Button1: TButton
            Left = 8
            Top = 8
            Width = 137
            Height = 25
            Caption = 'Filter'
            TabOrder = 0
          end
          object Button2: TButton
            Left = 8
            Top = 32
            Width = 137
            Height = 25
            Caption = 'Load'
            TabOrder = 1
            OnClick = Button2Click
          end
          object Button3: TButton
            Left = 8
            Top = 56
            Width = 137
            Height = 25
            Caption = 'Sqrt'
            TabOrder = 2
            OnClick = Button3Click
          end
          object Button11: TButton
            Left = 8
            Top = 272
            Width = 137
            Height = 17
            Caption = 'Export height map'
            TabOrder = 3
            OnClick = Button11Click
          end
          object GroupBox2: TGroupBox
            Left = 8
            Top = 112
            Width = 137
            Height = 153
            Caption = 'Fractal'
            TabOrder = 4
            object Label15: TLabel
              Left = 8
              Top = 24
              Width = 27
              Height = 13
              Caption = 'Scale'
            end
            object Label16: TLabel
              Left = 8
              Top = 48
              Width = 43
              Height = 13
              Caption = 'Iterations'
            end
            object Label17: TLabel
              Left = 8
              Top = 72
              Width = 49
              Height = 13
              Caption = 'Min height'
            end
            object Label18: TLabel
              Left = 8
              Top = 96
              Width = 52
              Height = 13
              Caption = 'Max height'
            end
            object Button26: TButton
              Left = 8
              Top = 120
              Width = 121
              Height = 25
              Caption = 'Generate'
              TabOrder = 0
              OnClick = Button26Click
            end
            object SpinEdit6: TSpinEdit
              Left = 72
              Top = 16
              Width = 57
              Height = 22
              MaxValue = 100000
              MinValue = 0
              TabOrder = 1
              Value = 40
            end
            object SpinEdit7: TSpinEdit
              Left = 72
              Top = 40
              Width = 57
              Height = 22
              MaxValue = 100000
              MinValue = 0
              TabOrder = 2
              Value = 3
            end
            object SpinEdit8: TSpinEdit
              Left = 72
              Top = 88
              Width = 57
              Height = 22
              MaxValue = 255
              MinValue = 0
              TabOrder = 3
              Value = 255
            end
            object SpinEdit9: TSpinEdit
              Left = 72
              Top = 64
              Width = 57
              Height = 22
              MaxValue = 255
              MinValue = 0
              TabOrder = 4
              Value = 0
            end
          end
        end
      end
      object Button4: TButton
        Left = 536
        Top = 352
        Width = 25
        Height = 25
        Caption = '+'
        TabOrder = 2
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 560
        Top = 352
        Width = 25
        Height = 25
        Caption = '-'
        TabOrder = 3
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 608
        Top = 328
        Width = 25
        Height = 25
        Caption = '/\'
        TabOrder = 4
        OnClick = Button6Click
      end
      object Button7: TButton
        Left = 584
        Top = 352
        Width = 25
        Height = 25
        Caption = '<'
        TabOrder = 5
        OnClick = Button7Click
      end
      object Button8: TButton
        Left = 608
        Top = 352
        Width = 25
        Height = 25
        Caption = '\/'
        TabOrder = 6
        OnClick = Button8Click
      end
      object Button9: TButton
        Left = 632
        Top = 352
        Width = 25
        Height = 25
        Caption = '>'
        TabOrder = 7
        OnClick = Button9Click
      end
      object Button10: TButton
        Left = 656
        Top = 328
        Width = 33
        Height = 49
        Caption = 'Reset'
        TabOrder = 8
        OnClick = Button10Click
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Texture'
      ImageIndex = 1
      object Label5: TLabel
        Left = 536
        Top = 64
        Width = 20
        Height = 13
        Caption = 'Size'
      end
      object Label6: TLabel
        Left = 536
        Top = 96
        Width = 34
        Height = 13
        Caption = 'Tile set'
      end
      object Label7: TLabel
        Left = 520
        Top = 8
        Width = 185
        Height = 33
        Alignment = taCenter
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Shape4: TShape
        Left = 552
        Top = 272
        Width = 128
        Height = 128
        Brush.Color = clBlack
        Pen.Color = clGreen
      end
      object Shape5: TShape
        Left = 552
        Top = 272
        Width = 128
        Height = 128
        Brush.Style = bsClear
        Pen.Color = clLime
        Pen.Style = psDot
      end
      object DXDraw2: TDXDraw
        Left = 0
        Top = 0
        Width = 512
        Height = 512
        Cursor = crCross
        AutoInitialize = True
        AutoSize = True
        Color = clBtnFace
        Display.FixedBitCount = True
        Display.FixedRatio = True
        Display.FixedSize = False
        Options = [doAllowReboot, doWaitVBlank, doCenter, doDirectX7Mode, doHardware, doSelectDriver]
        SurfaceHeight = 512
        SurfaceWidth = 512
        TabOrder = 0
        OnMouseDown = DXDraw2MouseDown
        OnMouseMove = DXDraw2MouseMove
        OnMouseUp = DXDraw2MouseUp
      end
      object SpinEdit4: TSpinEdit
        Left = 576
        Top = 56
        Width = 105
        Height = 22
        MaxValue = 150
        MinValue = 1
        TabOrder = 1
        Value = 2
      end
      object ComboBox1: TComboBox
        Left = 576
        Top = 88
        Width = 105
        Height = 21
        ItemHeight = 0
        TabOrder = 2
      end
      object Button12: TButton
        Left = 536
        Top = 144
        Width = 25
        Height = 25
        Caption = '+'
        TabOrder = 3
        OnClick = Button4Click
      end
      object Button13: TButton
        Left = 560
        Top = 144
        Width = 25
        Height = 25
        Caption = '-'
        TabOrder = 4
        OnClick = Button5Click
      end
      object Button14: TButton
        Left = 584
        Top = 168
        Width = 25
        Height = 25
        Caption = '<'
        TabOrder = 5
        OnClick = Button7Click
      end
      object Button15: TButton
        Left = 608
        Top = 168
        Width = 25
        Height = 25
        Caption = '\/'
        TabOrder = 6
        OnClick = Button8Click
      end
      object Button16: TButton
        Left = 608
        Top = 144
        Width = 25
        Height = 25
        Caption = '/\'
        TabOrder = 7
        OnClick = Button6Click
      end
      object Button17: TButton
        Left = 632
        Top = 168
        Width = 25
        Height = 25
        Caption = '>'
        TabOrder = 8
        OnClick = Button9Click
      end
      object Button18: TButton
        Left = 664
        Top = 144
        Width = 33
        Height = 49
        Caption = 'Reset'
        TabOrder = 9
        OnClick = Button10Click
      end
      object CheckBox2: TCheckBox
        Left = 528
        Top = 112
        Width = 169
        Height = 17
        Caption = 'Enable alpha(not reccomended)'
        TabOrder = 10
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Scenery'
      ImageIndex = 2
      object DXDraw3: TDXDraw
        Left = 0
        Top = 0
        Width = 512
        Height = 512
        Cursor = crCross
        AutoInitialize = True
        AutoSize = True
        Color = clBtnFace
        Display.FixedBitCount = True
        Display.FixedRatio = True
        Display.FixedSize = False
        Options = [doAllowReboot, doWaitVBlank, doCenter, doDirectX7Mode, doHardware, doSelectDriver]
        SurfaceHeight = 512
        SurfaceWidth = 512
        TabOrder = 0
        OnMouseDown = DXDraw3MouseDown
        OnMouseMove = DXDraw3MouseMove
        OnMouseUp = DXDraw3MouseUp
      end
      object Panel1: TPanel
        Left = 520
        Top = 0
        Width = 185
        Height = 513
        TabOrder = 1
        object Shape7: TShape
          Left = 40
          Top = 344
          Width = 128
          Height = 128
          Brush.Style = bsClear
          Pen.Color = clLime
          Pen.Style = psDot
        end
        object Shape8: TShape
          Left = 40
          Top = 344
          Width = 128
          Height = 128
          Brush.Color = clBlack
          Pen.Color = clLime
          Pen.Style = psDot
        end
        object Label12: TLabel
          Left = 16
          Top = 80
          Width = 66
          Height = 13
          Caption = 'Picking radius'
        end
        object Label13: TLabel
          Left = 40
          Top = 16
          Width = 87
          Height = 13
          Caption = 'Current decoration'
        end
        object Label14: TLabel
          Left = 16
          Top = 128
          Width = 63
          Height = 13
          Caption = 'Fixed rotation'
        end
        object Button23: TButton
          Left = 88
          Top = 200
          Width = 25
          Height = 25
          Caption = '\/'
          TabOrder = 0
          OnClick = Button8Click
        end
        object ComboBox4: TComboBox
          Left = 16
          Top = 40
          Width = 145
          Height = 21
          ItemHeight = 13
          TabOrder = 1
        end
        object Button19: TButton
          Left = 40
          Top = 176
          Width = 25
          Height = 25
          Caption = '-'
          TabOrder = 2
          OnClick = Button5Click
        end
        object Button20: TButton
          Left = 16
          Top = 176
          Width = 25
          Height = 25
          Caption = '+'
          TabOrder = 3
          OnClick = Button4Click
        end
        object Button21: TButton
          Left = 88
          Top = 176
          Width = 25
          Height = 25
          Caption = '/\'
          TabOrder = 4
          OnClick = Button6Click
        end
        object Button22: TButton
          Left = 64
          Top = 200
          Width = 25
          Height = 25
          Caption = '<'
          TabOrder = 5
          OnClick = Button7Click
        end
        object Button24: TButton
          Left = 112
          Top = 200
          Width = 25
          Height = 25
          Caption = '>'
          TabOrder = 6
          OnClick = Button9Click
        end
        object Button25: TButton
          Left = 144
          Top = 176
          Width = 33
          Height = 49
          Caption = 'Reset'
          TabOrder = 7
          OnClick = Button10Click
        end
        object SpinEdit5: TSpinEdit
          Left = 96
          Top = 72
          Width = 65
          Height = 22
          MaxValue = 200
          MinValue = 0
          TabOrder = 8
          Value = 5
        end
        object CheckBox3: TCheckBox
          Left = 16
          Top = 104
          Width = 97
          Height = 17
          Caption = 'Random rotation'
          Checked = True
          State = cbChecked
          TabOrder = 9
        end
        object Edit5: TEdit
          Left = 88
          Top = 120
          Width = 73
          Height = 21
          TabOrder = 10
          Text = '0,0'
        end
        object CheckBox4: TCheckBox
          Left = 16
          Top = 144
          Width = 113
          Height = 17
          Caption = 'Normal orientation'
          Checked = True
          State = cbChecked
          TabOrder = 11
        end
        object Button27: TButton
          Left = 40
          Top = 248
          Width = 75
          Height = 25
          Caption = 'Clear AI'
          TabOrder = 12
          OnClick = Button27Click
        end
        object CheckBox5: TCheckBox
          Left = 8
          Top = 232
          Width = 161
          Height = 17
          Caption = 'Creating AI checkpoints'
          TabOrder = 13
        end
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'Properties'
      ImageIndex = 3
      object GroupBox1: TGroupBox
        Left = 0
        Top = 120
        Width = 249
        Height = 73
        Caption = 'Enviroment'
        TabOrder = 0
        object Label10: TLabel
          Left = 8
          Top = 24
          Width = 66
          Height = 13
          Caption = 'Fog Start/end'
        end
        object Label11: TLabel
          Left = 8
          Top = 48
          Width = 44
          Height = 13
          Caption = 'Fog color'
        end
        object Shape6: TShape
          Left = 112
          Top = 40
          Width = 25
          Height = 25
          OnMouseUp = Shape6MouseUp
        end
        object Edit3: TEdit
          Left = 112
          Top = 16
          Width = 65
          Height = 21
          TabOrder = 0
          Text = '0,0'
        end
        object Edit4: TEdit
          Left = 176
          Top = 16
          Width = 65
          Height = 21
          TabOrder = 1
          Text = '1,0'
        end
      end
      object GroupBox3: TGroupBox
        Left = 0
        Top = 0
        Width = 337
        Height = 97
        Caption = 'Main'
        TabOrder = 1
        object Label8: TLabel
          Left = 8
          Top = 24
          Width = 28
          Height = 13
          Caption = 'Name'
        end
        object Label9: TLabel
          Left = 8
          Top = 48
          Width = 64
          Height = 13
          Caption = 'Width/Height'
        end
        object Label19: TLabel
          Left = 8
          Top = 72
          Width = 94
          Height = 13
          Caption = 'Hor. and Vert. scale'
        end
        object ComboBox3: TComboBox
          Left = 120
          Top = 40
          Width = 97
          Height = 21
          ItemHeight = 13
          ItemIndex = 4
          TabOrder = 0
          Text = '256'
          OnChange = ComboBox3Change
          Items.Strings = (
            '16'
            '32'
            '64'
            '128'
            '256'
            '512')
        end
        object Edit2: TEdit
          Left = 120
          Top = 16
          Width = 193
          Height = 21
          TabOrder = 1
          OnChange = Edit2Change
        end
        object ComboBox2: TComboBox
          Left = 216
          Top = 40
          Width = 97
          Height = 21
          ItemHeight = 13
          ItemIndex = 4
          TabOrder = 2
          Text = '256'
          OnChange = ComboBox2Change
          Items.Strings = (
            '16'
            '32'
            '64'
            '128'
            '256'
            '512')
        end
        object Edit6: TEdit
          Left = 120
          Top = 64
          Width = 97
          Height = 21
          TabOrder = 3
          Text = '2,0'
        end
        object Edit7: TEdit
          Left = 216
          Top = 64
          Width = 97
          Height = 21
          TabOrder = 4
          Text = '0,1'
        end
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 545
    Width = 713
    Height = 19
    Panels = <
      item
        Width = 500
      end
      item
        Bevel = pbRaised
        Text = 'PIE engine [Egg racing]'
        Width = 100
      end>
  end
  object MainMenu1: TMainMenu
    Left = 248
    object File1: TMenuItem
      Caption = '&File'
      object New1: TMenuItem
        Caption = 'New'
        OnClick = New1Click
      end
      object Open1: TMenuItem
        Caption = 'Open'
        OnClick = Open1Click
      end
      object Save1: TMenuItem
        Caption = 'Save'
        OnClick = Save1Click
      end
      object Export1: TMenuItem
        Caption = 'Export'
        OnClick = Export1Click
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
      end
    end
    object View1: TMenuItem
      Caption = 'View'
      object Redraw1: TMenuItem
        Caption = 'Redraw'
        ShortCut = 16466
        OnClick = Redraw1Click
      end
    end
    object Edit1: TMenuItem
      Caption = '&Edit'
    end
    object N1: TMenuItem
      Caption = '&?'
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 308
    Top = 24
  end
  object Timer1: TTimer
    Interval = 10000
    OnTimer = Timer1Timer
    Left = 220
  end
  object SaveDialog1: TSaveDialog
    Left = 276
    Top = 24
  end
  object SaveDialog2: TSaveDialog
    Filter = '~Pie map|*.~pm'
    Left = 276
  end
  object OpenDialog2: TOpenDialog
    Filter = '~Pie map|*.~pm'
    Left = 304
  end
  object ColorDialog1: TColorDialog
    Left = 368
    Top = 8
  end
  object SaveDialog3: TSaveDialog
    Filter = 'Pie map|*.pm'
    Left = 332
  end
end
