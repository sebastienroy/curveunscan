; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDensitoProPage
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "settingsmanagement.h"
LastPage=0

ClassCount=6

ResourceCount=11
Resource1=IDD_PROPPAGE_EXPORT (English (U.S.))
Class1=CLanguageProPage
Class2=CCurveProPage
Resource2=IDD_PROPPAGE_DENSITO (English (U.S.))
Class3=CColorChooseDialog
Resource3=IDD_PROPPAGE_EXPORT
Resource4=IDD_PROPPAGE_LANGUAGE (English (U.S.))
Resource5=IDD_PROPPAGE_PROMPT (English (U.S.))
Resource6=IDD_PROPPAGE_CURVE
Class4=CPromptProPage
Resource7=IDD_PROPPAGE_LANGUAGE
Resource8=IDD_DIALOG_COLORCHOOSE (English (U.S.))
Class5=CExportProPage
Resource9=IDD_PROPPAGE_CURVE (English (U.S.))
Class6=CDensitoProPage
Resource10=IDD_PROPPAGE_PROMPT
Resource11=IDD_PROPPAGE_DENSITO

[DLG:IDD_PROPPAGE_LANGUAGE (English (U.S.))]
Type=1
Class=CLanguageProPage
ControlCount=4
Control1=IDC_LANG_COMBO,combobox,1344340227
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_CURVE (English (U.S.))]
Type=1
Class=CCurveProPage
ControlCount=20
Control1=IDC_STATIC,static,1342177292
Control2=IDC_STATIC,button,1342177287
Control3=IDC_RADIO_SETTING_SMART,button,1342308361
Control4=IDC_RADIO_SETTING_SIMPLE,button,1342177289
Control5=IDC_STATIC,static,1342308864
Control6=IDC_EDIT_SETTING_THICKWIDTH,edit,1350631552
Control7=IDC_SPIN_THICKRANGE,msctls_updown32,1342177462
Control8=IDC_STATIC,button,1342177287
Control9=IDC_BUTTON_SETTING_BLACKCOLOR,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_RADIO_SETTING_TOPFOLLOW,button,1342308361
Control12=IDC_RADIO_SETTING_BOTTOMFOLLOW,button,1342177289
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_RADIO_SETTING_DASHED,button,1342373897
Control16=IDC_RADIO_SETTING_NOT_DASHED,button,1342177289
Control17=IDC_STATIC,static,1342308864
Control18=IDC_EDIT_SETTING_DASHMAX,edit,1350631552
Control19=IDC_SPIN_DASHMAX,msctls_updown32,1342177462
Control20=IDC_BUTTON_SETTING_CURVEDEFAULTS,button,1342242816

[CLS:CLanguageProPage]
Type=0
HeaderFile=LanguageProPage.h
ImplementationFile=LanguageProPage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CLanguageProPage

[CLS:CCurveProPage]
Type=0
HeaderFile=CurveProPage.h
ImplementationFile=CurveProPage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CCurveProPage

[CLS:CColorChooseDialog]
Type=0
HeaderFile=ColorChooseDialog.h
ImplementationFile=ColorChooseDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SLIDER_REDCOMP
VirtualFilter=dWC

[DLG:IDD_DIALOG_COLORCHOOSE (English (U.S.))]
Type=1
Class=?
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SLIDER_REDCOMP,msctls_trackbar32,1342177306
Control4=IDC_SLIDER_GREENCOMP,msctls_trackbar32,1342177306
Control5=IDC_SLIDER_BLUECOMP,msctls_trackbar32,1342177306
Control6=IDC_BUTTON_COLOR,button,1476460544
Control7=IDC_EDIT_REDSETTING,edit,1350639744
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_GREENSETTING,edit,1350639744
Control11=IDC_EDIT_BLUESETTING,edit,1350639744
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_CURVE]
Type=1
Class=CCurveProPage
ControlCount=20
Control1=IDC_STATIC,static,1342177292
Control2=IDC_STATIC,button,1342177287
Control3=IDC_RADIO_SETTING_SMART,button,1342308361
Control4=IDC_RADIO_SETTING_SIMPLE,button,1342177289
Control5=IDC_STATIC,static,1342308864
Control6=IDC_EDIT_SETTING_THICKWIDTH,edit,1350631552
Control7=IDC_SPIN_THICKRANGE,msctls_updown32,1342177462
Control8=IDC_STATIC,button,1342177287
Control9=IDC_BUTTON_SETTING_BLACKCOLOR,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_RADIO_SETTING_TOPFOLLOW,button,1342308361
Control12=IDC_RADIO_SETTING_BOTTOMFOLLOW,button,1342177289
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_RADIO_SETTING_DASHED,button,1342373897
Control16=IDC_RADIO_SETTING_NOT_DASHED,button,1342177289
Control17=IDC_STATIC,static,1342308864
Control18=IDC_EDIT_SETTING_DASHMAX,edit,1350631552
Control19=IDC_SPIN_DASHMAX,msctls_updown32,1342177462
Control20=IDC_BUTTON_SETTING_CURVEDEFAULTS,button,1342242816

[DLG:IDD_PROPPAGE_LANGUAGE]
Type=1
Class=CLanguageProPage
ControlCount=4
Control1=IDC_LANG_COMBO,combobox,1344340227
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_PROMPT (English (U.S.))]
Type=1
Class=CPromptProPage
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO_START_OPENGRAPHIC,button,1342308361
Control3=IDC_RADIO_START_IMPORTSCANNER,button,1342177289
Control4=IDC_RADIO_START_NONE,button,1342177289
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO_EXPORT_NOPROMPT,button,1342308361
Control7=IDC_RADIO_EXPORT_AUTOPROMPT,button,1342242825

[CLS:CPromptProPage]
Type=0
HeaderFile=PromptProPage.h
ImplementationFile=PromptProPage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPromptProPage

[DLG:IDD_PROPPAGE_PROMPT]
Type=1
Class=CPromptProPage
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO_START_OPENGRAPHIC,button,1342308361
Control3=IDC_RADIO_START_IMPORTSCANNER,button,1342177289
Control4=IDC_RADIO_START_NONE,button,1342177289
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO_EXPORT_NOPROMPT,button,1342308361
Control7=IDC_RADIO_EXPORT_AUTOPROMPT,button,1342242825

[DLG:IDD_PROPPAGE_EXPORT (English (U.S.))]
Type=1
Class=CExportProPage
ControlCount=10
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO_SETT_SEP_TAB,button,1342373897
Control3=IDC_RADIO_SETT_SEP_SEMIC,button,1342177289
Control4=IDC_RADIO_SETT_SEP_COMMA,button,1342177289
Control5=IDC_RADIO_SETT_SEP_SPACE,button,1342177289
Control6=IDC_RADIO_SETT_SEP_OTHER,button,1342177289
Control7=IDC_EDIT_SETT_SEP_OTHER,edit,1350631552
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308864
Control10=IDC_EDIT_SETT_FILEEXTENSION,edit,1350631552

[CLS:CExportProPage]
Type=0
HeaderFile=ExportProPage.h
ImplementationFile=ExportProPage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CExportProPage

[DLG:IDD_PROPPAGE_EXPORT]
Type=1
Class=CExportProPage
ControlCount=10
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO_SETT_SEP_TAB,button,1342373897
Control3=IDC_RADIO_SETT_SEP_SEMIC,button,1342177289
Control4=IDC_RADIO_SETT_SEP_COMMA,button,1342177289
Control5=IDC_RADIO_SETT_SEP_SPACE,button,1342177289
Control6=IDC_RADIO_SETT_SEP_OTHER,button,1342177289
Control7=IDC_EDIT_SETT_SEP_OTHER,edit,1350631552
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308864
Control10=IDC_EDIT_SETT_FILEEXTENSION,edit,1350631552

[DLG:IDD_PROPPAGE_DENSITO (English (U.S.))]
Type=1
Class=CDensitoProPage
ControlCount=8
Control1=IDC_STATIC,button,1342177287
Control2=IDC_SETTINGS_TOPCOLOR,button,1342242816
Control3=IDC_SETTINGS_BOTTOMCOLOR,button,1342242816
Control4=IDC_SETTINGS_COLORSCALE,button,1476460544
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SETTINGS_TOPVALUE,edit,1350631552
Control8=IDC_SETTINGS_BOTTOMVALUE,edit,1350631552

[CLS:CDensitoProPage]
Type=0
HeaderFile=DensitoProPage.h
ImplementationFile=DensitoProPage.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CDensitoProPage

[DLG:IDD_PROPPAGE_DENSITO]
Type=1
Class=?
ControlCount=8
Control1=IDC_STATIC,button,1342177287
Control2=IDC_SETTINGS_TOPCOLOR,button,1342242816
Control3=IDC_SETTINGS_BOTTOMCOLOR,button,1342242816
Control4=IDC_SETTINGS_COLORSCALE,button,1476460544
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SETTINGS_TOPVALUE,edit,1350631552
Control8=IDC_SETTINGS_BOTTOMVALUE,edit,1350631552
