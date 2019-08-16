/////////////////////////////////////////////////////////////////
// File : LicenceManagingResources.h

#if !defined(__LICENCEMANAGINGRESOURCES_H__)
#define __LICENCEMANAGINGRESOURCES_H__

// Time (in miliseconds) before checksum starts
//
#define TIME_BEFORE_CHECKSUM 3*60*1000

// General infos
//
#define SECURITYROOTKEY		HKEY_CLASSES_ROOT
#define STRPERIODKEYPATH	"Crvnscn\\v110"
#define DATE_ENTRY			"lcdt"
#define SERIAL				"V140PR33"
#define BUILD_NB			"06"
#define MYCOMPANY			"SquarePoint Software"
#define THISVERSION			"1.04.000"
#define MAJORVERSION_NB		1
#define MINORVERSION_NB		4
#define SOFTWARENAME		"CurveUnscan"


// Training period confirmation file :
//

// filename (created somewhere in the disk)
#define CONFIRM_FILENAME "srsftw.dll"
#define CONFIRM_REGPATH "Software\\Microsoft\\ie"
#define CONFIRM_REGKEYNAME "rmntm"
// Section name
#define CONFIRM_SECTION "Prmtr"
// Installation date entry
#define INSTALL_ENTRY "nstl"
// First use entry
#define FIRSTUSE_ENTRY "frst"
// Last use entry
#define LASTUSE_ENTRY "lst"
// number of days before writing confirm file
#define TEST_PERIOD_DAYS_NB 31
#define NBOFDAYSBEFOREWRITINGCONFIRMFILE 3

//--- Export limitation
#define EXPORT_NB_FILENAME "csvtosh.dll"
#define EXPORT_NB_REGPATH "Software\\Microsoft\\ie"
#define EXPORT_NB_REGKEYNAME "tgdtsn"

#define EXPORT_NB_SECTION "xprtnb"
#define EXPORT_NB_ENTRY "value"
#define INITIAL_EXPORT_NB 5

//--- Checksum
#define CHECKSUM_FILENAME_EXT "chk"

#endif // !defined(__LICENCEMANAGINGRESOURCES_H__)
