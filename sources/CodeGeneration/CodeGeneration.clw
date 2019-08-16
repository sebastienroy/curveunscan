; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCodeGenerationDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CodeGeneration.h"

ClassCount=4
Class1=CCodeGenerationApp
Class2=CCodeGenerationDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_PWD_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CPasswordDialog
Resource4=IDD_CODEGENERATION_DIALOG

[CLS:CCodeGenerationApp]
Type=0
HeaderFile=CodeGeneration.h
ImplementationFile=CodeGeneration.cpp
Filter=N

[CLS:CCodeGenerationDlg]
Type=0
HeaderFile=CodeGenerationDlg.h
ImplementationFile=CodeGenerationDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_RADIO_LANGUAGE_FR

[CLS:CAboutDlg]
Type=0
HeaderFile=CodeGenerationDlg.h
ImplementationFile=CodeGenerationDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CODEGENERATION_DIALOG]
Type=1
Class=CCodeGenerationDlg
ControlCount=30
Control1=IDC_COMBO_VERSIONS,combobox,1344340226
Control2=IDC_EDIT_NAME,edit,1350631552
Control3=IDC_EDIT_COMPANY,edit,1350631552
Control4=IDC_STATIC,button,1342177287
Control5=IDC_RADIO_LANGUAGE_ENG,button,1342308361
Control6=IDC_RADIO_LANGUAGE_FR,button,1342177289
Control7=IDC_EDIT_REGISTRATION,edit,1350631552
Control8=IDC_BUTTON_REGISTRATION,button,1342242817
Control9=IDC_BUTTON_CHECK,button,1342242816
Control10=IDOK,button,1342242816
Control11=IDCANCEL,button,1342242816
Control12=IDC_EDIT_STRING,edit,1350631552
Control13=IDC_BUTTON_ENCODE,button,1342242816
Control14=IDC_BUTTON_DECODE,button,1342242816
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,button,1342177287
Control22=IDC_EDIT_FILENAME,edit,1350633600
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EDIT_CHECKSUM,edit,1350633600
Control26=IDC_BUTTON_CHOOSEFILE,button,1342242816
Control27=IDC_BUTTON_GENERATE,button,1342242816
Control28=IDC_STATIC,static,1342308352
Control29=IDC_EDIT_EXTENSION,edit,1350631552
Control30=IDC_EDIT_LICENCE_TEXT,edit,1350633604

[DLG:IDD_PWD_DIALOG]
Type=1
Class=CPasswordDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PASSWORD_EDIT,edit,1350631584

[CLS:CPasswordDialog]
Type=0
HeaderFile=PasswordDialog.h
ImplementationFile=PasswordDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPasswordDialog

