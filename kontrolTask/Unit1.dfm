object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 506
  ClientWidth = 743
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 99
    Height = 17
    Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1076#1080#1089#1082#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 56
    Width = 39
    Height = 17
    Caption = #1055#1086#1080#1089#1082
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 128
    Top = 8
    Width = 98
    Height = 17
    Caption = #1054#1087#1086#1079#1085#1072#1085#1085#1072#1103' '#1060#1057
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 248
    Top = 8
    Width = 71
    Height = 17
    Caption = #1056#1072#1079#1084#1077#1088' '#1060#1057
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 336
    Top = 8
    Width = 109
    Height = 17
    Caption = #1050#1086#1083'-'#1074#1086' '#1082#1083#1072#1089#1090#1077#1088#1086#1074
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 472
    Top = 8
    Width = 106
    Height = 17
    Caption = #1056#1072#1079#1084#1077#1088' '#1082#1083#1072#1089#1090#1077#1088#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelFS: TLabel
    Left = 128
    Top = 31
    Width = 4
    Height = 17
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelSizeFS: TLabel
    Left = 246
    Top = 31
    Width = 4
    Height = 17
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelClustersNumber: TLabel
    Left = 336
    Top = 31
    Width = 4
    Height = 17
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelClusterSize: TLabel
    Left = 472
    Top = 31
    Width = 4
    Height = 17
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 8
    Top = 170
    Width = 105
    Height = 15
    AutoSize = False
  end
  object CheckBoxEmptyClusters: TCheckBox
    Left = 600
    Top = 8
    Width = 129
    Height = 33
    Caption = #1055#1091#1089#1090#1099#1077' '#1082#1083#1072#1089#1090#1077#1088#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object EditDiskName: TEdit
    Left = 8
    Top = 32
    Width = 105
    Height = 23
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 15
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
  object EditSearch: TEdit
    Left = 8
    Top = 79
    Width = 105
    Height = 23
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 15
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
  end
  object ButtonStart: TButton
    Left = 8
    Top = 139
    Width = 105
    Height = 25
    Caption = #1047#1072#1087#1091#1089#1082
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = ButtonStartClick
  end
  object ButtonStop: TButton
    Left = 8
    Top = 201
    Width = 105
    Height = 25
    Caption = #1057#1090#1086#1087
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = ButtonStopClick
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 119
    Top = 54
    Width = 610
    Height = 411
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 5
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'ID'
        Width = 96
      end
      item
        Position = 1
        Text = #1050#1083#1072#1089#1090#1077#1088#1099
        Width = 498
      end>
  end
  object ButtonDeleteChosen: TButton
    Left = 440
    Top = 473
    Width = 137
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1099#1073#1088#1072#1085#1085#1086#1077
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    OnClick = ButtonDeleteChosenClick
  end
  object ButtonDeleteAll: TButton
    Left = 583
    Top = 473
    Width = 137
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1105
    Enabled = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    OnClick = ButtonDeleteAllClick
  end
  object Button1: TButton
    Left = 8
    Top = 108
    Width = 105
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 18
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 8
    OnClick = Button1Click
  end
end
